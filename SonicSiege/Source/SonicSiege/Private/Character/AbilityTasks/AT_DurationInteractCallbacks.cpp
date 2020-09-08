// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

#include "Character/AbilitySystemCharacter.h"
#include "Utilities/LogCategories.h"

#include "Kismet/KismetSystemLibrary.h"

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
	ENetRole role = GASCharacter->GetLocalRole();
	if (Interact->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	{
		OnPawnLeftOverlapInteractableDelegateHandle = GASCharacter->OnElementRemovedFromFrameOverlapInteractablesStack.AddUObject(this, &UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable);
	}
	
}

void UAT_DurationInteractCallbacks::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		GASCharacter->OnElementRemovedFromFrameOverlapInteractablesStack.Remove(OnPawnLeftOverlapInteractableDelegateHandle);	// Only want 1 callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
		OnSuccessfulInteractDelegate.Broadcast(currentTime);
		RemoveAllDelegates();
		return;
	}

	if (Interact != GASCharacter->CurrentDetectedInteract)							
	{
		if (Interact->GetDetectType() == EDetectType::DETECTTYPE_Sweeped)		// If the character's Interaction sweep doesn't detect the same Interactable we started interacting with
		{

			GASCharacter->OnElementRemovedFromFrameOverlapInteractablesStack.Remove(OnPawnLeftOverlapInteractableDelegateHandle);	// Only want 1 callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
			OnInteractionSweepMissDelegate.Broadcast(currentTime);
			RemoveAllDelegates();
			return;
		}
	}

	if (currentTime == 0)
	{
		//OnInteractionBeginDelegate.Broadcast();	Currently handling this in ActivateAbility() instead of here so that we get a free prediction key for the callback
	}

	if (skipFirstTick && continueTimestamp == 0)
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

// Updtae: Turns out client was actually in the wrong, but only for this specific problem where the timer on the client keeps ticking. This is happening because this event isn't being called on client some reason. Also found another anoying problem. Weird case where ability keeps activating and getting rejected every tick after a successful interact D:
// Update: Fixed the problem with EndAbility() being called twice, but that wasn't the problem of the task on the client remaining to tick.
// Update: Turns out I was thinking about things in the wrong way. Interactable's OnDurationInteractEnded() should only be called once, not twice (like Success and LeftInteractableOverlap, like the server is doing). So I was thinking the wrong thing this whole time. The server is in the wrong and the client (who is only calling OnDurationInteractEnded() once) is correct. This means server is some reason calling EndAbility() twice. Anyway, after I fix that problem I should make it so that this ability supports the developer calling Destroy() from within OnDurationInteractEnded() with a reason of Success (i think I should)
void UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable(IInteractable*& InteractableThePawnLeft)	// Somehow this is not being called on the client so client's timer keeps running	
{
	ENetRole role = GASCharacter->GetLocalRole();
	if (Interact == InteractableThePawnLeft)
	{
		ENetRole d = GASCharacter->GetLocalRole();
		OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);	// Only gets called on SERVER some reason when the problem described below happens. So thats a hint to that problem. Another hint is that this problem below doesn't happen at all when in single player (listen server)
		//RemoveAllDelegates();
		//PROBLEM THE SYSTEM IS FACING RN: if 2 or more overlaps in framoverlapsStack and you finish the first, then leave during the next, timer keeps running and eventually completes and destroys the interactable. If all interactables are is same position and size the false timer one doesn't get destroyed some reason. This only happens if implementor destroys the first interactable on success event
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

void UAT_DurationInteractCallbacks::OnDestroy(bool AbilityEnded)
{
	ENetRole d = GASCharacter->GetLocalRole();
	Super::OnDestroy(AbilityEnded);

}
