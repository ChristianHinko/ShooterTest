// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/STGameplayAbility_Reload.h"

#include "Inventory/Item/STAttributeSet_Ammo.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Modular/ArcItemStackModular.h"
#include "Inventory/Item/Fragments/STItemFragment_ClipAmmo.h"



USTGameplayAbility_Reload::USTGameplayAbility_Reload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityTags.AddTag(STNativeGameplayTags::InputAction_Reload);
	AbilityTags.AddTag(STNativeGameplayTags::Ability_Reload);
}

void USTGameplayAbility_Reload::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}

}

void USTGameplayAbility_Reload::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	UArcItemStackModular* SourceGun = Cast<UArcItemStackModular>(GetCurrentSourceObject());
	if (!IsValid(SourceGun))
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() No valid Gun when given the reload ability - ensure you are assigning the SourceObject to a GunStack when calling GiveAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	ClipAmmoItemFragment = SourceGun->FindFirstFragment<USTItemFragment_ClipAmmoInstanced>();
}
void USTGameplayAbility_Reload::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);


	ClipAmmoItemFragment = nullptr;
}

bool USTGameplayAbility_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}


	if (!DepleteBackupAmmoEffectTSub)
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() DepleteBackupAmmoEffectTSub was NULL. Returned false. - Please fill out blueprint TSubs"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!ClipAmmoItemFragment.IsValid())
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() ClipAmmoItemFragment was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USTAttributeSet_Ammo::GetMaxClipAmmoAttribute());
	if (ClipAmmoItemFragment->ClipAmmo >= MaxClipAmmo)
	{
		UE_LOG(LogSTGameplayAbility, Log, TEXT("%s() Already have full ammo. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USTAttributeSet_Ammo::GetBackupAmmoAttribute());
	if (BackupAmmo <= 0)
	{
		UE_LOG(LogSTGameplayAbility, Log, TEXT("%s() No backup ammo to use to reload. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}

void USTGameplayAbility_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
		UE_LOG(LogSTGameplayAbility, Warning, TEXT("ReloadingEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
	}


	// Amount to move out of BackupAmmo, and into ClipAmmo
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USTAttributeSet_Ammo::GetMaxClipAmmoAttribute());
	float AmmoToMove = MaxClipAmmo - ClipAmmoItemFragment->ClipAmmo;

	// Check if BackupAmmo went negative
	{
		const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USTAttributeSet_Ammo::GetBackupAmmoAttribute());
		float PostBackupAmmo = BackupAmmo - AmmoToMove;
		if (PostBackupAmmo < 0)
		{
			// Make it so we don't take that much away
			AmmoToMove -= FMath::Abs(PostBackupAmmo);
		}
	}

	// Move ammo out of backup
	FGameplayEffectSpecHandle DepleteBackupAmmoSpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoEffectTSub, GetAbilityLevel());
	DepleteBackupAmmoSpecHandle.Data.Get()->SetSetByCallerMagnitude(STNativeGameplayTags::SetByCaller_BackupAmmoDepletion, -1 * AmmoToMove);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoSpecHandle);


	// Move ammo into clip
	ClipAmmoItemFragment->ClipAmmo = ClipAmmoItemFragment->ClipAmmo + AmmoToMove;






	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}




void USTGameplayAbility_Reload::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ReloadingEffectActiveHandle);

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
