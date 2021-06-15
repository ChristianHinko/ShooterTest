// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterJump.h"

#include "Character/SSCharacter.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character/SSCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterJump::UGA_CharacterJump()
{
	AbilityInputID = EAbilityInputID::Jump;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Jump")));


	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Movement.Crouch"));
	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Movement.Run"));
}


void UGA_CharacterJump::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	TryCallOnAvatarSetOnPrimaryInstance
		Super::OnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		return;
	}


	SSCharacter = Cast<ASSCharacter>(AvatarActor);
	if (SSCharacter)
	{
		CMC = SSCharacter->GetSSCharacterMovementComponent();
		if (!CMC)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() GetCharacterMovement was NULL"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() SSCharacter was NULL"), *FString(__FUNCTION__));
	}
}

bool UGA_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!SSCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() SSCharacter was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	if (CMC->CanAttemptJump() == false)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Was not able to jump when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


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
		UE_LOG(LogGameplayAbility, Warning, TEXT("JumpEffectTSub empty in %s - please fill out Character Jump ability blueprint"), *FString(__FUNCTION__));
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

	CMC->UnJump();

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(JumpEffectActiveHandle);


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
