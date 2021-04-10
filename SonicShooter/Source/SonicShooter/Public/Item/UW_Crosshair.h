// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"
#include "AttributeSet.h"

#include "UW_Crosshair.generated.h"


class UAbilitySystemComponent;
struct FOnAttributeChangeData;
class ASSPlayerController;



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

	FGameplayAttribute SpreadAttribute;

protected:
	UAbilitySystemComponent* PlayerASC;
	ASSPlayerController* SSOwningPlayerController; // only have this for the PS valid delegate

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void OnPlayerStateValid();


	void OnSpreadAttributeChanged(const FOnAttributeChangeData& Data);

	//UFUNCTION(BlueprintSetter)
		void SetCurrentSpread(float NewSpread);

	/** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Crosshair", meta = (Keywords = "Tick"))
		void UpdateCrosshair();
};
