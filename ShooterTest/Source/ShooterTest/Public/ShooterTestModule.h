// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

//#include "ShooterTestModule.generated.h" // if we ever need reflection in here



#define SHOOTERTEST_MODULE_NAME TEXT("ShooterTest")

/**
 * 
 */
class FShooterTestModule : public IModuleInterface
{
public:
	virtual bool IsGameModule() const override
	{
		return true;
	}

	static inline FShooterTestModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FShooterTestModule>(SHOOTERTEST_MODULE_NAME);
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(SHOOTERTEST_MODULE_NAME);
	}

protected:
	//BEGIN IModuleInterface Interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//END IModuleInterface Interface

};
