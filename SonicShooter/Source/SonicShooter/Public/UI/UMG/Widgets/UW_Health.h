// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_Health.generated.h"


struct FOnAttributeChangeData;
class UTextBlock;
class UProgressBar;



/**
 * Base Health widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a Health attribute values and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_Health : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UTextBlock> HealthTextBlock;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UProgressBar> HealthProgressBar;

public:
	UUW_Health(const FObjectInitializer& ObjectInitializer);


	/** The current health value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float CurrentHealth;
	/** The current max health value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float MaxHealth;

protected:
	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data) override;

	/** Called on Health changed. Use this to update Health based UI */
	void UpdateHealthStatus();
};
