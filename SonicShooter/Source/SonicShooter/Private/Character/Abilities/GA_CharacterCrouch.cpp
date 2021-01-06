// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterCrouch.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "AbilitySystem\AbilityTasks\AT_WaitInputPressCust.h"
#include "AbilitySystem\AbilityTasks\AT_WaitInputReleaseCust.h"
#include "Character/SSCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_CharacterCrouch::UGA_CharacterCrouch()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Crouch")));


	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Run"));
	//NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UGA_CharacterCrouch::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL"), *FString(__FUNCTION__));
	}
}

bool UGA_CharacterCrouch::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
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

	return true;
}

void UGA_CharacterCrouch::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (CMC->GetToggleCrouchEnabled())
	{
		InputPressTask = UAT_WaitInputPressCust::WaitInputPressCust(this, false, true);
		if (!InputPressTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputPressTask was NULL when trying to activate crouch ability. Called EndAbility()"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		InputPressTask->OnPress.AddDynamic(this, &UGA_CharacterCrouch::OnPress);
	}
	else
	{
		InputReleasedTask = UAT_WaitInputReleaseCust::WaitInputReleaseCust(this, false, true);
		if (!InputReleasedTask)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate crouch ability. Called EndAbility()"), *FString(__FUNCTION__));
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterCrouch::OnRelease);
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		bool replicateEndAbility = true;
		if (ActivationInfo.ActivationMode != EGameplayAbilityActivationMode::Authority)
		{
			// Only server->client EndAbility replication
			replicateEndAbility = false;
		}

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), replicateEndAbility, false);
		return;
	}
	///////////////////////// we've passed the checks ///////////


	OnWantsToCrouchChangedDelegateHandle = CMC->OnWantsToCrouchChanged.AddUObject(this, &UGA_CharacterCrouch::OnWantsToCrouchChanged);


	if (CMC->GetToggleCrouchEnabled())
	{
		InputPressTask->ReadyForActivation();
	}
	else
	{
		InputReleasedTask->ReadyForActivation();
	}

	CrouchingEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, CrouchingEffectTSub.GetDefaultObject(), GetAbilityLevel());
	GASCharacter->Crouch();
}


void UGA_CharacterCrouch::OnWantsToCrouchChanged(bool newWantsToCrouch)
{
	if (newWantsToCrouch == false)
	{
		bool replicateEndAbility = true;
		if (GetCurrentActivationInfo().ActivationMode != EGameplayAbilityActivationMode::Authority)
		{
			// Only server->client EndAbility replication
			replicateEndAbility = false;
		}

		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), replicateEndAbility, false);
	}
}



void UGA_CharacterCrouch::OnRelease(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterCrouch::OnPress(float TimeElapsed)
{
	if (InputPressTask->callBackNumber > 1)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}












void UGA_CharacterCrouch::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (bWasCancelled == false)
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
		




		CMC->OnWantsToCrouchChanged.Remove(OnWantsToCrouchChangedDelegateHandle);
		GASCharacter->UnCrouch();
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchingEffectActiveHandle);







		Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
}
