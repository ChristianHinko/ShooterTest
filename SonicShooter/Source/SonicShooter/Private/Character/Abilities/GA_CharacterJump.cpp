// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterJump.h"

#include "Character/SSCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterJump::UGA_CharacterJump()
{
	AbilityInputID = EAbilityInputID::Jump;
	AbilityTags.AddTag(NativeGameplayTags::Ability_Movement_Jump);


	CancelAbilitiesWithTag.AddTag(NativeGameplayTags::Ability_Movement_Crouch);
	CancelAbilitiesWithTag.AddTag(NativeGameplayTags::Ability_Movement_Run);
}


void UGA_CharacterJump::OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSetThatWorks(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}

}

bool UGA_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!IsValid(Character))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (Character->CanJump() == false)
	{
		UE_LOG(LogGameplayAbility, Verbose, TEXT("%s() Was not able to jump when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
	if (!IsValid(CMC))
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to activate ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
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
		UE_LOG(LogGameplayAbility, Warning, TEXT("JumpEffectTSub empty in %s - please fill out Character Jump ability blueprint"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	CMC->DoJump(false);
}



void UGA_CharacterJump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterJump::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}


	if (const FSSGameplayAbilityActorInfo* SSActorInfo = static_cast<const FSSGameplayAbilityActorInfo*>(ActorInfo))
	{
		if (USSCharacterMovementComponent* CMC = SSActorInfo->SSCharacterMovementComponent.Get())
		{
			CMC->UnJump();
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to UnJump"), ANSI_TO_TCHAR(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() SSActorInfo was NULL when trying to UnJump"), ANSI_TO_TCHAR(__FUNCTION__));
	}

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(JumpEffectActiveHandle);


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
