// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUD.h"

#include "HUD_ShooterCharacter.generated.h"


class UUW_Health;



/**
 * ShooterCharacter specific HUD
 */
UCLASS()
class SONICSHOOTER_API AHUD_ShooterCharacter : public ASSHUD
{
	GENERATED_BODY()

public:
	AHUD_ShooterCharacter();



	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_Health> HealthWidgetTSub;
	UUserWidget* HealthWidget;


	UUserWidget* CrosshairWidget;
	UUserWidget* AmmoWidget;

protected:
	virtual void PostInitializeComponents() override;
};
