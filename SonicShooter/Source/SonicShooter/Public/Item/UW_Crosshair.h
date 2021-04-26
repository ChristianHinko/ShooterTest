// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"

#include "UW_Crosshair.generated.h"


struct FOnAttributeChangeData;



/**
 * Base crosshair widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a spread attribute value and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_Crosshair : public USSUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_Crosshair(const FObjectInitializer& ObjectInitializer);


	/** The current spread value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly/*, BlueprintReadWrite, BlueprintSetter = SetCurrentSpread*/, Category = "Crosshair")
		float CurrentSpread;

protected:
	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data) override;

	//UFUNCTION(BlueprintSetter)
		void SetCurrentSpread(float NewSpread);

	/** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Crosshair", meta = (Keywords = "Tick"))
		void UpdateCrosshair();
};
