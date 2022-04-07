// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/GA_Reload.h"

#include "Utilities/LogCategories.h"
#include "Utilities/SSNativeGameplayTags.h"
#include "Inventory/Item/AS_Ammo.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Subobjects/O_ClipAmmo.h"



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
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		return;
	}





}

void UGA_Reload::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);


	UArcItemStack_Gun* SourceGun = Cast<UArcItemStack_Gun>(GetCurrentSourceObject());
	if (!IsValid(SourceGun))
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s() No valid Gun when given the reload ability - ensure you are assigning the SourceObject to a GunStack when calling GiveAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}

	ClipAmmoSubobject = SourceGun->GetClipAmmoSubobject();
}
void UGA_Reload::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);


	ClipAmmoSubobject = nullptr;
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

	if (!ClipAmmoSubobject.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ClipAmmoSubobject was NULL. returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(UAS_Ammo::GetMaxClipAmmoAttribute());
	if (ClipAmmoSubobject->ClipAmmo >= MaxClipAmmo)
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Already have full ammo. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(UAS_Ammo::GetBackupAmmoAttribute());
	if (BackupAmmo <= 0)
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
	const float MaxClipAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(UAS_Ammo::GetMaxClipAmmoAttribute());
	float AmmoToMove = MaxClipAmmo - ClipAmmoSubobject->ClipAmmo;

	// Check if BackupAmmo went negative
	{
		const float BackupAmmo = ActorInfo->AbilitySystemComponent->GetNumericAttribute(UAS_Ammo::GetBackupAmmoAttribute());
		float PostBackupAmmo = BackupAmmo - AmmoToMove;
		if (PostBackupAmmo < 0)
		{
			// Make it so we don't take that much away
			AmmoToMove -= FMath::Abs(PostBackupAmmo);
		}
	}

	// Move ammo out of backup
	FGameplayEffectSpecHandle DepleteBackupAmmoSpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoEffectTSub, GetAbilityLevel());
	DepleteBackupAmmoSpecHandle.Data.Get()->SetSetByCallerMagnitude(Tag_SetByCallerBackupAmmoDepletion, -1 * AmmoToMove);

	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, DepleteBackupAmmoSpecHandle);


	// Move ammo into clip
	ClipAmmoSubobject->ClipAmmo = ClipAmmoSubobject->ClipAmmo + AmmoToMove;






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
