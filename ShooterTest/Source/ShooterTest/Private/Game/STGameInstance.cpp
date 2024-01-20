// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/STGameInstance.h"

#include "SettingsManager.h"



void USTGameInstance::Init()
{
	check(USettingsManager::Get());
	USettingsManager::RegisterBoolCVarSetting(TEXT("input.ToggleRun"), true, TEXT("Running is a toggle"));
	USettingsManager::RegisterBoolCVarSetting(TEXT("input.ToggleCrouch"), true, TEXT("Crouching is a toggle"));


	Super::Init();
}
