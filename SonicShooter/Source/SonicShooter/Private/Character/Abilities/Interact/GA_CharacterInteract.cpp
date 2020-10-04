// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Interact/GA_CharacterInteract.h"

#include "Character/ShooterCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character/AbilitySystemCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

UGA_CharacterInteract::UGA_CharacterInteract()
{

}

void UGA_CharacterInteract::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
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

	ShooterCharacter = Cast<AShooterCharacter>(ActorInfo->AvatarActor.Get());
	if (!ShooterCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL"), *FString(__FUNCTION__));
		return;
	}
}

bool UGA_CharacterInteract::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	if (!ShooterCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Character was NULL when trying to activate duration interact ability"), *FString(__FUNCTION__));
		return false;
	}
	if (!ShooterCharacter->CurrentPrioritizedInteractable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Detected nothing to interact with when activating interact duration ability. Cancelling"), *FString(__FUNCTION__));
		return false;
	}
	if (!ShooterCharacter->CurrentPrioritizedInteractable->GetCanCurrentlyBeInteractedWith())
	{
		UE_LOG(LogGameplayAbility, Log, TEXT("%s() Couldn't interact because bCanCurrentlyBeInteractedWith was false"), *FString(__FUNCTION__));
		return false;
	}
	
	return true;
}

void UGA_CharacterInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	ShooterCharacter = Cast<AShooterCharacter>(ActorInfo->AvatarActor.Get());
	if (!ShooterCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Cast to ShooterCharacter was NULL when activating an interact ability"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	Interactable = ShooterCharacter->CurrentPrioritizedInteractable;
	if (!Interactable)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Server detected nothing to interact with when activating interact duration ability. This should be an invalid state. Cancelling"), *FString(__FUNCTION__));
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	/*Your logic here... ie.
	
		//InteractEffectTSub = Interactable->GetInteractableEffectTSub();
		//if (InteractEffectTSub)
		//{
		//	InteractEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, InteractEffectTSub.GetDefaultObject(), GetAbilityLevel());
		//}
	
		//Interactable->OnDurationInteractBegin(ShooterCharacter);
	*/
}
