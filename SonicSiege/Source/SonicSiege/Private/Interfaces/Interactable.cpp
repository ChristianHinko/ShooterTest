// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/Interactable.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.
IInteractable::IInteractable()
{
	bShouldFireSweepEvents = false;
	interactDuration = 5.f;
	tickInterval = 0;
	shouldSkipFirstTick = false;
}