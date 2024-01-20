// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "STUserWidget_ActiveItem.generated.h"


class USTUserWidget_Crosshair;
class USTUserWidget_Ammo;
class UTextBlock;



/**
 * Base item widget. No visuals and is meant for subclassing in BP
 */
UCLASS()
class SHOOTERTEST_API USTUserWidget_ActiveItem : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<USTUserWidget_Crosshair> CrosshairWidget;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<USTUserWidget_Ammo> AmmoWidget;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> ItemTextBlock;

public:
	USTUserWidget_ActiveItem(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, Category = "Crosshair")
		FSlateBrush CrosshairBrush;

protected:
	virtual void NativeOnInitialized() override;
};
