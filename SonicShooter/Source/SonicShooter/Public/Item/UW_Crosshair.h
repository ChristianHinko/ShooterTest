// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"
#include "Styling\SlateBrush.h"

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
	virtual void NativeConstruct() override;


	/** The current spread value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly/*, BlueprintReadWrite, BlueprintSetter = SetCurrentSpread*/, Category = "Crosshair")
		float CurrentSpread;


	UPROPERTY(EditAnywhere/*, BlueprintReadWrite, BlueprintSetter = SetCurrentSpread*/, Category = "Crosshair")
		FSlateBrush Brush_CrossHair;
protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		USizeBox* SB_Top;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		USizeBox* SB_Bottom;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		USizeBox* SB_Left;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		USizeBox* SB_Right;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* Image_Top;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* Image_Bottom;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* Image_Left;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* Image_Right;


	virtual void OnPlayerASCValid() override;
	UASC_Shooter* ShooterASC;

	UFUNCTION()
		void OnCurrentBulletSpreadChange(const float& OldValue, const float& NewValue);


	//UFUNCTION(BlueprintSetter)
		void SetCurrentSpread(float NewSpread);

	/** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
		void UpdateCrosshair();


	virtual void NativeDestruct() override;
};
