// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GA_FireGun.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/AT_SSWaitTargetData.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Utilities/CollisionChannels.h"
#include "Item/AS_Gun.h"
#include "Item/AS_Ammo.h"
#include "Item\Weapons\GunStack.h"
#include "ArcInventoryItemTypes.h"
#include "Item\Definitions\ArcItemDefinition_Active.h"
#include "AbilitySystem/AbilityTasks/AT_Ticker.h"
#include "AbilitySystem\AbilityTasks\AT_WaitInputReleaseCust.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_FireGun::UGA_FireGun()
{
	AbilityInputID = EAbilityInputID::PrimaryFire;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("AbilityInput.PrimaryFire")));

	fireNumber = 0;

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

	// Spawn the Gun's target actor
	BulletTraceTargetActor = GetWorld()->SpawnActorDeferred<AGATA_BulletTrace>(GunToFire->BulletTraceTargetActorTSub, FTransform());
	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid BulletTraceTargetActor in the GunStack when giving the fire ability. How the heck we supposed to fire the gun!?!?"), *FString(__FUNCTION__));
		return;
	}
	BulletTraceTargetActor->OwningAbility = this;
	BulletTraceTargetActor->bDestroyOnConfirmation = false;

	UGameplayStatics::FinishSpawningActor(BulletTraceTargetActor, FTransform());


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

	// If we're firing too fast
	if (GetWorld()->GetTimeSeconds() - timestampPreviousFireEnd < GunAttributeSet->GetFireRate())
	{
		//UE_LOG(LogGameplayAbility, Log, TEXT("%s() Tried firing gun faster than the gun's FireRate allowed. returned false"), *FString(__FUNCTION__));
		return false;
	}


	return true;
}

void UGA_FireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);



	UAT_Ticker* TickerTask = nullptr;
	if (GunToFire->FiringMode != EGunFireMode::MODE_SemiAuto)
	{
		TickerTask = UAT_Ticker::Ticker(this, false, -1.f, 1 / GunAttributeSet->GetAutoShootingRate());
		if (!TickerTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate fire ability. Called EndAbility()"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
	}
	
	// We only want a release task if we are a full auto fire
	UAT_WaitInputReleaseCust* WaitInputReleaseTask = nullptr;
	if (GunToFire->FiringMode == EGunFireMode::MODE_FullAuto)
	{
		WaitInputReleaseTask = UAT_WaitInputReleaseCust::WaitInputReleaseCust(this);
		if (!WaitInputReleaseTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputReleaseTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////////////////// we are safe to proceed /////////

	if (FireEffectTSub)
	{
		FireEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, FireEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("FireEffectTSub TSubclassOf empty in %s"), *FString(__FUNCTION__));
	}





	switch (GunToFire->FiringMode)
	{
	case EGunFireMode::MODE_SemiAuto:
		Fire();
		break;

	case EGunFireMode::MODE_Burst:

		TickerTask->OnTick.AddDynamic(this, &UGA_FireGun::OnFullAutoTick);
		TickerTask->ReadyForActivation();

		break;

	case EGunFireMode::MODE_FullAuto:

		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_FireGun::OnRelease);
		WaitInputReleaseTask->ReadyForActivation();

		TickerTask->OnTick.AddDynamic(this, &UGA_FireGun::OnFullAutoTick);
		TickerTask->ReadyForActivation();

		break;


	default:
		break;
	}

}




void UGA_FireGun::OnFullAutoTick(float DeltaTime, float CurrentTime, float TimeRemaining)
{
	// Full-auto logic
	if (GunToFire->FiringMode == EGunFireMode::MODE_FullAuto)
	{
		Fire();
		return;
	}

	// Burst logic
	if (GunToFire->FiringMode == EGunFireMode::MODE_Burst)
	{
		const int32 TimesToBurst = GunAttributeSet->GetNumBursts();
		if (TimesToBurst > 0 && timesBursted < TimesToBurst)
		{
			Fire();
			++timesBursted;
			return;
		}

		// No more bursts left
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
		return;
	}
}

void UGA_FireGun::Fire()
{
	++fireNumber;
	// Check if we have enough ammo first
	if (AmmoAttributeSet->GetClipAmmo() < GunAttributeSet->GetAmmoCost()) // if we don't have enough ammo
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Not enough ammo to fire"), *FString(__FUNCTION__));

		// Handle out of ammo




		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}


	// Try to make wait target data task for this shot
	UAT_SSWaitTargetData* WaitTargetDataActorTask = UAT_SSWaitTargetData::SSWaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::Instant, BulletTraceTargetActor);
	if (!WaitTargetDataActorTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to shoot. Called EndAbility()"), *FString(__FUNCTION__));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}
	// Bind to wait target data delegates and activate the task
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_FireGun::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &UGA_FireGun::OnCancelled);


	BulletTraceTargetActor->StartLocation = MakeTargetLocationInfoFromOwnerSkeletalMeshComponent(TEXT("None"));		// this will take the actor info's skeletal mesh, maybe make our own in SSGameplayAbility which you can specify a skeletal mesh to use


	const int16 predKey = GetCurrentActivationInfo().GetActivationPredictionKey().Current;	// Use the prediction key as a net safe random seed.
	const int32 fireRandomSeed = predKey + fireNumber;										// Make the random seed unique to this particular fire
	BulletTraceTargetActor->FireSpecificNetSafeRandomSeed = fireRandomSeed;							// Inject this random seed into our target actor (target actor will make random seed unique to each bullet in the fire if there are multible bullets in the fire)

	// Lets finally fire
	AmmoAttributeSet->SetClipAmmo(AmmoAttributeSet->GetClipAmmo() - GunAttributeSet->GetAmmoCost());
	WaitTargetDataActorTask->ReadyForActivation();
	GunAttributeSet->ApplyFireBulletSpread();
}






void UGA_FireGun::OnRelease(float TimeHeld)
{
	// When a machine gun stops shooting
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_FireGun::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	if (TSubclassOf<UGameplayEffect> BulletHitEffectTSub = GunToFire->BulletHitEffectTSub)
	{
		if (Data.Num() > 0)	// No need to call if we have no targets
		{
			// Create our effect spec so we can pass target data stuff into it for the GEEC
			ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), Data, GunToFire->BulletHitEffectTSub, GetAbilityLevel());
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): GunToFire gave us an empty BulletHitEffectTSub. Make sure to fill out DefaultBulletHitEffectTSub in the Gun generator"), *FString(__FUNCTION__));
	}
	
	if (GunToFire->FiringMode == EGunFireMode::MODE_SemiAuto)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}
void UGA_FireGun::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	// This won't ever happen for hit scans I think, but if it does we'll just end the ability I guess
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
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

	// Store when this fire ended so next fire can determine fire rate
	timestampPreviousFireEnd = GetWorld()->GetTimeSeconds();

	// Reset back to zero for next activation
	fireNumber = 0;
	timesBursted = 0;

	if (ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(FireEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove FireEffectActiveHandle"), *FString(__FUNCTION__));
	}



	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
