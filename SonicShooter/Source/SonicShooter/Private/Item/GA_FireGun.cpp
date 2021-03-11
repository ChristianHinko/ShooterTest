// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GA_FireGun.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AbilityTasks/AT_SSWaitTargetData.h"
#include "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Utilities/CollisionChannels.h"
#include "Item/AS_Ammo.h"
#include "Item\Weapons\WeaponStack.h"
#include "ArcInventoryItemTypes.h"
#include "Item\Definitions\ArcItemDefinition_Active.h"
#include "AbilitySystem/AbilityTasks/AT_Ticker.h"
#include "AbilitySystem\AbilityTasks\AT_WaitInputReleaseCust.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_FireGun::UGA_FireGun()
{
	AbilityInputID = EAbilityInputID::PrimaryFire;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Fire")));
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("AbilityInput.PrimaryFire")));


}


void UGA_FireGun::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
	Super::OnAvatarSet(ActorInfo, Spec);


}

// This ability is only granted to the player while his weapon is active
void UGA_FireGun::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	// Need to make the item generators use the weapon stack now
	// instead of it using item stack so this cast works.
	WeaponToFire = Cast<UWeaponStack>(GetCurrentSourceObject());
	if (!WeaponToFire)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid weapon (weapon stack) when giving the fire ability"), *FString(__FUNCTION__));
		return;
	}

	// Spawn the weapon's target actor
	FActorSpawnParameters TargetActorSpawnParameters;
	TargetActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	BulletTraceTargetActor = GetWorld()->SpawnActor<AGATA_BulletTrace>(WeaponToFire->BulletTraceTargetActorTSub, TargetActorSpawnParameters);
	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid BulletTraceTargetActor in the weapon item stack when giving the fire ability. How the heck we supposed to fire the weapon!?!?"), *FString(__FUNCTION__));
		return;
	}
	BulletTraceTargetActor->bDestroyOnConfirmation = false;


	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	for (UAttributeSet* AttributeSet : ASC->GetSpawnedAttributes())
	{
		if (UAS_Ammo* AmmoAS = Cast<UAS_Ammo>(AttributeSet))
		{
			AmmoAttributeSet = AmmoAS;
			break;
		}
	}
}

// This ability is only granted to the player while his weapon is active
void UGA_FireGun::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	WeaponToFire = nullptr;
	if (BulletTraceTargetActor && BulletTraceTargetActor->Destroy())
	{
		BulletTraceTargetActor = nullptr;
	}

	AmmoAttributeSet = nullptr;
}

bool UGA_FireGun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!BulletTraceTargetActor)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() BulletTraceTargetActor was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}

	if (!AmmoAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() AmmoAttributeSet was NULL. returned false"), *FString(__FUNCTION__));
		return false;
	}


	return true;
}

void UGA_FireGun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);



	UAT_Ticker* TickerTask = nullptr;
	if (WeaponToFire->FiringMode == EWeaponFireMode::MODE_FullAuto)
	{
		TickerTask = UAT_Ticker::Ticker(this, false, -1.f, WeaponToFire->FireRate);
		if (!TickerTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate fire ability. Called EndAbility()"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
	}
	
	// We only want a release task if we are a full auto fire
	UAT_WaitInputReleaseCust* WaitInputReleaseTask = nullptr;
	if (WeaponToFire->FiringMode == EWeaponFireMode::MODE_FullAuto && WeaponToFire->NumBursts <= 0)
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





	switch (WeaponToFire->FiringMode)
	{
	case EWeaponFireMode::MODE_SemiAuto:
		Fire();
		break;

	case EWeaponFireMode::MODE_FullAuto:
		if (WeaponToFire->NumBursts <= 0)
		{
			WaitInputReleaseTask->OnRelease.AddDynamic(this, &UGA_Fire::OnRelease);
			WaitInputReleaseTask->ReadyForActivation();
		}

		TickerTask->OnTick.AddDynamic(this, &UGA_FireGun::OnFullAutoTick);
		TickerTask->ReadyForActivation();
		break;

	default:
		break;
	}

}




void UGA_FireGun::OnFullAutoTick(float DeltaTime, float CurrentTime, float TimeRemaining)
{
	const int32 TimesToBurst = WeaponToFire->NumBursts;

	if (TimesToBurst <= 0)
	{
		Fire();
		return;
	}

	// Burst logic:

	if (TimesToBurst > 0 && timesBursted < TimesToBurst)
	{
		Fire();
		++timesBursted;
		return;
	}

	// No more bursts left
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_FireGun::Fire()
{
	// Check if we have enough ammo first
	if (AmmoAttributeSet->GetClipAmmo() < WeaponToFire->AmmoCost) // if we don't have enough ammo
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Not enough ammo to fire"), *FString(__FUNCTION__));

		// Handle out of ammo




		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
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

	




	// Lets finally fire
	AmmoAttributeSet->SetClipAmmo(AmmoAttributeSet->GetClipAmmo() - WeaponToFire->AmmoCost);
	BulletTraceTargetActor->StartLocation = MakeTargetLocationInfoFromOwnerSkeletalMeshComponent(TEXT("None"));		// this will take the actor info's skeletal mesh, maybe make our own in SSGameplayAbility which you can specify a skeletal mesh to use
	WaitTargetDataActorTask->ReadyForActivation();
}






void UGA_FireGun::OnRelease(float TimeHeld)
{
	// When a machine gun stops shooting
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_FireGun::OnValidData(const FGameplayAbilityTargetDataHandle& Data)
{
	if (TSubclassOf<UGameplayEffect> BulletHitEffectTSub = WeaponToFire->BulletHitEffectTSub)
	{
		ApplyGameplayEffectToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), Data, WeaponToFire->BulletHitEffectTSub, GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s(): WeaponToFire gave us an empty BulletHitEffectTSub. Make sure to fill out DefaultBulletHitEffectTSub in the weapon generator"), *FString(__FUNCTION__));
	}
	
	if (WeaponToFire->FiringMode == EWeaponFireMode::MODE_SemiAuto)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}
}
void UGA_FireGun::OnCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	// This won't ever happen for hit scans I think, but if it does we'll just end the ability I guess
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
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

	// Reset back to zero for next activation
	timesBursted = 0;

	if (ActorInfo)
	{
		if (ActorInfo->AbilitySystemComponent.Get())
		{
			//ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(FireEffectActiveHandle); // this would give us back our ammo, maybe use this for a firing state tag though
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove RunEffectActiveHande"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove RunEffectActiveHande"), *FString(__FUNCTION__));
	}


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
