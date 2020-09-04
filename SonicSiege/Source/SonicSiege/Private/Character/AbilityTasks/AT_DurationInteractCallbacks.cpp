// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

#include "Character/AbilitySystemCharacter.h"
#include "Utilities/LogCategories.h"

UAT_DurationInteractCallbacks::UAT_DurationInteractCallbacks(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;

}

UAT_DurationInteractCallbacks* UAT_DurationInteractCallbacks::DurationInteractCallbacks(UGameplayAbility* OwningAbility, AAbilitySystemCharacter* GASCharactor, IInteractable*& InInteract)
{
	if (!InInteract || !OwningAbility || !GASCharactor)
	{
		UE_LOG(LogGameplayTask, Error, TEXT("%s() InInteract, OwningAbility, or GASCharactor was NULL when trying activate task"), *FString(__FUNCTION__));
		return nullptr;
	}

	UAT_DurationInteractCallbacks* MyObj = NewAbilityTask<UAT_DurationInteractCallbacks>(OwningAbility);
	MyObj->GASCharacter = GASCharactor;
	MyObj->Interact = InInteract;
	MyObj->duration = InInteract->interactDuration;
	MyObj->tickInterval = InInteract->tickInterval;
	MyObj->skipFirstTick = InInteract->bShouldSkipFirstTick;
	MyObj->shouldCallTickEvent = InInteract->bShouldInteractableTick;

	return MyObj;
}

void UAT_DurationInteractCallbacks::Activate()
{
	currentTime = 0;
	continueTimestamp = 0;
	if (Interact->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	{
		OnPawnLeftOverlapInteractableDelegateHandle = GASCharacter->OnElementRemovedFromFrameOverlapInteractablesStack.AddUObject(this, &UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable);
	}
	
}

void UAT_DurationInteractCallbacks::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		GASCharacter->OnElementRemovedFromFrameOverlapInteractablesStack.Remove(OnPawnLeftOverlapInteractableDelegateHandle);
		OnSuccessfulInteractDelegate.Broadcast(currentTime);
		RemoveAllDelegates();
		return;
	}

	if (Interact != GASCharacter->CurrentDetectedInteract)							
	{
		if (Interact->GetDetectType() == EDetectType::DETECTTYPE_Sweeped)		// If the character's Interaction sweep doesn't detect the same Interactable we started interacting with
		{
			OnInteractionSweepMissDelegate.Broadcast(currentTime);
			RemoveAllDelegates();
		}
	}

	if (currentTime == 0)
	{
		//OnInteractionBeginDelegate.Broadcast();	Currently handling this in ActivateAbility() instead of here so that we get a free prediction key for the callback
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

void UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable(IInteractable*& InteractableThePawnLeft)
{
	if (Interact == InteractableThePawnLeft)
	{
		ENetRole d = GASCharacter->GetLocalRole();
		OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);	// Only gets called on SERVER some reason when the problem described below happens. So thats a hint to that problem. Another hint is that this problem below doesn't happen at all when in single player (listen server)
		RemoveAllDelegates();
		//PROBLEM THE SYSTEM IS FACING RN: if 2 or more overlaps in framoverlapsStack and you finish the first, then leave during the next, timer keeps running and eventually completes. This only happens if implementor destroys the first interactable on success event
	}
	//if (Interact->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	//{
	//	if (GASCharacter->CurrentDetectedInteract == nullptr)
	//	{
	//		OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);
	//	}
	//	else	// There's a new overlap priority. Didn't really find use for this so commented out
	//	{
	//		//OnNewInteractionPriorityDelegate.Broadcast(currentTime);
	//		if (GASCharacter->CurrentDetectedInteract->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	//		{
	//			if (!GASCharacter->FrameOverlapInteractablesStack.Contains(Interact))
	//			{
	//				OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);
	//			}
	//		}

	//	}
	//}
}




void UAT_DurationInteractCallbacks::RemoveAllDelegates()
{
	OnInteractTickDelegate.Clear();
	OnInteractionSweepMissDelegate.Clear();
	OnCharacterLeftInteractionOverlapDelegate.Clear();
	OnNewInteractionPriorityDelegate.Clear();
	OnSuccessfulInteractDelegate.Clear();
}










FString UAT_DurationInteractCallbacks::GetDebugString() const
{
	return FString::Printf(TEXT("DurationInteractCallbacks"));
}
