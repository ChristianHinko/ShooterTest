// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_Crosshair.generated.h"


class UASC_Shooter;
class USizeBox;
class UImage;



/**
 * Base crosshair widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a spread attribute value and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_Crosshair : public UASSEUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_Crosshair(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, Category = "Crosshair")
		FSlateBrush CrosshairBrush;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void OnPlayerASCValid() override;
	virtual void NativeDestruct() override;

	UASC_Shooter* ShooterASC;


	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBoxTop;
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBoxBottom;
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBoxLeft;
	UPROPERTY(meta = (BindWidget))
		USizeBox* SizeBoxRight;

	UPROPERTY(meta = (BindWidget))
		UImage* ImageTop;
	UPROPERTY(meta = (BindWidget))
		UImage* ImageBottom;
	UPROPERTY(meta = (BindWidget))
		UImage* ImageLeft;
	UPROPERTY(meta = (BindWidget))
		UImage* ImageRight;



	UFUNCTION()
		void OnCurrentBulletSpreadChange(const float& OldValue, const float& NewValue);

	/** The current spread value of the Attribute */
	float CurrentSpread;

	/** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
	void UpdateCrosshair();


};
