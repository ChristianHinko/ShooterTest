// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AbilityTasks\AT_InteractableInterfaceCaller.h"

#include "Character/AbilitySystemCharacter.h"
#include "Utilities/LogCategories.h"

UAT_InteractableInterfaceCaller::UAT_InteractableInterfaceCaller(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;

}

UAT_InteractableInterfaceCaller* UAT_InteractableInterfaceCaller::InteractableInterfaceCaller(UGameplayAbility* OwningAbility, AAbilitySystemCharacter* GASCharactor, IInteractable*& InInteract)
{
	if (!InInteract || !OwningAbility || !GASCharactor)
	{
		UE_LOG(LogGameplayTask, Error, TEXT("%s() InInteract, OwningAbility, or GASCharactor was NULL when trying activate task"), *FString(__FUNCTION__));
		return nullptr;
	}

	UAT_InteractableInterfaceCaller* MyObj = NewAbilityTask<UAT_InteractableInterfaceCaller>(OwningAbility);
	MyObj->GASCharacter = GASCharactor;
	MyObj->Interact = InInteract;
	MyObj->duration = InInteract->interactDuration;
	MyObj->tickInterval = InInteract->tickInterval;
	MyObj->skipFirstTick = InInteract->shouldSkipFirstTick;
	MyObj->shouldCallTickEvent = InInteract->shouldInteractableTick;

	return MyObj;
}

void UAT_InteractableInterfaceCaller::Activate()
{
	currentTime = 0;
	continueTimestamp = 0;
}

void UAT_InteractableInterfaceCaller::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		OnSuccessfulInteractDelegate.Broadcast(currentTime);
		return;
	}

	if (Interact != GASCharacter->CurrentInteract)	// If the character's Interaction sweep doesn't detect the same Interactable we started interacting with
	{
		OnInteractionSweepMissDelegate.Broadcast(currentTime);
	}

	if (currentTime == 0)
	{
		OnInteractionBeginDelegate.Broadcast();
	}

	if (continueTimestamp == 0 && skipFirstTick)
	{
		skipFirstTick = false;

		////
		currentTime = currentTime + DeltaTime;
		continueTimestamp = continueTimestamp + tickInterval;
		////
		return;
	}
	if (currentTime < continueTimestamp)
	{
		currentTime = currentTime + DeltaTime;
		return;
	}

	if (shouldCallTickEvent)
	{
		OnInteractTickDelegate.Broadcast(DeltaTime, currentTime);
	}

	////
	currentTime = currentTime + DeltaTime;
	continueTimestamp = continueTimestamp + tickInterval;
	////
}













FString UAT_InteractableInterfaceCaller::GetDebugString() const
{
	return FString::Printf(TEXT("InteractableInterfaceCaller"));
}
