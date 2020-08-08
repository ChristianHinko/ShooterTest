// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "SSHUD.generated.h"



/**
 * This class is being treated as a place to manage UUserWidgets (creating or adding and removing them from viewport)
 */
UCLASS()
class SONICSIEGE_API ASSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASSHUD();

protected:
	//BEGIN AActor interface
	virtual void PostInitializeComponents() override;
	//END AActor interface

};
