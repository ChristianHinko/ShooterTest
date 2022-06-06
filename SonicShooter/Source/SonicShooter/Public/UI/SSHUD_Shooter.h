// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSHUD.h"

#include "SSHUD_Shooter.generated.h"


class USSUserWidget_Health;
class USSUserWidget_ActiveItem;



/**
 * Shooter specific HUD
 */
UCLASS()
class SONICSHOOTER_API ASSHUD_Shooter : public ASSHUD
{
	GENERATED_BODY()

public:
	ASSHUD_Shooter(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<USSUserWidget_Health> HealthWidgetTSub;
	UPROPERTY()
		TObjectPtr<UUserWidget> HealthWidget;

	// Weak Object Ptr because this is purely meant to point to Item Stack's widget - we don't want any impact on its existence
	UPROPERTY()
		TWeakObjectPtr<USSUserWidget_ActiveItem> CurrentActiveItemWidget;

protected:
	virtual void PostInitializeComponents() override;

};
