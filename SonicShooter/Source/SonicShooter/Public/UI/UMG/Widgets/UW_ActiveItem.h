// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_ActiveItem.generated.h"


class UUW_Crosshair;
class UUW_Ammo;



/**
 * Base item widget. No visuals and is meant for subclassing in BP
 */
UCLASS()
class SONICSHOOTER_API UUW_ActiveItem : public UASSEUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_ActiveItem(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UUW_Crosshair* CrosshairWidget;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UUW_Ammo* AmmoWidget;


	UPROPERTY(BlueprintReadOnly, Category = "Item")
		FText ActiveItemName;

protected:
	virtual void NativeConstruct() override;

};
