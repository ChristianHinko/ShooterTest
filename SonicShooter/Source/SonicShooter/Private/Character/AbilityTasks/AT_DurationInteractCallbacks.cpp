// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\AbilityTasks\AT_DurationInteractCallbacks.h"

#include "Character/ShooterCharacter.h"
#include "Utilities/LogCategories.h"
#include "Subobjects/ActorComponents/InteractorComponent.h"

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
		UE_LOG(LogGameplayAbilityTask, Error, TEXT("%s() InInteract, OwningAbility, or ShooterCharacter was NULL when trying activate task"), ANSI_TO_TCHAR(__FUNCTION__));
		return nullptr;
	}

	UAT_DurationInteractCallbacks* MyObj = NewAbilityTask<UAT_DurationInteractCallbacks>(OwningAbility);
	MyObj->ShooterCharacter = ShooterCharacter;
	MyObj->Interactable = InInteract;
	MyObj->duration = InInteract->GetInteractDuration();
	MyObj->tickInterval = InInteract->GetTickInterval();
	MyObj->skipFirstTick = InInteract->GetShouldSkipFirstTick();
	MyObj->shouldCallTickEvent = InInteract->GetShouldDurationInteractableTick();

	return MyObj;
}

void UAT_DurationInteractCallbacks::Activate()
{
	currentTime = 0;
	continueTimestamp = 0;
	ENetRole role = ShooterCharacter->GetLocalRole();
	if (Interactable->GetDetectType() == EDetectType::DETECTTYPE_Overlapped)
	{
		OnPawnLeftOverlapInteractableDelegateHandle = ShooterCharacter->GetInteractorComponent()->OnElementRemovedFromFrameOverlapInteractablesStack.AddUObject(this, &UAT_DurationInteractCallbacks::OnPawnLeftOverlapInteractable);
	}
	
}

void UAT_DurationInteractCallbacks::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		ShooterCharacter->GetInteractorComponent()->OnElementRemovedFromFrameOverlapInteractablesStack.Clear();	// Only want 1 end ability callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
		OnSuccessfulInteractDelegate.Broadcast(currentTime);
		RemoveAllDelegates();
		return;
	}

	if (Interactable != ShooterCharacter->GetInteractorComponent()->CurrentPrioritizedInteractable)
	{
		if (Interactable->GetDetectType() == EDetectType::DETECTTYPE_Sweeped)		// If the character's Interaction sweep doesn't detect the same Interactable we started interacting with
		{
			ShooterCharacter->GetInteractorComponent()->OnElementRemovedFromFrameOverlapInteractablesStack.Remove(OnPawnLeftOverlapInteractableDelegateHandle);	// Only want 1 end ability callback being triggered so take away the possibility of 2 being triggered. EndAbility() should only be called once now :D
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
