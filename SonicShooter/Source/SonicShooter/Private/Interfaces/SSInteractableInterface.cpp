// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/SSInteractableInterface.h"

// Add default functionality here for any ISSInteractableInterface functions that are not pure virtual.
ISSInteractableInterface::ISSInteractableInterface()
{
	bDurationInteractOccurring = false;
}

void ISSInteractableInterface::InjectDurationInteractOccurring(bool newDurationInteractOccurring)
{
	bDurationInteractOccurring = newDurationInteractOccurring;
}

void ISSInteractableInterface::InjectDetectType(ESSDetectType newDetectType)
{
	DetectType = newDetectType;
}





bool ISSInteractableInterface::GetDurationInteractOccurring()
{
	return bDurationInteractOccurring;
}
ESSDetectType ISSInteractableInterface::GetDetectType()
{
	return DetectType;
}









void ISSInteractableInterface::OnInstantInteract(ASSCharacter_Shooter* InteractingCharacter)
{
}






void ISSInteractableInterface::OnDurationInteractBegin(ASSCharacter_Shooter* InteractingCharacter)
{
}
void ISSInteractableInterface::InteractingTick(ASSCharacter_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void ISSInteractableInterface::OnDurationInteractEnd(ASSCharacter_Shooter* InteractingPawn, ESSDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void ISSInteractableInterface::OnInitialDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}
void ISSInteractableInterface::OnConsecutiveDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}
void ISSInteractableInterface::OnEndDetect(ASSCharacter_Shooter* InteractingCharacter)
{
}
