// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/SSGameplayAbility_Reload.h"

#include "Inventory/Item/SSAttributeSet_Ammo.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Subobjects/SSObject_ClipAmmo.h"



USSGameplayAbility_Reload::USSGameplayAbility_Reload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESSAbilityInputID::Reload;
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Reload);
}

void USSGameplayAbility_Reload::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}

}

void USSGameplayAbility_Reload::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	USSItemStack_Gun* SourceGun = Cast<USSItemStack_Gun>(GetCurrentSourceObject());
	if (!IsValid(SourceGun))
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() No valid Gun when given the reload ability - ensure you are assigning the SourceObject to a GunStack when calling GiveAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	ClipAmmoSubobject = SourceGun->GetClipAmmoSubobject();
}
void USSGameplayAbility_Reload::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);


	ClipAmmoSubobject = nullptr;
}

bool USSGameplayAbility_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}


	if (!DepleteBackupAmmoEffectTSub)
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() DepleteBackupAmmoEffectTSub was NULL. Returned false. - Please fill out blueprint TSubs"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (!ClipAmmoSubobject.IsValid())
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() ClipAmmoSubobject was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USSAttributeSet_Ammo::GetMaxClipAmmoAttribute());
	if (ClipAmmoSubobject->ClipAmmo >= MaxClipAmmo)
	{
		UE_LOG(LogSSGameplayAbility, Log, TEXT("%s() Already have full ammo. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USSAttributeSet_Ammo::GetBackupAmmoAttribute());
	if (BackupAmmo <= 0)
	{
		UE_LOG(LogSSGameplayAbility, Log, TEXT("%s() No backup ammo to use to reload. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}


	return true;
}

void USSGameplayAbility_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
		UE_LOG(LogSSGameplayAbility, Warning, TEXT("ReloadingEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
	}


	// Amount to move out of BackupAmmo, and into ClipAmmo
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USSAttributeSet_Ammo::GetMaxClipAmmoAttribute());
	float AmmoToMove = MaxClipAmmo - ClipAmmoSubobject->ClipAmmo;

	// Check if BackupAmmo went negative
	{
		const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(USSAttributeSet_Ammo::GetBackupAmmoAttribute());
		float PostBackupAmmo = BackupAmmo - AmmoToMove;
		if (PostBackupAmmo < 0)
		{
			// Make it so we don't take that much away
			AmmoToMove -= FMath::Abs(PostBackupAmmo);
		}
	}

	// Move ammo out of backup
	FGameplayEffectSpecHandle DepleteBackupAmmoSpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoEffectTSub, GetAbilityLevel());
	DepleteBackupAmmoSpecHandle.Data.Get()->SetSetByCallerMagnitude(SSNativeGameplayTags::SetByCaller_BackupAmmoDepletion, -1 * AmmoToMove);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoSpecHandle);


	// Move ammo into clip
	ClipAmmoSubobject->ClipAmmo = ClipAmmoSubobject->ClipAmmo + AmmoToMove;






	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}




void USSGameplayAbility_Reload::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ReloadingEffectActiveHandle);

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
