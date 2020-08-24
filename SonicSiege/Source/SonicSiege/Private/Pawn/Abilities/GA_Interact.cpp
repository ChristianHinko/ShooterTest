// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Abilities/GA_Interact.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"

UGA_Interact::UGA_Interact()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Interact")));

	//TagAimingDownSights = FGameplayTag::RequestGameplayTag(FName("State.Character.IsAimingDownSights"));
	//ActivationOwnedTags.AddTagFast(TagAimingDownSights);
}


bool UGA_Interact::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}




	return true;
}

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	/*if (!InteractEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Interact ability blueprint"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}*/
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Character was NULL when trying to activate Interact ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate Interact ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}

	//	Make sure we apply effect in valid prediction key window so we make sure the tag also gets applied on the client too
	//InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
	//Character->Interact();

	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_Interact::OnRelease);
	InputReleasedTask->ReadyForActivation();
}

void UGA_Interact::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	}
}

void UGA_Interact::OnRelease(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);	// no need to replicate, server runs this too
}

void UGA_Interact::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_Interact::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	if (ActorInfo)
	{
		ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
		if (Character && ActorInfo->AbilitySystemComponent.Get())
		{
			//Character->StopInteracting();
			//ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Couldn't call Character->StopInteracting() because Character* was NULL"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove InteractEffectActiveHande and when trying to call StopInteracting on the character"), *FString(__FUNCTION__));
	}


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
