// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterJump.h"

#include "Character/AbilitySystemCharacter.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character/SSCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterJump::UGA_CharacterJump()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));


	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Crouch"));
	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Run"));
}


void UGA_CharacterJump::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
	if (!ActorInfo)
	{
		return;
	}
	if (!ActorInfo->AvatarActor.Get())
	{
		return;
	}


	GASCharacter = Cast<AAbilitySystemCharacter>(ActorInfo->AvatarActor.Get());
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL"), *FString(__FUNCTION__));
	}

	CMC = GASCharacter->GetSSCharacterMovementComponent();
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GetSSCharacterMovementComponent was NULL"), *FString(__FUNCTION__));
	}
}

bool UGA_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL. Returned false"), *FString(__FUNCTION__));
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


	if (CMC->CanAttemptJump() == false)
	{
		bool replicateEndAbility = true;
		if (ActivationInfo.ActivationMode != EGameplayAbilityActivationMode::Authority)
		{
			// Only server->client EndAbility replication
			replicateEndAbility = false;
		}

		EndAbility(Handle, ActorInfo, ActivationInfo, replicateEndAbility, false);
		return;
	}
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		bool replicateEndAbility = true;
		if (ActivationInfo.ActivationMode != EGameplayAbilityActivationMode::Authority)
		{
			// Only server->client EndAbility replication
			replicateEndAbility = false;
		}

		EndAbility(Handle, ActorInfo, ActivationInfo, replicateEndAbility, false);
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
