// Fill out your copyright notice in the Description page of Project Settings.

#include "SonicShooter.h"

#include "Modules/ModuleManager.h"



void FSonicShooter::StartupModule()
{
	UE_LOG(LogSonicShooterModule, Log, TEXT("%s primary game module start up!"), *FString(SONICSHOOTER_MODULE_NAME))
}

void FSonicShooter::ShutdownModule()
{
	UE_LOG(LogSonicShooterModule, Log, TEXT("Primary game module %s shutting down."), *FString(SONICSHOOTER_MODULE_NAME))
}


IMPLEMENT_PRIMARY_GAME_MODULE(FSonicShooter, SonicShooter, SONICSHOOTER_MODULE_NAME);
