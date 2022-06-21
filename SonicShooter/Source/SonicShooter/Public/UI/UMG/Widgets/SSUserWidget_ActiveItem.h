// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "SSUserWidget_ActiveItem.generated.h"


class USSUserWidget_Crosshair;
class USSUserWidget_Ammo;
class UTextBlock;



/**
 * Base item widget. No visuals and is meant for subclassing in BP
 */
UCLASS()
class SONICSHOOTER_API USSUserWidget_ActiveItem : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<USSUserWidget_Crosshair> CrosshairWidget;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<USSUserWidget_Ammo> AmmoWidget;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UTextBlock> ItemTextBlock;

public:
	USSUserWidget_ActiveItem(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, Category = "Crosshair")
		FSlateBrush CrosshairBrush;

protected:
	virtual void NativeOnInitialized() override;
	virtual void AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder) override;

};
