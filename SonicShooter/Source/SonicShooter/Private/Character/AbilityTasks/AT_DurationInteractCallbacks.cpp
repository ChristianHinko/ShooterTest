// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

#include "Character/ShooterCharacter.h"
#include "Utilities/LogCategories.h"
#include "ActorComponents/InteractorComponent.h"

#include "Kismet/KismetSystemLibrary.h"

UAT_DurationInteractCallbacks::UAT_DurationInteractCallbacks(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;

}

UAT_DurationInteractCallbacks* UAT_DurationInteractCallbacks::DurationInteractCallbacks(UGameplayAbility* OwningAbility, AShooterCharacter* ShooterCharacter, IInteractable*& InInteract)
{
	if (!InInteract || !OwningAbility || !ShooterCharacter)
	{
		UE_LOG(LogGameplayAbilityTask, Error, TEXT("%s() InInteract, OwningAbility, or ShooterCharacter was NULL when trying activate task"), *FString(__FUNCTION__));
		return nullptr;
	}

	UAT_DurationInteractCallbacks* MyObj = NewAbilityTask<UAT_DurationInteractCallbacks>(OwningAbility);
	MyObj->ShooterCharacter = ShooterCharacter;
	MyObj->Interactable = InInteract;
	MyObj->duration = InInteract->interactDuration;
	MyObj->tickInterval = InInteract->tickInterval;
	MyObj->skipFirstTick = InInteract->bShouldSkipFirstTick;
	MyObj->shouldCallTickEvent = InInteract->bShouldDurationInteractableTick;

	return MyObj;
}

void UAT_DurationInteractCallbacks::Activate()
{
	currentTime = 0;
	continueTimestamp = 0;
	ENetRole role = ShooterCharacter->GetLocalRole();
	if (Interactable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	{
		OnPawnLeftOverlapInteractableDelegateHandle = ShooterCharacter->Interactor->OnElementRemovedFromFrameOverlapInteractablesStack.AddUObject(this, &UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable);
	}
	
}

void UAT_DurationInteractCallbacks::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		ShooterCharacter->Interactor->OnElementRemovedFromFrameOverlapInteractablesStack.Clear();	// Only want 1 end ability callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
		OnSuccessfulInteractDelegate.Broadcast(currentTime);
		RemoveAllDelegates();
		return;
	}

	if (Interactable != ShooterCharacter->Interactor->CurrentPrioritizedInteractable)
	{
		if (Interactable->GetDetectType() == EDetectType::DETECTTYPE_Sweeped)		// If the character's Interaction sweep doesn't detect the same Interactable we started interacting with
		{
			ShooterCharacter->Interactor->OnElementRemovedFromFrameOverlapInteractablesStack.Remove(OnPawnLeftOverlapInteractableDelegateHandle);	// Only want 1 end ability callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
			OnInteractionSweepMissDelegate.Broadcast(currentTime);
			RemoveAllDelegates();
			return;
		}
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

void UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable(IInteractable*& InteractableThePawnLeft)
{
	ENetRole role = ShooterCharacter->GetLocalRole();
	if (Interactable == InteractableThePawnLeft)
	{
		ENetRole d = ShooterCharacter->GetLocalRole();
		OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);
		RemoveAllDelegates();
	}
	//if (Interactable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	//{
	//	if (ShooterCharacter->CurrentPrioritizedInteractable == nullptr)
	//	{
	//		OnCharacterLeftInteractionOverlapDelegate.Broadcast(currentTime);
	//	}
	//	else	// There's a new overlap priority. Didn't really find use for this so commented out
	//	{
	//		//OnNewInteractionPriorityDelegate.Broadcast(currentTime);
	//		if (ShooterCharacter->CurrentPrioritizedInteractable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	//		{
	//			if (!ShooterCharacter->CurrentOverlapInteractablesStack.Contains(Interactable))
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
	ENetRole d = ShooterCharacter->GetLocalRole();
	Super::OnDestroy(AbilityEnded);

}
