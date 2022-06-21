// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SSGameInstance.h"

#include "SettingsManager.h"



void USSGameInstance::Init()
{
	USettingsManager::RegisterBoolCVarSetting(TEXT("input.ToggleRun"), true, TEXT("Running is a toggle"));
	USettingsManager::RegisterBoolCVarSetting(TEXT("input.ToggleCrouch"), true, TEXT("Crouching is a toggle"));


	Super::Init();
}
