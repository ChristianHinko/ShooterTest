// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"

#include "UW_ActiveItem.generated.h"


struct FOnAttributeChangeData;
class UASC_Shooter;



/**
 * Base ammo widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a ammo attribute values and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_ActiveItem : public USSUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_ActiveItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		FText ActiveItemName;

protected:
	virtual void NativeDestruct() override;
};
