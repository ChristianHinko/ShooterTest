// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GA_Reload.h"

#include "Utilities/LogCategories.h"
#include "Utilities/SSNativeGameplayTags.h"
#include "Item/AS_Ammo.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_Reload::UGA_Reload()
{
	AbilityInputID = EAbilityInputID::Reload;
	AbilityTags.AddTag(Tag_ReloadAbility);
}

void UGA_Reload::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
	Super::OnAvatarSet(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}
	//AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!ActorInfo->AvatarActor.Get()/*AvatarActor*/)
	{
		return;
	}





}

void UGA_Reload::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


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
void UGA_Reload::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);


	AmmoAttributeSet = nullptr;
}

bool UGA_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}


	if (!DepleteBackupAmmoEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() DepleteBackupAmmoEffectTSub was NULL. Returned false. - Please fill out blueprint TSubs"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!AmmoAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() AmmoAttributeSet was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (AmmoAttributeSet->ClipAmmo >= AmmoAttributeSet->GetMaxClipAmmo())
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Already have full ammo. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (AmmoAttributeSet->GetBackupAmmo() <= 0)
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() No backup ammo to use to reload. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}

void UGA_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);



	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (ReloadingEffectTSub)
	{
		ReloadingEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, ReloadingEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("ReloadingEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
	}


	// Amount to move out of BackupAmmo, and into ClipAmmo
	float AmmoToMove = AmmoAttributeSet->GetMaxClipAmmo() - AmmoAttributeSet->ClipAmmo;

	// Check if BackupAmmo went negative
	{
		float postBackupAmmo = AmmoAttributeSet->GetBackupAmmo() - AmmoToMove;
		if (postBackupAmmo < 0)
		{
			// Make it so we don't take that much away
			AmmoToMove -= FMath::Abs(postBackupAmmo);
		}
	}

	// Move ammo out of backup
	FGameplayEffectSpecHandle DepleteBackupAmmoSpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoEffectTSub, GetAbilityLevel());
	DepleteBackupAmmoSpecHandle.Data.Get()->SetSetByCallerMagnitude(Tag_SetByCallerBackupAmmoDepletion, -1 * AmmoToMove);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoSpecHandle);


	// Move ammo into clip
	AmmoAttributeSet->ClipAmmo = AmmoAttributeSet->ClipAmmo + AmmoToMove;






	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}




void UGA_Reload::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}

	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_Reload::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}




	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ReloadingEffectActiveHandle);




	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
