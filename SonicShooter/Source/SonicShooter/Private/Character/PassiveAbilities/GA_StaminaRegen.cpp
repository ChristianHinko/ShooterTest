// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PassiveAbilities/GA_StaminaRegen.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Character/AbilityTasks/AT_StaminaRegen.h"
#include "Kismet/KismetSystemLibrary.h"

UGA_StaminaRegen::UGA_StaminaRegen()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	TagHasMaxStamina = FGameplayTag::RequestGameplayTag(FName("Character.State.HasMaxStamina"));
	TagIsRunning = FGameplayTag::RequestGameplayTag(FName("Character.State.IsRunning"));
	//TagIsRegeningStamina = FGameplayTag::RequestGameplayTag(FName("Character.State.IsRegeningStamina"));

	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Passive.StaminaRegen")));

	ActivateAbilityOnGrant = true;

	TickTimerDel.BindUObject(this, &UGA_StaminaRegen::OnTimerTick);
}




bool UGA_StaminaRegen::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UGA_StaminaRegen::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//	This ability only gets activated once and exists throughout the lifetime of the avatar (or at least should exist until the avatar dies).
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}
	if (!StaminaGainEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s  the efftect StaminaGainEffectTSub was NULL so this ability was canceled - please fill out StaminaGainEffectTSub in the StaminaRegen ability blueprint"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}
	GASCharacter = Cast<AAbilitySystemCharacter>(GetAvatarActorFromActorInfo());
	if (!GASCharacter)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		UE_LOG(LogGameplayAbility, Error, TEXT("%s failed to get reference to GASCharacter. Stamina will not regen D:"), *FString(__FUNCTION__));
		return;
	}
	CharacterAttributeSet = GASCharacter->GetCharacterAttributeSet();
	if (CharacterAttributeSet)
	{
		ActorInfo->AbilitySystemComponent.Get()->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetStaminaAttribute()).AddUObject(this, &UGA_StaminaRegen::OnStaminaAttributeChange);

	}



}

void UGA_StaminaRegen::OnStaminaAttributeChange(const FOnAttributeChangeData& Data)
{
	float oldValue = Data.OldValue;
	float newValue = Data.NewValue;

	if (oldValue > 0.f && newValue < oldValue && newValue < CharacterAttributeSet->GetMaxStamina())
	{
		if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
		{
			//if (ASC->HasMatchingGameplayTag(TagIsRegeningStamina) == false && ASC->HasMatchingGameplayTag(TagHasMaxStamina) == false && ASC->HasMatchingGameplayTag(TagIsRunning) == false)
			//{
			//	// Then create new prediction key

			//	GetWorld()->GetTimerManager().SetTimer(TickTimerHandle, TickTimerDel, 1.f, true, 0.f);
			//}
		}
		return;
	}

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().IsTimerActive(TickTimerHandle);
	}
}








void UGA_StaminaRegen::OnTimerTick()
{
	//	TODO: Make sure we apply effect in valid prediction key window
	ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), StaminaGainEffectTSub.GetDefaultObject(), GetAbilityLevel());
}

void UGA_StaminaRegen::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_StaminaRegen::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Rejected)
	{
		UKismetSystemLibrary::PrintString(this, "Rollback Occured", true, false, FLinearColor::Red);
	}

	// Lets do the logic we want to happen when the ability ends. If you want you can do an async task,
	// but just make sure you don't call Super::EndAbility until after the task ends (call Super::EndAbility in the task's callback)
	// Clear ALL timers that belong to this (Actor) instance.
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	TickTimerDel.Unbind();









	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
















void UGA_StaminaRegen::BeginDestroy()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}

	Super::BeginDestroy();
}

















/*
#pragma region Debug Prediction
if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Authority)
{
	UKismetSystemLibrary::PrintString(this, "Authority");
}
if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Confirmed)
{
	UKismetSystemLibrary::PrintString(this, "Confirmed");
}
if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::NonAuthority)
{
	UKismetSystemLibrary::PrintString(this, "NonAuthority");
}
if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Predicting)
{
	UKismetSystemLibrary::PrintString(this, "Predicting");
}
if (ActivationInfo.ActivationMode == EGameplayAbilityActivationMode::Rejected)
{
	UKismetSystemLibrary::PrintString(this, "Rejected");
}

if (ActivationInfo.GetActivationPredictionKey().IsValidForMorePrediction())
{
	UKismetSystemLibrary::PrintString(this, "Valid");
}
else
{
	UKismetSystemLibrary::PrintString(this, "invalid");
}
#pragma endregion
*/