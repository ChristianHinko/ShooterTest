// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"

AItem::AItem()
{
	bShouldFireSweepEvents = true;
}

void AItem::OnInteractInstant(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnInteractInstant", true, true, FLinearColor::Gray);
}

void AItem::BeginInteractDuration(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "BeginInteractDuration", true, true, FLinearColor::Gray);
}
void AItem::InteractingTick(APawn* InteractingPawn, float DeltaTime)
{
	UKismetSystemLibrary::PrintString(this, "Interacting", true, true, FLinearColor::Gray);
}
void AItem::FinishInteractDuration(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "EndInteractDuration", true, true, FLinearColor::Gray);
}
void AItem::CancelledInteractDuration(APawn* InteractingPawn, float interactionTime)
{
	UKismetSystemLibrary::PrintString(this, "CancledInteractDuration", true, true, FLinearColor::Gray);
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
