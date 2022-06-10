// Fill out your copyright notice in the Description page of Project Settings.

#include "SonicShooterModule.h"

#include "Modules/ModuleManager.h"



void FSonicShooterModule::StartupModule()
{
	UE_LOG(LogSonicShooterModule, Log, TEXT("%s() %s primary game module start up!"), ANSI_TO_TCHAR(__FUNCTION__), *FString(SONICSHOOTER_MODULE_NAME))
}

void FSonicShooterModule::ShutdownModule()
{
	UE_LOG(LogSonicShooterModule, Log, TEXT("%s() Primary game module %s shutting down."), ANSI_TO_TCHAR(__FUNCTION__), *FString(SONICSHOOTER_MODULE_NAME))
}


IMPLEMENT_PRIMARY_GAME_MODULE(FSonicShooterModule, SonicShooter, SONICSHOOTER_MODULE_NAME);
