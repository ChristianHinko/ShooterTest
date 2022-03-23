// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUD.h"

#include "HUD_Shooter.generated.h"


class UUW_Health;
class UUW_ActiveItem;



/**
 * Shooter specific HUD
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

	// Weak Object Ptr because this is purely meant to point to Item Stack's widget - we don't want any impact on its existence
	UPROPERTY()
		TWeakObjectPtr<UUW_ActiveItem> CurrentActiveItemWidget;

protected:
	virtual void PostInitializeComponents() override;

};
