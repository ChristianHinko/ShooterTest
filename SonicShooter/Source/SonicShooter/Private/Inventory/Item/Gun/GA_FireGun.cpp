// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/GA_FireGun.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/ASSAbilityTask_WaitTargetData.h"
#include "AbilitySystem/TargetActors/GATA_BulletTrace.h"
#include "AbilitySystem/ASSAbilitySystemBlueprintLibrary.h"
#include "Utilities/CollisionChannels.h"
#include "Inventory/Item/Gun/AS_Gun.h"
#include "Subobjects/O_ClipAmmo.h"
#include "Subobjects/O_BulletSpread.h"
#include "Inventory/Item\Gun\ArcItemStack_Gun.h"
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
	AbilityTags.AddTag(NativeGameplayTags::Ability_Fire);

	ShotNumber = 0;
	bInputPressed = false;
}


void UGA_FireGun::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
	Super::OnAvatarSet(ActorInfo, Spec);
}

// This ability is only given to the player while his Gun is active
void UGA_FireGun::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		check(0);
		return;
	}

	// Get initial values
	AmmoCost = ASC->GetNumericAttribute(UAS_Gun::GetAmmoCostAttribute());
	NumShotsPerBurst = ASC->GetNumericAttribute(UAS_Gun::GetNumShotsPerBurstAttribute());
	bFullAuto = ASC->GetNumericAttribute(UAS_Gun::GetbFullAutoAttribute());
	TimeBetweenFiresOverride = ASC->GetNumericAttribute(UAS_Gun::GetTimeBetweenFiresOverrideAttribute());
	TimeBetweenShots = ASC->GetNumericAttribute(UAS_Gun::GetTimeBetweenShotsAttribute());
	TimeBetweenBurstsOverride = ASC->GetNumericAttribute(UAS_Gun::GetTimeBetweenBurstsOverrideAttribute());

	MaxRange = ASC->GetNumericAttribute(UAS_Gun::GetMaxRangeAttribute());
	NumberOfBulletsPerFire = ASC->GetNumericAttribute(UAS_Gun::GetNumberOfBulletsPerFireAttribute());
	Penetrations = ASC->GetNumericAttribute(UAS_Gun::GetPenetrationsAttribute());
	Ricochets = ASC->GetNumericAttribute(UAS_Gun::GetRicochetsAttribute());
	InitialBulletSpeed = ASC->GetNumericAttribute(UAS_Gun::GetInitialBulletSpeedAttribute());
	BulletSpeedFalloff = ASC->GetNumericAttribute(UAS_Gun::GetBulletSpeedFalloffAttribute());


	//BEGIN Attribute value change binding
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetAmmoCostAttribute()).AddUObject(this, &UGA_FireGun::OnAmmoCostChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetNumShotsPerBurstAttribute()).AddUObject(this, &UGA_FireGun::OnNumShotsPerBurstChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetbFullAutoAttribute()).AddUObject(this, &UGA_FireGun::OnbFullAutoChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenFiresOverrideAttribute()).AddUObject(this, &UGA_FireGun::OnTimeBetweenFiresOverrideChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenShotsAttribute()).AddUObject(this, &UGA_FireGun::OnTimeBetweenShotsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenBurstsOverrideAttribute()).AddUObject(this, &UGA_FireGun::OnTimeBetweenBurstsOverrideChange);

	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMaxRangeAttribute()).AddUObject(this, &UGA_FireGun::OnMaxRangeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetNumberOfBulletsPerFireAttribute()).AddUObject(this, &UGA_FireGun::OnNumberOfBulletsPerFireChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetPenetrationsAttribute()).AddUObject(this, &UGA_FireGun::OnPenetrationsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetRicochetsAttribute()).AddUObject(this, &UGA_FireGun::OnRicochetsChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetInitialBulletSpeedAttribute()).AddUObject(this, &UGA_FireGun::OnInitialBulletSpeedChange);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpeedFalloffAttribute()).AddUObject(this, &UGA_FireGun::OnBulletSpeedFalloffChange);
	//END Attribute value change binding





	// Need to make the item generators use the GunStack now
	// instead of it using item stack so this cast works.
	GunToFire = Cast<UArcItemStack_Gun>(GetCurrentSourceObject());
	if (!GunToFire.IsValid())
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid Gun when given the fire ability - ensure you are assigning the SourceObject to a GunStack when calling GiveAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}

	ClipAmmoSubobject = GunToFire->GetClipAmmoSubobject();
	BulletSpreadSubobject = GunToFire->GetBulletSpreadSubobject();






	// Inject the data our Target Actor needs and spawn it 
	BulletTraceTargetActor = GetWorld()->SpawnActorDeferred<AGATA_BulletTrace>(GunToFire->BulletTargetActorTSub, FTransform());
	if (!IsValid(BulletTraceTargetActor))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() No valid BulletTraceTargetActor in the GunStack when giving the fire ability. How the heck we supposed to fire the gun!?!?"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}

	BulletTraceTargetActor->OwningAbility = this;
	BulletTraceTargetActor->bDestroyOnConfirmation = false;

	FGTDF_MultiFilter MultiFilter = FGTDF_MultiFilter();
	MultiFilter.bOnlyAcceptAbilitySystemInterfaces = true;
	BulletTraceTargetActor->Filter = UASSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(MultiFilter, ActorInfo->AvatarActor.Get());

	UGameplayStatics::FinishSpawningActor(BulletTraceTargetActor, FTransform());
}

// This ability is only given to the player while his Gun is active
void UGA_FireGun::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!IsValid(ASC))
	{
		check(0);
		return;
	}

	//BEGIN Unbind from Attribute value change delegates
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetAmmoCostAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetNumShotsPerBurstAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetbFullAutoAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenFiresOverrideAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenShotsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetTimeBetweenBurstsOverrideAttribute()).RemoveAll(this);

	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMaxRangeAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetNumberOfBulletsPerFireAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetPenetrationsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetRicochetsAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetInitialBulletSpeedAttribute()).RemoveAll(this);
	ASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpeedFalloffAttribute()).RemoveAll(this);
	//END Unbind from Attribute value change delegates





	GunToFire = nullptr;
	if (IsValid(BulletTraceTargetActor) && BulletTraceTargetActor->Destroy())
	{
		BulletTraceTargetActor = nullptr;
	}

	ClipAmmoSubobject = nullptr;
	BulletSpreadSubobject = nullptr;
}

bool UGA_FireGun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

bool UGA_FireGun::CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
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
bool UGA_FireGun::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

void UGA_FireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	bInputPressed = true;


	if (IsFullAuto() || IsBurst()) // if full auto or burst mode
	{
		TickerTask = UAT_Ticker::Ticker(this, false, -1.f, TimeBetweenShots);
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
		UAT_WaitInputRelease* WaitInputReleaseTask = UAT_WaitInputRelease::WaitInputRelease(this, false, true);
		if (!IsValid(WaitInputReleaseTask))
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputReleaseTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), ANSI_TO_TCHAR(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_FireGun::OnRelease);
		WaitInputReleaseTask->ReadyForActivation();
	}
	if (IsFullAuto() && IsBurst()) // if we are full auto burst
	{
		UAT_WaitInputPress* WaitInputPressTask = UAT_WaitInputPress::WaitInputPress(this, false, true);
		if (!IsValid(WaitInputPressTask))
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() WaitInputPressTask was NULL when trying to activate a fire. Called EndAbility() to prevent further weirdness"), ANSI_TO_TCHAR(__FUNCTION__));
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
		UE_LOG(LogGameplayAbility, Warning, TEXT("IsFiringGunEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
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

void UGA_FireGun::Shoot()
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
	WaitTargetDataActorTask->ValidData.AddDynamic(this, &UGA_FireGun::OnValidData);
	WaitTargetDataActorTask->Cancelled.AddDynamic(this, &UGA_FireGun::OnCancelled);

	BulletTraceTargetActor->SourceActor = GetAvatarActorFromActorInfo();

	// Update our target actor's start location
	BulletTraceTargetActor->bUseAimPointAsStartLocation = true; // we just want to use the player camera position directly for our StartLocation
	
	// Inject random seed - btw it's cool that we have a net safe random seed and we have a system for it, but reality is we don't need it now since client will just send its target data to server.
	const int16 PredictionKey = GetCurrentActivationInfo().GetActivationPredictionKey().Current;	// Use the prediction key as a net safe random seed.
	const int32 FireRandomSeed = PredictionKey + ShotNumber;										// Make the random seed unique to this particular fire
	BulletTraceTargetActor->FireSpecificNetSafeRandomSeed = FireRandomSeed;					// Inject this random seed into our target actor (target actor will make random seed unique to each bullet in the fire if there are multible bullets in the fire)

	// Inject our CurrentBulletSpread
	BulletTraceTargetActor->CurrentBulletSpread = BulletSpreadSubobject->CurrentBulletSpread;

	// Inject our current Attribute values
	BulletTraceTargetActor->MaxRange = MaxRange;
	BulletTraceTargetActor->NumOfScans = NumberOfBulletsPerFire;
	BulletTraceTargetActor->NumOfPenetrations = Penetrations;
	BulletTraceTargetActor->NumOfRicochets = Ricochets;
	BulletTraceTargetActor->InitialBulletSpeed = InitialBulletSpeed;
	BulletTraceTargetActor->BulletSpeedFalloff = BulletSpeedFalloff;



	// Lets finally fire
	ClipAmmoSubobject->ClipAmmo = ClipAmmoSubobject->ClipAmmo - AmmoCost;
	WaitTargetDataActorTask->ReadyForActivation();
	BulletSpreadSubobject->ApplyFireBulletSpread();
}


void UGA_FireGun::OnPress(float TimeWaited)
{
	bInputPressed = true;
}

void UGA_FireGun::OnRelease(float TimeHeld)
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

void UGA_FireGun::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
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
void UGA_FireGun::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): Not sure how this got hit :/ Something unexpected happened"), ANSI_TO_TCHAR(__FUNCTION__));
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



	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}





//BEGIN Attribute Set helpers
bool UGA_FireGun::IsFullAuto() const
{
	return static_cast<bool>(bFullAuto);
}
bool UGA_FireGun::IsBurst() const
{
	const int32 ShotsPerBurst = NumShotsPerBurst;

	const bool bIsBurst = (ShotsPerBurst > 1);
	return bIsBurst;
}

float UGA_FireGun::GetTimeBetweenFires() const
{
	return (TimeBetweenFiresOverride < 0) ? TimeBetweenShots : TimeBetweenFiresOverride;
}
float UGA_FireGun::GetTimeBetweenBursts() const
{
	return (TimeBetweenBurstsOverride < 0) ? TimeBetweenShots : TimeBetweenBurstsOverride;
}

bool UGA_FireGun::CurrentlyBursting() const
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



void UGA_FireGun::OnTimeBetweenShotsChange(const FOnAttributeChangeData& Data)
{
	TimeBetweenShots = Data.NewValue;

	if (IsValid(TickerTask))
	{
		// Update AT_Ticker
		TickerTask->SetTickInterval(TimeBetweenShots);
	}
}



void UGA_FireGun::OnMaxRangeChange(const FOnAttributeChangeData& Data)
{
	MaxRange = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->MaxRange = MaxRange;
	}
}
void UGA_FireGun::OnNumberOfBulletsPerFireChange(const FOnAttributeChangeData& Data)
{
	NumberOfBulletsPerFire = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->NumOfScans = NumberOfBulletsPerFire;
	}
}
void UGA_FireGun::OnPenetrationsChange(const FOnAttributeChangeData& Data)
{
	Penetrations = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->NumOfPenetrations = Penetrations;
	}
}
void UGA_FireGun::OnRicochetsChange(const FOnAttributeChangeData& Data)
{
	Ricochets = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->NumOfRicochets = Ricochets;
	}
}
void UGA_FireGun::OnInitialBulletSpeedChange(const FOnAttributeChangeData& Data)
{
	InitialBulletSpeed = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->InitialBulletSpeed = InitialBulletSpeed;
	}
}
void UGA_FireGun::OnBulletSpeedFalloffChange(const FOnAttributeChangeData& Data)
{
	BulletSpeedFalloff = Data.NewValue;

	if (IsValid(BulletTraceTargetActor))
	{
		// Update GATA_BulletTrace
		BulletTraceTargetActor->BulletSpeedFalloff = BulletSpeedFalloff;
	}
}
