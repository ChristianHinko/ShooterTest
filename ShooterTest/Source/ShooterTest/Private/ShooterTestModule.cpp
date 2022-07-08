// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterTestModule.h"

#include "Modules/ModuleManager.h"



void FShooterTestModule::StartupModule()
{
	UE_LOG(LogShooterTestModule, Log, TEXT("%s() Primary game module start up!"), ANSI_TO_TCHAR(__FUNCTION__))
}

void FShooterTestModule::ShutdownModule()
{
	UE_LOG(LogShooterTestModule, Log, TEXT("%s() Primary game module shutting down."), ANSI_TO_TCHAR(__FUNCTION__))
}


IMPLEMENT_PRIMARY_GAME_MODULE(FShooterTestModule, ShooterTest, TEXT("ShooterTest"));
