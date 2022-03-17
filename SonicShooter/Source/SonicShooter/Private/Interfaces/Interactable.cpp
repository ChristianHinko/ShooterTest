// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
IInteractable::IInteractable()
{
	bDurationInteractOccurring = false;
}

void IInteractable::InjectDurationInteractOccurring(bool newDurationInteractOccurring)
{
	bDurationInteractOccurring = newDurationInteractOccurring;
}

void IInteractable::InjectDetectType(EDetectType newDetectType)
{
	DetectType = newDetectType;
}





bool IInteractable::GetDurationInteractOccurring()
{
	return bDurationInteractOccurring;
}
EDetectType IInteractable::GetDetectType()
{
	return DetectType;
}









void IInteractable::OnInstantInteract(AC_Shooter* InteractingCharacter)
{
}






void IInteractable::OnDurationInteractBegin(AC_Shooter* InteractingCharacter)
{
}
void IInteractable::InteractingTick(AC_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void IInteractable::OnDurationInteractEnd(AC_Shooter* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void IInteractable::OnInitialDetect(AC_Shooter* InteractingCharacter)
{
}
void IInteractable::OnConsecutiveDetect(AC_Shooter* InteractingCharacter)
{
}
void IInteractable::OnEndDetect(AC_Shooter* InteractingCharacter)
{
}
