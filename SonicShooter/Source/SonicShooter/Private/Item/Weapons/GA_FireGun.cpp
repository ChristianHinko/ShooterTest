// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GA_FireGun.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/ASSAbilityTask_WaitTargetData.h"
#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Utilities/CollisionChannels.h"
#include "Item/Weapons/AS_Gun.h"
#include "Item/AS_Ammo.h"
#include "Item\Weapons\GunStack.h"
#include "ArcInventoryItemTypes.h"
#include "Item\Definitions\ArcItemDefinition_Active.h"

#include "AbilityTasks/AT_Ticker.h"
#include "Kismet/GameplayStatics.h"
#include "AbilityTasks\AT_WaitInputPress.h"
#include "AbilityTasks\AT_WaitInputRelease.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"



UGA_FireGun::UGA_FireGun()
{
	AbilityInputID = EAbilityInputID::PrimaryFire;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("AbilityInput.PrimaryFire")));

	shotNumber = 0;
	bInputPressed = false;
}


void UGA_FireGun::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
	Super::OnAvatarSet(ActorInfo, Spec);


}

// This ability is only granted to the player while his Gun is active
void UGA_FireGun::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	// Need to make the item generators use the GunStack now
	// instead of it using item stack so this cast works.
	GunToFire = Cast<UGunStack>(GetCurrentSourceObject());
	if (!GunToFire)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid Gun when giving the fire ability"), *FString(__FUNCTION__));
		return;
	}

	{
		bool bFoundGunAS = false;
		bool bFoundAmmoAS = false;

		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		for (UAttributeSet* AttributeSet : ASC->GetSpawnedAttributes())
		{
			if (UAS_Gun* GunAS = Cast<UAS_Gun>(AttributeSet))
			{
				GunAttributeSet = GunAS;
				bFoundGunAS = true;
			}
			if (UAS_Ammo* AmmoAS = Cast<UAS_Ammo>(AttributeSet))
			{
				AmmoAttributeSet = AmmoAS;
				bFoundAmmoAS = true;
			}

			if (bFoundGunAS && bFoundAmmoAS) // this is a kind of a stupid optimization it's here
			{
				break;
			}
		}
	}


	// Inject the data our target actor needs and spawn it 
	BulletTraceTargetActor = GetWorld()->SpawnActorDeferred<AGATA_BulletTrace>(GunToFire->BulletTraceTargetActorTSub, FTransform());
	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid BulletTraceTargetActor in the GunStack when giving the fire ability. How the heck we supposed to fire the gun!?!?"), *FString(__FUNCTION__));
		return;
	}
	BulletTraceTargetActor->OwningAbility = this;
	BulletTraceTargetActor->bDestroyOnConfirmation = false;
	BulletTraceTargetActor->GunAttributeSet = GunAttributeSet;

	UGameplayStatics::FinishSpawningActor(BulletTraceTargetActor, FTransform());
}

// This ability is only granted to the player while his Gun is active
void UGA_FireGun::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	GunToFire = nullptr;
	if (BulletTraceTargetActor && BulletTraceTargetActor->Destroy())
	{
		BulletTraceTargetActor = nullptr;
	}

	GunAttributeSet = nullptr;
	AmmoAttributeSet = nullptr;
}

bool UGA_FireGun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}


	if (!GunToFire)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GunToFire was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}

	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() BulletTraceTargetActor was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}

	if (!GunAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GunAttributeSet was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!AmmoAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() AmmoAttributeSet was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!EnoughAmmoToShoot())
	{
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Not enough ammo to perform a fire. returned false"), *FString(__FUNCTION__));
		return false;
	}

	// If we're firing too fast
	const float timeBetweenFires = (GunAttributeSet->GetTimeBetweenFiresOverride() == -1) ? GunAttributeSet->GetTimeBetweenShots() : GunAttributeSet->GetTimeBetweenFiresOverride();
	const float timePassed = GetWorld()->GetTimeSeconds() - timestampPreviousFireEnd;
	if (timePassed < timeBetweenFires)
	{
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Tried firing gun faster than the gun's FireRate allowed. returned false"), *FString(__FUNCTION__));
		return false;
	}


	return true;
}

void UGA_FireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	bInputPressed = true;


	if (IsFullAuto() || IsBurst()) // if full auto or burst mode
	{
		TickerTask = UAT_Ticker::Ticker(this, false, -1.f, GunAttributeSet->GetTimeBetweenShots());
		if (!TickerTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate fire ability. Called EndAbility()"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
	}

	// We only want a release task if we are full auto
	UAT_WaitInputRelease* WaitInputReleaseTask = nullptr;
	if (IsFullAuto())
	{
		WaitInputReleaseTask = UAT_WaitInputRelease::WaitInputRelease(this, false, true);
		if (!WaitInputReleaseTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputReleaseTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_FireGun::OnRelease);
		WaitInputReleaseTask->ReadyForActivation();
	}
	UAT_WaitInputPress* WaitInputPressTask = nullptr;
	if (IsFullAuto() && IsBurst()) // if we are full auto burst
	{
		WaitInputPressTask = UAT_WaitInputPress::WaitInputPress(this, false, true);
		if (!WaitInputPressTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputPressTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		WaitInputPressTask->OnPress.AddDynamic(this, &UGA_FireGun::OnPress);
		WaitInputPressTask->ReadyForActivation();
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////////////////// we are safe to proceed /////////

	if (IsFiringGunEffectTSub)
	{
		IsFiringGunEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, IsFiringGunEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("IsFiringGunEffectTSub TSubclassOf empty in %s"), *FString(__FUNCTION__));
	}


	if (IsFullAuto() == false && IsBurst() == false) // semi-auto and single shot
	{
		Shoot();
		return;
	}


	TickerTask->OnTick.AddDynamic(this, &UGA_FireGun::OnShootTick);
	TickerTask->ReadyForActivation();

	// If we ended ability within the above functions, return here (this is important for if we want to do further logic after)
	if (bIsActive == false)
	{
		return;
	}




}


void UGA_FireGun::OnShootTick(float DeltaTime, float CurrentTime, float TimeRemaining)
{
	// No burst
	if (IsBurst() == false)
	{
		Shoot();
		return;
	}


	// Burst logic:
	int32 shotsPerBurst = GunAttributeSet->GetNumShotsPerBurst();

	// Semi-auto burst
	if (IsFullAuto() == false)
	{
		if (timesBursted < shotsPerBurst)
		{
			Shoot();
			++timesBursted;
			return;
		}

		// No more bursts left
		return;
	}

	// Full-auto burst
	if (timesBursted < shotsPerBurst)
	{
		Shoot();
		++timesBursted;

		// If this was our last shot in this burst
		if (timesBursted >= shotsPerBurst)
		{
			timesBursted = 0; // reset times bursted

			const float timeBetweenBursts = (GunAttributeSet->GetTimeBetweenBurstsOverride() == -1) ? GunAttributeSet->GetTimeBetweenShots() : GunAttributeSet->GetTimeBetweenBurstsOverride();
			TickerTask->Freeze(timeBetweenBursts);	// For full auto, just freeze the ticker for a little so we can continue to fire again (of course unless the player lets go of the fire button)

			// This is our last shot in the burst, check if we want to stop
			if (bInputPressed == false)
			{
				EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
				return;
			}
		}

		return;
	}
}

void UGA_FireGun::Shoot()
{
	++shotNumber;


	if (!EnoughAmmoToShoot())
	{
		// Currently this never gets hit. But left it here for now in case we want to make this ability trigger the shoot function even if you have no ammo.
		// The reason you may want to do this is so that you could do some kind of thing in response to a shot not having ammo (ie. play clicking sound or animation idk)
		// Not saying this is where it should be done, but thought it might be useful to keep for now if we ever end up liking the idea.
		// Another suggestion of where to do these kind of things would maybe to do it in the OnShootTick(), so we don't have to call this function and we could do these effects in there.
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Not enough ammo to shoot"), *FString(__FUNCTION__));

		return;
	}

	// Play shoot montage
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWaitTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("ShootMontage"), ShootMontage, 1.f, NAME_None, false);
	if (!PlayMontageAndWaitTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() PlayMontageAndWaitTask was NULL when trying to shoot. Called EndAbility() so shot doesn't happen to keep things consistant"), *FString(__FUNCTION__));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}
	PlayMontageAndWaitTask->ReadyForActivation();

	// Try to make wait target data task for this shot
	UASSAbilityTask_WaitTargetData* WaitTargetDataActorTask = UASSAbilityTask_WaitTargetData::ASSWaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::Instant, BulletTraceTargetActor);
	if (!WaitTargetDataActorTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to shoot. Called EndAbility()"), *FString(__FUNCTION__));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}
	// Bind to wait target data delegates
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_FireGun::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &UGA_FireGun::OnCancelled);


	// Update our target actor's start location
	BulletTraceTargetActor->bUseAimPointAsStartLocation = true; // we just want to use the player camera position directly for our StartLocation
	

	// btw it's cool that we have a net safe random seed and we have a system for it, but reality is we don't need it now since client will just send its target data to server.
	const int16 predKey = GetCurrentActivationInfo().GetActivationPredictionKey().Current;	// Use the prediction key as a net safe random seed.
	const int32 fireRandomSeed = predKey + shotNumber;										// Make the random seed unique to this particular fire
	BulletTraceTargetActor->FireSpecificNetSafeRandomSeed = fireRandomSeed;					// Inject this random seed into our target actor (target actor will make random seed unique to each bullet in the fire if there are multible bullets in the fire)

	// Lets finally fire
	UKismetSystemLibrary::PrintString(this, "Shoot", true, false, FLinearColor::Blue, 5.f);
	AmmoAttributeSet->ClipAmmo = AmmoAttributeSet->ClipAmmo - GunAttributeSet->GetAmmoCost();
	WaitTargetDataActorTask->ReadyForActivation();
	GunAttributeSet->ApplyFireBulletSpread();
}


void UGA_FireGun::OnPress(float TimeWaited)
{
	UKismetSystemLibrary::PrintString(this, "OnPress", true, false, FLinearColor::Green);
	bInputPressed = true;
}

void UGA_FireGun::OnRelease(float TimeHeld)
{
	UKismetSystemLibrary::PrintString(this, "OnRelease", true, false, FLinearColor::Yellow, 5.f);
	bInputPressed = false;

	// Only thing to do left is see if we should end the ability
	if (IsFullAuto())
	{
		if (IsBurst() && CurrentlyBursting()) // don't end ability yet if we are in the middle of a burst - we will wait until we finish the burst
		{
			// We don't end ability here because we need to wait until we finish bursting!
			return;
		}

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}

void UGA_FireGun::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	// Apply effects
	if (TSubclassOf<UGameplayEffect> BulletHitEffectTSub = GunToFire->BulletHitEffectTSub)
	{
		if (Data.Num() > 0)	// No need to call if we have no targets
		{
			ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), Data, GunToFire->BulletHitEffectTSub, GetAbilityLevel());
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): GunToFire gave us an empty BulletHitEffectTSub. Make sure to fill out DefaultBulletHitEffectTSub in the Gun generator"), *FString(__FUNCTION__));
	}

	// Execute cues
	//GetAbilitySystemComponentFromActorInfo()->AddGameplayCue(FGameplayTag::RequestGameplayTag("GameplayCue.Test"));	// Very temp. This is just to see a gc work




	// Only thing to do left is to decide if we should end the ability or not........


	// If we don't have enough ammo for another shot, always end here
	if (!EnoughAmmoToShoot())
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
		return;
	}


	if (IsFullAuto() == false)
	{
		if (IsBurst() == false)
		{
			// We are a single shot semi-auto - end here
			EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
			return;
		}


		if (IsBurst() && CurrentlyBursting() == false)
		{
			// We are out of shots for this burst - end here
			EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
			return;
		}
	}

}
void UGA_FireGun::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): Not sure how this got hit :/ Something unexpected happened"), *FString(__FUNCTION__));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UGA_FireGun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_FireGun::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	UKismetSystemLibrary::PrintString(this, "End", true, false, FLinearColor::Red, 5.f);
	// Store when this fire ended so next fire can determine fire rate
	timestampPreviousFireEnd = GetWorld()->GetTimeSeconds();

	// Reset back to zero for next activation
	shotNumber = 0;
	timesBursted = 0;

	if (ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(IsFiringGunEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove IsFiringGunEffectActiveHandle"), *FString(__FUNCTION__));
	}



	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}





bool UGA_FireGun::EnoughAmmoToShoot() const
{
	const float clipAmmoAfterNextShot = AmmoAttributeSet->ClipAmmo - GunAttributeSet->GetAmmoCost();
	return (clipAmmoAfterNextShot >= 0);
}

bool UGA_FireGun::IsFullAuto() const
{
	return !!GunAttributeSet->GetbFullAuto();
}
bool UGA_FireGun::IsBurst() const
{
	const int32 shotsPerBurst = GunAttributeSet->GetNumShotsPerBurst();

	const bool isBurst = (shotsPerBurst > 1);
	return isBurst;
}

bool UGA_FireGun::CurrentlyBursting() const
{
	if (IsBurst() == false)
	{
		return false;
	}

	const int32 shotsPerBurst = GunAttributeSet->GetNumShotsPerBurst();

	const bool hasBurstsLeft = (timesBursted > 0 && timesBursted < shotsPerBurst);
	return hasBurstsLeft;
}
