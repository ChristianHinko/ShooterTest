// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

//#include "SonicShooter.generated.h" // if we ever need reflection in here



#define SONICSHOOTER_MODULE_NAME TEXT("SonicShooter")

/**
 * 
 */
class FSonicShooter : public IModuleInterface
{
	typedef IModuleInterface Super;

public:
	virtual bool IsGameModule() const override
	{
		return true;
	}

	static inline FSonicShooter& Get()
	{
		return FModuleManager::LoadModuleChecked<FSonicShooter>(SONICSHOOTER_MODULE_NAME);
	}
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded(SONICSHOOTER_MODULE_NAME);
	}

protected:
	//BEGIN IModuleInterface Interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//END IModuleInterface Interface

};
