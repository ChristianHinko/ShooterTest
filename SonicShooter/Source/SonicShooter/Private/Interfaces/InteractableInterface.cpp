// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InteractableInterface.h"

// Add default functionality here for any IInteractableInterface functions that are not pure virtual.
IInteractableInterface::IInteractableInterface()
{
	bDurationInteractOccurring = false;
}

void IInteractableInterface::InjectDurationInteractOccurring(bool newDurationInteractOccurring)
{
	bDurationInteractOccurring = newDurationInteractOccurring;
}

void IInteractableInterface::InjectDetectType(EDetectType newDetectType)
{
	DetectType = newDetectType;
}





bool IInteractableInterface::GetDurationInteractOccurring()
{
	return bDurationInteractOccurring;
}
EDetectType IInteractableInterface::GetDetectType()
{
	return DetectType;
}









void IInteractableInterface::OnInstantInteract(AC_Shooter* InteractingCharacter)
{
}






void IInteractableInterface::OnDurationInteractBegin(AC_Shooter* InteractingCharacter)
{
}
void IInteractableInterface::InteractingTick(AC_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void IInteractableInterface::OnDurationInteractEnd(AC_Shooter* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void IInteractableInterface::OnInitialDetect(AC_Shooter* InteractingCharacter)
{
}
void IInteractableInterface::OnConsecutiveDetect(AC_Shooter* InteractingCharacter)
{
}
void IInteractableInterface::OnEndDetect(AC_Shooter* InteractingCharacter)
{
}
