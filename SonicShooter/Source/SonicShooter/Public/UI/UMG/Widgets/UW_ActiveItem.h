// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_ActiveItem.generated.h"


struct FOnAttributeChangeData;
class UASC_Shooter;



/**
 * Base item widget. No visuals and is meant for subclassing in BP
 */
UCLASS()
class SONICSHOOTER_API UUW_ActiveItem : public UASSEUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_ActiveItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		FText ActiveItemName;

protected:
	virtual void NativeDestruct() override;
};
