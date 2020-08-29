// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"

AItem::AItem()
{
	bShouldFireSweepEvents = true;
}

void AItem::OnInteractInstant(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnInteractInstant", true, true, FLinearColor::Yellow);
}

void AItem::BeginInteractDuration(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "BeginInteractDuration", true, true, FLinearColor::Yellow);
}
void AItem::EndInteractDuration(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "EndInteractDuration", true, true, FLinearColor::Yellow);
}

void AItem::OnInteractSweepInitialHit(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Start", true, true, FLinearColor::Green);
}
void AItem::OnInteractSweepConsecutiveHit(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Tick", true, true, FLinearColor::Blue);
}
void AItem::OnInteractSweepEndHitting(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "End", true, true, FLinearColor::Red);
}
