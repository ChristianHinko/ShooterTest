// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSGameplayAbility_FireGun.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/ASSAbilityTask_WaitTargetData.h"
#include "AbilitySystem/TargetActors/SSGameplayAbilityTargetActor_BulletTrace.h"
#include "AbilitySystem/ASSAbilitySystemBlueprintLibrary.h"
#include "Utilities/SSCollisionChannels.h"
#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"
#include "Subobjects/SSObject_ClipAmmo.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "Inventory/Item\Gun\SSItemStack_Gun.h"
#include "ArcInventoryItemTypes.h"
#include "Item\Definitions\ArcItemDefinition_Active.h"
#include "AbilitySystem/Types/ASSGameplayAbilityTypes.h"

#include "AbilityTasks/ASSEAbilityTask_Ticker.h"
#include "Kismet/GameplayStatics.h"
#include "AbilityTasks\ASSEAbilityTask_WaitInputPress.h"
#include "AbilityTasks\ASSEAbilityTask_WaitInputRelease.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"



USSGameplayAbility_FireGun::USSGameplayAbility_FireGun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESSAbilityInputID::PrimaryFire;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Fire);

	ShotNumber = 0;
	bInputPressed = false;
}


void USSGameplayAbility_FireGun::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);
}

// This ability is only given to the player while his Gun is active
void USSGameplayAbility_FireGun::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		check(0);
		return;
	}

	// Get initial values
	AmmoCost = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetAmmoCostAttribute());
	NumShotsPerBurst = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetNumShotsPerBurstAttribute());
	bFullAuto = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetbFullAutoAttribute());
	TimeBetweenFiresOverride = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute());
	TimeBetweenShots = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetTimeBetweenShotsAttribute());
	TimeBetweenBurstsOverride = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute());

	MaxRange = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetMaxRangeAttribute());
	NumberOfBulletsPerFire = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute());
	Penetrations = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetPenetrationsAttribute());
	Ricochets = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetRicochetsAttribute());
	InitialBulletSpeed = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetInitialBulletSpeedAttribute());
	BulletSpeedFalloff = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetBulletSpeedFalloffAttribute());


	//BEGIN Attribute value change binding
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetAmmoCostAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnAmmoCostChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetNumShotsPerBurstAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnNumShotsPerBurstChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetbFullAutoAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnbFullAutoChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnTimeBetweenFiresOverrideChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenShotsAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnTimeBetweenShotsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnTimeBetweenBurstsOverrideChange);

	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetMaxRangeAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnMaxRangeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnNumberOfBulletsPerFireChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetPenetrationsAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnPenetrationsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetRicochetsAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnRicochetsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetInitialBulletSpeedAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnInitialBulletSpeedChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetBulletSpeedFalloffAttribute()).AddUObject(this, &USSGameplayAbility_FireGun::OnBulletSpeedFalloffChange);
	//END Attribute value change binding





	// Need to make the item generators use the GunStack now
	// instead of it using item stack so this cast works.
	GunToFire = Cast<USSItemStack_Gun>(GetCurrentSourceObject());
	if (!GunToFire.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() No valid Gun when given the fire ability - ensure you are assigning the SourceObject to a GunStack when calling GiveAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	ClipAmmoSubobject = GunToFire->GetClipAmmoSubobject();
	BulletSpreadSubobject = GunToFire->GetBulletSpreadSubobject();






	// Inject the data our Target Actor needs and spawn it 
	BulletTraceTargetActor = GetWorld()->SpawnActorDeferred<ASSGameplayAbilityTargetActor_BulletTrace>(GunToFire->BulletTargetActorTSub, FTransform());
	if (!IsValid(BulletTraceTargetActor))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() No valid BulletTraceTargetActor in the GunStack when giving the fire ability. How the heck we supposed to fire the gun!?!?"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}

	BulletTraceTargetActor->OwningAbility = this;
	BulletTraceTargetActor->bDestroyOnConfirmation = false;

	FASSGameplayTargetDataFilter_MultiFilter MultiFilter = FASSGameplayTargetDataFilter_MultiFilter();
	MultiFilter.bOnlyAcceptAbilitySystemInterfaces = true;
	BulletTraceTargetActor->Filter = UASSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(MultiFilter, ActorInfo->AvatarActor.Get());

	UGameplayStatics::FinishSpawningActor(BulletTraceTargetActor, FTransform());
}

// This ability is only given to the player while his Gun is active
void USSGameplayAbility_FireGun::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		check(0);
		return;
	}

	//BEGIN Unbind from Attribute value change delegates
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetAmmoCostAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetNumShotsPerBurstAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetbFullAutoAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenFiresOverrideAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenShotsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetTimeBetweenBurstsOverrideAttribute()).RemoveAll(this);

	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetMaxRangeAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetNumberOfBulletsPerFireAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetPenetrationsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetRicochetsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetInitialBulletSpeedAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Gun::GetBulletSpeedFalloffAttribute()).RemoveAll(this);
	//END Unbind from Attribute value change delegates





	GunToFire = nullptr;
	if (IsValid(BulletTraceTargetActor) && BulletTraceTargetActor->Destroy())
	{
		BulletTraceTargetActor = nullptr;
	}

	ClipAmmoSubobject = nullptr;
	BulletSpreadSubobject = nullptr;
}

bool USSGameplayAbility_FireGun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}


	if (!GunToFire.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GunToFire was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!IsValid(BulletTraceTargetActor))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() BulletTraceTargetActor was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!ClipAmmoSubobject.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ClipAmmoSubobject was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (!BulletSpreadSubobject.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() BulletSpreadSubobject was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}

bool USSGameplayAbility_FireGun::CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCooldown(Handle, ActorInfo, OptionalRelevantTags))
	{
		return false;
	}

	// If we're firing too fast
	const float TimePassed = GetWorld()->GetTimeSeconds() - TimestampPreviousFireEnd;
	if (TimePassed < GetTimeBetweenFires())
	{
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Tried firing gun faster than the gun's FireRate allowed. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}
bool USSGameplayAbility_FireGun::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags))
	{
		return false;
	}

	// If we don't have enough ammo
	const float ClipAmmoAfterNextShot = ClipAmmoSubobject->ClipAmmo - AmmoCost;
	if (ClipAmmoAfterNextShot < 0)
	{
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Not enough ammo to perform a fire. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}

void USSGameplayAbility_FireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	bInputPressed = true;


	if (IsFullAuto() || IsBurst()) // if full auto or burst mode
	{
		TickerTask = UASSEAbilityTask_Ticker::Ticker(this, false, -1.f, TimeBetweenShots);
		if (!IsValid(TickerTask))
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate fire ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
	}

	if (IsFullAuto())
	{
		// We only want a release task if we are full auto
		UASSEAbilityTask_WaitInputRelease* WaitInputReleaseTask = UASSEAbilityTask_WaitInputRelease::WaitInputRelease(this, false, true);
		if (!IsValid(WaitInputReleaseTask))
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputReleaseTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), ANSI_TO_TCHAR(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &USSGameplayAbility_FireGun::OnRelease);
		WaitInputReleaseTask->ReadyForActivation();
	}
	if (IsFullAuto() && IsBurst()) // if we are full auto burst
	{
		UASSEAbilityTask_WaitInputPress* WaitInputPressTask = UASSEAbilityTask_WaitInputPress::WaitInputPress(this, false, true);
		if (!IsValid(WaitInputPressTask))
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputPressTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), ANSI_TO_TCHAR(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		WaitInputPressTask->OnPress.AddDynamic(this, &USSGameplayAbility_FireGun::OnPress);
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
		UE_LOG(LogGameplayAbility, Warning, TEXT("IsFiringGunEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
	}


	if (IsFullAuto() == false && IsBurst() == false) // semi-auto and single shot
	{
		Shoot();
		return;
	}

	TickerTask->OnTick.AddDynamic(this, &USSGameplayAbility_FireGun::OnShootTick);
	TickerTask->ReadyForActivation();

	// If we ended ability within the above functions, return here (this is important for if we want to do further logic after)
	if (bIsActive == false)
	{
		return;
	}




}


void USSGameplayAbility_FireGun::OnShootTick(float DeltaTime, float CurrentTime, float TimeRemaining)
{
	// No burst
	if (IsBurst() == false)
	{
		Shoot();
		return;
	}


	// Burst logic:
	int32 ShotsPerBurst = NumShotsPerBurst;

	// Semi-auto burst
	if (IsFullAuto() == false)
	{
		if (TimesBursted < ShotsPerBurst)
		{
			Shoot();
			++TimesBursted;
			return;
		}

		// No more bursts left
		return;
	}

	// Full-auto burst
	if (TimesBursted < ShotsPerBurst)
	{
		Shoot();
		++TimesBursted;

		// If this was our last shot in this burst
		if (TimesBursted >= ShotsPerBurst)
		{
			TimesBursted = 0; // reset times bursted

			TickerTask->Freeze(GetTimeBetweenBursts());	// For full auto, just freeze the ticker for a little so we can continue to fire again (of course unless the player lets go of the fire button)

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

void USSGameplayAbility_FireGun::Shoot()
{
	++ShotNumber;

	if (!CheckCost(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()))
	{
		// Currently this never gets hit. But left it here for now in case we want to make this ability trigger the shoot function even if you have no ammo.
		// The reason you may want to do this is so that you could do some kind of thing in response to a shot not having ammo (ie. play clicking sound or animation idk)
		// Not saying this is where it should be done, but thought it might be useful to keep for now if we ever end up liking the idea.
		// Another suggestion of where to do these kind of things would maybe to do it in the OnShootTick(), so we don't have to call this function and we could do these effects in there.
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Not enough ammo to shoot"), ANSI_TO_TCHAR(__FUNCTION__));

		return;
	}

	// Play shoot montage
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWaitTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("ShootMontage"), ShootMontage, 1.f, NAME_None, false);
	if (!IsValid(PlayMontageAndWaitTask))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() PlayMontageAndWaitTask was NULL when trying to shoot. Called EndAbility() so shot doesn't happen to keep things consistant"), ANSI_TO_TCHAR(__FUNCTION__));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}
	PlayMontageAndWaitTask->ReadyForActivation();

	// Try to make wait target data task for this shot
	UASSAbilityTask_WaitTargetData* WaitTargetDataActorTask = UASSAbilityTask_WaitTargetData::ASSWaitTargetDataUsingActor(this, TEXT("WaitTargetDataActorTask"), EGameplayTargetingConfirmation::Instant, BulletTraceTargetActor);
	if (!IsValid(WaitTargetDataActorTask))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitTargetDataActorTask was NULL when trying to shoot. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}

	// Bind to wait target data delegates
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &USSGameplayAbility_FireGun::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &USSGameplayAbility_FireGun::OnCancelled);

	BulletTraceTargetActor->SourceActor = GetAvatarActorFromActorInfo();

	// Update our target actor's start location
	BulletTraceTargetActor->StartLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	FVector ViewStart = FVector::ZeroVector;
	if (const FASSGameplayAbilityActorInfo* ASSActorInfo = static_cast<const FASSGameplayAbilityActorInfo*>(GetCurrentActorInfo()))
	{
		FRotator ViewRot;
		ASSActorInfo->Controller->GetPlayerViewPoint(ViewStart, ViewRot);
	}
	BulletTraceTargetActor->StartLocation.LiteralTransform.SetLocation(ViewStart); // we just want to use the player camera position directly for our StartLocation
	
	// Inject random seed - btw it's cool that we have a net safe random seed and we have a system for it, but reality is we don't need it now since client will just send its target data to server.
	const int16 PredictionKey = GetCurrentActivationInfo().GetActivationPredictionKey().Current;	// Use the prediction key as a net safe random seed.
	const int32 FireRandomSeed = PredictionKey + ShotNumber;										// Make the random seed unique to this particular fire
	BulletTraceTargetActor->FireSpecificNetSafeRandomSeed = FireRandomSeed;					// Inject this random seed into our target actor (target actor will make random seed unique to each bullet in the fire if there are multible bullets in the fire)

	// Inject our CurrentBulletSpread
	BulletTraceTargetActor->CurrentBulletSpread = BulletSpreadSubobject->CurrentBulletSpread;

	// Inject our current Attribute values
	BulletTraceTargetActor->MaxRange = MaxRange;
	BulletTraceTargetActor->NumOfBullets = NumberOfBulletsPerFire;
	BulletTraceTargetActor->MaxPenetrations = Penetrations;
	BulletTraceTargetActor->MaxRicochets = Ricochets;
	BulletTraceTargetActor->InitialBulletSpeed = InitialBulletSpeed;
	BulletTraceTargetActor->RangeFalloffNerf = BulletSpeedFalloff;    // TODO: We're not sure we want this value to be gun specific. We want it to be more of a static value for all guns (maybe define it statically in the bullet trace file)



	// Lets finally fire
	ClipAmmoSubobject->ClipAmmo = ClipAmmoSubobject->ClipAmmo - AmmoCost;
	WaitTargetDataActorTask->ReadyForActivation();
	BulletSpreadSubobject->ApplyFireBulletSpread();
}


void USSGameplayAbility_FireGun::OnPress(float TimeWaited)
{
	bInputPressed = true;
}

void USSGameplayAbility_FireGun::OnRelease(float TimeHeld)
{
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

void USSGameplayAbility_FireGun::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	// Apply effects
	if (GunToFire->BulletInflictEffectTSub)
	{
		if (Data.Num() > 0)	// No need to call if we have no targets
		{
			ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), Data, GunToFire->BulletInflictEffectTSub, GetAbilityLevel());
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): GunToFire gave us an empty BulletInflictEffectTSub. Make sure to fill out DefaultBulletInflictEffectTSub in the Item Generator"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	// Execute cues
	//GetAbilitySystemComponentFromActorInfo()->AddGameplayCue(GameplayCue_Test);	// Very temp. This is just to see a gc work




	// Only thing to do left is to decide if we should end the ability or not........


	// If we don't have enough ammo for another shot, always end here
	if (!CheckCost(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()))
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
void USSGameplayAbility_FireGun::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): Not sure how this got hit :/ Something unexpected happened"), ANSI_TO_TCHAR(__FUNCTION__));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void USSGameplayAbility_FireGun::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Store when this fire ended so next fire can determine fire rate
	TimestampPreviousFireEnd = GetWorld()->GetTimeSeconds();

	// Reset back to zero for next activation
	ShotNumber = 0;
	TimesBursted = 0;

	if (ActorInfo->AbilitySystemComponent.Get())
	{
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(IsFiringGunEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove IsFiringGunEffectActiveHandle"), ANSI_TO_TCHAR(__FUNCTION__));
	}


	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}





//BEGIN Attribute Set helpers
bool USSGameplayAbility_FireGun::IsFullAuto() const
{
	return static_cast<bool>(bFullAuto);
}
bool USSGameplayAbility_FireGun::IsBurst() const
{
	const int32 ShotsPerBurst = NumShotsPerBurst;

	const bool bIsBurst = (ShotsPerBurst > 1);
	return bIsBurst;
}

float USSGameplayAbility_FireGun::GetTimeBetweenFires() const
{
	return (TimeBetweenFiresOverride < 0) ? TimeBetweenShots : TimeBetweenFiresOverride;
}
float USSGameplayAbility_FireGun::GetTimeBetweenBursts() const
{
	return (TimeBetweenBurstsOverride < 0) ? TimeBetweenShots : TimeBetweenBurstsOverride;
}

bool USSGameplayAbility_FireGun::CurrentlyBursting() const
{
	if (IsBurst() == false)
	{
		return false;
	}

	const int32 ShotsPerBurst = NumShotsPerBurst;

	const bool bHasBurstsLeft = (TimesBursted > 0 && TimesBursted < ShotsPerBurst);
	return bHasBurstsLeft;
}
//END Attribute Set helpers



void USSGameplayAbility_FireGun::OnTimeBetweenShotsChange(const FOnAttributeChangeData& Data)
{
	TimeBetweenShots = Data.NewValue;

	if (IsValid(TickerTask))
	{
		// Update AT_Ticker
		TickerTask->SetTickInterval(TimeBetweenShots);
	}
}



void USSGameplayAbility_FireGun::OnMaxRangeChange(const FOnAttributeChangeData& Data)
{
	MaxRange = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->MaxRange = MaxRange;
	}
}
void USSGameplayAbility_FireGun::OnNumberOfBulletsPerFireChange(const FOnAttributeChangeData& Data)
{
	NumberOfBulletsPerFire = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->NumOfBullets = NumberOfBulletsPerFire;
	}
}
void USSGameplayAbility_FireGun::OnPenetrationsChange(const FOnAttributeChangeData& Data)
{
	Penetrations = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->MaxPenetrations = Penetrations;
	}
}
void USSGameplayAbility_FireGun::OnRicochetsChange(const FOnAttributeChangeData& Data)
{
	Ricochets = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->MaxRicochets = Ricochets;
	}
}
void USSGameplayAbility_FireGun::OnInitialBulletSpeedChange(const FOnAttributeChangeData& Data)
{
	InitialBulletSpeed = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->InitialBulletSpeed = InitialBulletSpeed;
	}
}
void USSGameplayAbility_FireGun::OnBulletSpeedFalloffChange(const FOnAttributeChangeData& Data)
{
	BulletSpeedFalloff = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update SSGameplayAbilityTargetActor_BulletTrace
		BulletTraceTargetActor->RangeFalloffNerf = BulletSpeedFalloff;
	}
}
