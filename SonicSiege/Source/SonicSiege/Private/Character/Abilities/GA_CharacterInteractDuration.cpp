// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterInteractDuration.h"

#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Interfaces/Interactable.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"

//temp
#include "Kismet\KismetSystemLibrary.h"

UGA_CharacterInteractDuration::UGA_CharacterInteractDuration()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.InteractDuration")));
	//TagAimingDownSights = FGameplayTag::RequestGameplayTag(FName("State.Character.IsAimingDownSights"));
	//ActivationOwnedTags.AddTagFast(TagAimingDownSights);

	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
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
	// Gets called on client as well for ServerOnly abilities ONLY IF bAllowRemoteActivation is true in TryActivateAbility()
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (ActorInfo && ActorInfo->IsNetAuthority() && !GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate duration interact ability"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterInteractDuration::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(this, "Interact ability activated");
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	/*FHitResult OutHit;									// make it so we can replace this with just a variable lookup
	Character->ScanForInteractables(Interactable, OutHit);	//-----------------------------------------------------------
	if (Interactable)										//-----------------------------------------------------------
	{														//-----------------------------------------------------------
															//-----------------------------------------------------------
	}*/
	/*if (!InteractEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Interact ability blueprint"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}*/

	//	Make sure we apply effect in valid prediction key window so we make sure the tag also gets applied on the client too
	//InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
	//Character->Interact();

	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate InteractDuration ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterInteractDuration::OnRelease);
	InputReleasedTask->ReadyForActivation();

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UGA_CharacterInteractDuration::OnRelease(float TimeHeld)
{
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
		//Character->StopInteracting();
		//ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(InteractEffectActiveHandle);
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Couldn't call Character->StopInteracting() because Character* was NULL"), *FString(__FUNCTION__));
	}


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

