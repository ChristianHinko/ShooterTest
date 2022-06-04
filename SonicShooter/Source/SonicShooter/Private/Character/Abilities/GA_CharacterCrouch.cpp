// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterCrouch.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterCrouch::UGA_CharacterCrouch()
{
	AbilityInputID = EAbilityInputID::Crouch;
	AbilityTags.AddTag(NativeGameplayTags::Ability_Movement_Crouch);


	CancelAbilitiesWithTag.AddTag(NativeGameplayTags::Ability_Movement_Run);
}


void UGA_CharacterCrouch::OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSetThatWorks(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	Character = Cast<ACharacter>(ActorInfo->AvatarActor);
	if (Character.IsValid())
	{
		CMC = Character->GetCharacterMovement();
	}
}

bool UGA_CharacterCrouch::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!Character.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (!CMC.IsValid())
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (CMC->CanCrouchInCurrentState() == false)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Was not able to crouch in current state when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterCrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////// we've passed the checks ///////////


	CrouchingEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, CrouchingEffectTSub.GetDefaultObject(), GetAbilityLevel());

	CMC->Crouch();
}





void UGA_CharacterCrouch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}

	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterCrouch::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	CMC->UnCrouch();

	if (CMC->IsCrouching()) // if we failed to uncrouch
	{
		// Do not end this ability if we have not successfully uncrouched
		return;
	}

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchingEffectActiveHandle);






	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
