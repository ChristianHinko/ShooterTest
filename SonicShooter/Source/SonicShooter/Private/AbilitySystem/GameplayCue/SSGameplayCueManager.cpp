// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayCue/SSGameplayCueManager.h"



bool USSGameplayCueManager::ShouldAsyncLoadRuntimeObjectLibraries() const
{
	// Idea: maybe check this machines memory specs to determine this ret val


	return false;
}

void USSGameplayCueManager::FlushPendingCues()
{
	Super::FlushPendingCues();


}
