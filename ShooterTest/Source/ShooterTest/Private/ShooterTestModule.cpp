// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterTestModule.h"

#include "Modules/ModuleManager.h"



void FShooterTestModule::StartupModule()
{
	UE_LOG(LogShooterTestModule, Log, TEXT("%s() %s primary game module start up!"), ANSI_TO_TCHAR(__FUNCTION__), *FString(SHOOTERTEST_MODULE_NAME))
}

void FShooterTestModule::ShutdownModule()
{
	UE_LOG(LogShooterTestModule, Log, TEXT("%s() Primary game module %s shutting down."), ANSI_TO_TCHAR(__FUNCTION__), *FString(SHOOTERTEST_MODULE_NAME))
}


IMPLEMENT_PRIMARY_GAME_MODULE(FShooterTestModule, ShooterTest, SHOOTERTEST_MODULE_NAME);
