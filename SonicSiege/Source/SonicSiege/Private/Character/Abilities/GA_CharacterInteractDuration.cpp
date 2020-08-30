// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterInteractDuration.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "AbilitySystem/AbilityTasks/AT_Ticker.h"


//temp
#include "Kismet\KismetSystemLibrary.h"

UGA_CharacterInteractDuration::UGA_CharacterInteractDuration()
{
	bReplicateInputDirectly = true;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.InteractDuration")));

	//NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGA_CharacterInteractDuration::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	//	Good place to cache references so we don't have to cast every time. If this event gets called too early from a GiveAbiliy(), AvatarActor will be messed up and some reason and this gets called 3 times
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
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to setup duration interact ability"), *FString(__FUNCTION__));
		return;
	}
}

bool UGA_CharacterInteractDuration::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{	
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	//if (ActorInfo && ActorInfo->IsNetAuthority())		// used to use this when ability was ServerOnly but changed it to LocalPredicted
	{
		if (!GASCharacter)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate duration interact ability"), *FString(__FUNCTION__));
			return false;
		}
		if (!GASCharacter->CurrentInteract)
		{
			if (GASCharacter->CurrentInteract->InteractionMode != EInteractionMode::Duration)
			{
				UE_LOG(LogGameplayAbility, Error, TEXT("%s() EInteractionMode was \"Instant\" when trying to activate duration interact ability. Returning false"), *FString(__FUNCTION__));
				return false;
			}
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact ability. Cancelling"), *FString(__FUNCTION__));
			return false;
		}
		if (!InteractEffectTSub)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Interact ability blueprint"), *FString(__FUNCTION__));
			return false;
		}
			
		
	}

	return true;
}

void UGA_CharacterInteractDuration::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	Interactable = GASCharacter->CurrentInteract;
	if (!Interactable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact ability. This should be an invalid state. Cancelling"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	

	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterInteractDuration::OnRelease);
	InputReleasedTask->ReadyForActivation();

	UAT_Ticker* TickerTask = UAT_Ticker::Ticker(this, Interactable->InteractDuration);
	if (!TickerTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() TickerTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	TickerTask->OnTickDelegate.AddDynamic(this, &UGA_CharacterInteractDuration::OnTick);
	TickerTask->OnFinish.AddDynamic(this, &UGA_CharacterInteractDuration::OnTickFinish);
	TickerTask->ReadyForActivation();

	InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());

	Interactable->BeginInteractDuration(GASCharacter);
}

void UGA_CharacterInteractDuration::OnTick(float DeltaTime)
{
	Interactable->InteractingTick(GASCharacter, DeltaTime);
}
void UGA_CharacterInteractDuration::OnTickFinish()
{
	InteractEndStatus = EInteractEndStatus::CallFinishEvent;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterInteractDuration::OnRelease(float TimeHeld)
{
	// Not too sure if this will result in only calling the cancel interact function in the interface. Possibility that it might also still call the Interacting function as well (which we don't want)
	timeHeld = TimeHeld;
	InteractEndStatus = EInteractEndStatus::CallCancelledEvent;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_CharacterInteractDuration::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterInteractDuration::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	if (GASCharacter && ActorInfo->AbilitySystemComponent.Get())
	{
		if (InteractEndStatus == EInteractEndStatus::CallCancelledEvent)
		{
			Interactable->CancelledInteractDuration(GASCharacter, timeHeld);
		}
		else if (InteractEndStatus == EInteractEndStatus::CallFinishEvent)
		{
			Interactable->FinishInteractDuration(GASCharacter);
		}
		
		ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Couldn't call the end interaction function on interabtable interface because Character* was NULL"), *FString(__FUNCTION__));
	}
	
	InteractEndStatus = EInteractEndStatus::NOCALL;
	timeHeld = 0;

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

