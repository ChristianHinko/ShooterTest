// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/STHUD.h"

#include "STHUD_Shooter.generated.h"


class USTUserWidget_Health;



/**
 * Shooter specific HUD
 */
UCLASS()
class SHOOTERTEST_API ASTHUD_Shooter : public ASTHUD
{
    GENERATED_BODY()

public:
    ASTHUD_Shooter(const FObjectInitializer& ObjectInitializer);


    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
        TSubclassOf<USTUserWidget_Health> HealthWidgetTSub;
    UPROPERTY()
        TObjectPtr<UUserWidget> HealthWidget;

    // Weak Object Ptr because this is purely meant to point to Item Stack's widget - we don't want any impact on its existence
    UPROPERTY()
        TWeakObjectPtr<UUserWidget> CurrentActiveItemWidget;

protected:
    virtual void PostInitializeComponents() override;

};
