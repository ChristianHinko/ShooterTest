// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Interactable.h"
#include "Character/AbilitySystemCharacter.h"

AItem::AItem()
{
	bShouldFireSweepEvents = true;
	tickInterval = 0;
	InteractionMode = EInteractionMode::Instant;
	shouldInteractableTick = true;
}




bool AItem::CanInteract(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}








void AItem::OnInstantInteract(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Instant Interact", true, true, FLinearColor::Yellow);
}



void AItem::OnDurationInteractBegin(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnDurationInteractBegin", true, true, FLinearColor::Gray);
}
void AItem::InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime)
{
	UKismetSystemLibrary::PrintString(this, "Interacting a " + FString::SanitizeFloat(interactDuration) + "duration interactable.....\nCurrentTime=" + FString::SanitizeFloat(CurrentInteractionTime), true, true, FLinearColor::Gray);
}
void AItem::OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
	UKismetSystemLibrary::PrintString(this, "OnDurationInteractEnd", true, true, FLinearColor::Gray);
}







void AItem::OnInteractSweepInitialHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Start", true, true, FLinearColor::Green);
}
void AItem::OnInteractSweepConsecutiveHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Tick", true, true, FLinearColor::Blue);
}
void AItem::OnInteractSweepEndHitting(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "End", true, true, FLinearColor::Red);
}
