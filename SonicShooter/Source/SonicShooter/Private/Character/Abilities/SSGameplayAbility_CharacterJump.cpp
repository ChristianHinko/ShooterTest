// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/SSGameplayAbility_CharacterJump.h"

#include "Character/SSCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Kismet/KismetSystemLibrary.h"



USSGameplayAbility_CharacterJump::USSGameplayAbility_CharacterJump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESSAbilityInputID::Jump;
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Movement_Jump);


	CancelAbilitiesWithTag.AddTag(SSNativeGameplayTags::Ability_Movement_Crouch);
	CancelAbilitiesWithTag.AddTag(SSNativeGameplayTags::Ability_Movement_Run);
}


void USSGameplayAbility_CharacterJump::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
}

bool USSGameplayAbility_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!IsValid(Character))
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() Character was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (Character->CanJump() == false)
	{
		UE_LOG(LogSSGameplayAbility, Verbose, TEXT("%s() Was not able to jump when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void USSGameplayAbility_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
	if (!IsValid(CMC))
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to activate ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////// we've passed the checks ///////////


	//	Make sure we apply effect in valid prediction key window so we make sure the tag also gets applied on the client too
	if (JumpEffectTSub)
	{
		JumpEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, JumpEffectTSub.GetDefaultObject(), GetAbilityLevel());
	}
	else
	{
		UE_LOG(LogSSGameplayAbility, Warning, TEXT("JumpEffectTSub empty in %s - please fill out Character Jump ability blueprint"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	CMC->DoJump(false);
}



void USSGameplayAbility_CharacterJump::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (const FSSGameplayAbilityActorInfo* SSActorInfo = static_cast<const FSSGameplayAbilityActorInfo*>(ActorInfo))
	{
		if (USSCharacterMovementComponent* CMC = SSActorInfo->SSCharacterMovementComponent.Get())
		{
			CMC->UnJump();
		}
		else
		{
			UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to UnJump"), ANSI_TO_TCHAR(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() SSActorInfo was NULL when trying to UnJump"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(JumpEffectActiveHandle);


	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
