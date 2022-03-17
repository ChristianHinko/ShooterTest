// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUD.h"

#include "HUD_Shooter.generated.h"


class UUW_Health;
class UUW_ActiveItem;



/**
 * ShooterCharacter specific HUD
 */
UCLASS()
class SONICSHOOTER_API AHUD_Shooter : public ASSHUD
{
	GENERATED_BODY()

public:
	AHUD_Shooter(const FObjectInitializer& ObjectInitializer);



	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_Health> HealthWidgetTSub;
	UPROPERTY()
		UUserWidget* HealthWidget;

	UPROPERTY()
		UUW_ActiveItem* CurrentActiveItemWidget;

protected:
	virtual void PostInitializeComponents() override;
};
