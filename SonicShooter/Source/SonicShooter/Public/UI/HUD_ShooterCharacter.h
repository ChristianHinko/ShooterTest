// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUD.h"

#include "HUD_ShooterCharacter.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AHUD_ShooterCharacter : public ASSHUD
{
	GENERATED_BODY()

public:
	AHUD_ShooterCharacter();


	//UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	//	TSubclassOf<UUserWidget> MyWidgetTSub;
	//UUserWidget* MyWidget;

	UUserWidget* CrosshairWidget;

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
