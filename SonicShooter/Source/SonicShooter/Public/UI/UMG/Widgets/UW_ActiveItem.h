// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_ActiveItem.generated.h"


class UUW_Crosshair;
class UUW_Ammo;
class UTextBlock;



/**
 * Base item widget. No visuals and is meant for subclassing in BP
 */
UCLASS()
class SONICSHOOTER_API UUW_ActiveItem : public UASSEUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_ActiveItem(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, Category = "Crosshair")
		FSlateBrush CrosshairBrush;

	/** Inject item name here immediately after Widget creation */
	FText ActiveItemName;

protected:
	virtual void NativeOnInitialized() override;


	UPROPERTY(meta = (BindWidget))
		UUW_Crosshair* CrosshairWidget; 
	UPROPERTY(meta = (BindWidget))
		UUW_Ammo* AmmoWidget;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ItemTextBlock;

};
