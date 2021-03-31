// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"
#include "AttributeSet.h"

#include "UW_Crosshair.generated.h"


class UAbilitySystemComponent;
struct FOnAttributeChangeData;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UUW_Crosshair : public USSUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_Crosshair();


	UPROPERTY(EditAnywhere, BlueprintReadOnly/*, BlueprintReadWrite, BlueprintSetter = SetCurrentSpread*/, Category = "Crosshair")
		float CurrentSpread;

	FGameplayAttribute SpreadAttribute;

protected:
	UAbilitySystemComponent* PlayerASC;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	void SpreadAttributeChanged(const FOnAttributeChangeData& Data);

	//UFUNCTION(BlueprintSetter)
		void SetCurrentSpread(float NewSpread);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Crosshair", meta = (Keywords = "Tick"))
		void UpdateCrosshair();
};
