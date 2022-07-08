// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//#include "ShooterTestModule.generated.h" // uncomment if we need reflection in here



/**
 * Shooter Test module
 */
class FShooterTestModule : public FDefaultGameModuleImpl
{
public:
	//  BEGIN IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//  END IModuleInterface interface
};
