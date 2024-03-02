// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "STUserWidget_Crosshair.generated.h"


class USizeBox;
class UImage;
class USTItemFragment_BulletSpreadInstanced;



/**
 * Base crosshair widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a spread attribute value and events for when to update UI.
 */
UCLASS()
class SHOOTERTEST_API USTUserWidget_Crosshair : public UASSEUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> SizeBoxTop;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> SizeBoxBottom;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> SizeBoxLeft;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> SizeBoxRight;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ImageTop;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ImageBottom;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ImageLeft;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> ImageRight;

public:
    USTUserWidget_Crosshair(const FObjectInitializer& ObjectInitializer);


    UPROPERTY(EditAnywhere, Category = "Crosshair")
    FSlateBrush CrosshairBrush;

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;


    virtual void OnPlayerASCValid() override;

    UPROPERTY()
    TWeakObjectPtr<USTItemFragment_BulletSpreadInstanced> BulletSpreadItemFragment;
    UFUNCTION()
        void OnCurrentBulletSpreadChange(FGCFloatPropertyWrapper& PropertyWrapper, const float& InOldValue, const float& InNewValue);

    /** The current spread value of the Attribute */
    float CurrentSpread;

    /** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
    void UpdateCrosshair();


};
