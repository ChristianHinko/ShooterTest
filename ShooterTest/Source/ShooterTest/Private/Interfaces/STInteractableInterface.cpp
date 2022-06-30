// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/STInteractableInterface.h"

// Add default functionality here for any ISTInteractableInterface functions that are not pure virtual.
ISTInteractableInterface::ISTInteractableInterface()
{
	bDurationInteractOccurring = false;
}

void ISTInteractableInterface::InjectDurationInteractOccurring(bool newDurationInteractOccurring)
{
	bDurationInteractOccurring = newDurationInteractOccurring;
}

void ISTInteractableInterface::InjectDetectType(ESTDetectType newDetectType)
{
	DetectType = newDetectType;
}





bool ISTInteractableInterface::GetDurationInteractOccurring()
{
	return bDurationInteractOccurring;
}
ESTDetectType ISTInteractableInterface::GetDetectType()
{
	return DetectType;
}









void ISTInteractableInterface::OnInstantInteract(ASTCharacter_Shooter* InteractingCharacter)
{
}






void ISTInteractableInterface::OnDurationInteractBegin(ASTCharacter_Shooter* InteractingCharacter)
{
}
void ISTInteractableInterface::InteractingTick(ASTCharacter_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime)
{
}
void ISTInteractableInterface::OnDurationInteractEnd(ASTCharacter_Shooter* InteractingPawn, ESTDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
}






void ISTInteractableInterface::OnInitialDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}
void ISTInteractableInterface::OnConsecutiveDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}
void ISTInteractableInterface::OnEndDetect(ASTCharacter_Shooter* InteractingCharacter)
{
}
