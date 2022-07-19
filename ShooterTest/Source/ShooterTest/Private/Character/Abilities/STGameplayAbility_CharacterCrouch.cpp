// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/STGameplayAbility_CharacterCrouch.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "Utilities/ASSNativeGameplayTags.h"

#include "Kismet/KismetSystemLibrary.h"



USTGameplayAbility_CharacterCrouch::USTGameplayAbility_CharacterCrouch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityTags.AddTag(STNativeGameplayTags::Ability_Movement_Crouch);
	AbilityTags.AddTag(ASSNativeGameplayTags::Ability_Type_DisableAutoActivationFromInput);
	AbilityTags.AddTag(STNativeGameplayTags::InputAction_Crouch);

	CancelAbilitiesWithTag.AddTag(STNativeGameplayTags::Ability_Movement_Run);
}


void USTGameplayAbility_CharacterCrouch::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

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

bool USTGameplayAbility_CharacterCrouch::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!Character.IsValid())
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Character was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (!CMC.IsValid())
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (CMC->CanCrouchInCurrentState() == false)
	{
		UE_LOG(LogSTGameplayAbility, Warning, TEXT("%s() Was not able to crouch in current state when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void USTGameplayAbility_CharacterCrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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





void USTGameplayAbility_CharacterCrouch::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CMC->UnCrouch();

	if (CMC->IsCrouching()) // if we failed to uncrouch
	{
		// Do not end this ability if we have not successfully uncrouched
		return;
	}

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchingEffectActiveHandle);



	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
