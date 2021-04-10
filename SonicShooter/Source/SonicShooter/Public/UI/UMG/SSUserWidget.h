// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"

#include "SSUserWidget.generated.h"


class UAbilitySystemComponent;
struct FOnAttributeChangeData;
class ASSPlayerController;



/**
 * Base UserWidget class.
 * 
 * Has ability to listen for attribute changes
 */
UCLASS()
class SONICSHOOTER_API USSUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USSUserWidget(const FObjectInitializer& ObjectInitializer);


	TArray<FGameplayAttribute> AttributesToListenFor;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UAbilitySystemComponent* PlayerASC;
	ASSPlayerController* SSOwningPlayerController; // only have this for the PS valid delegate

	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data);

private:
	void SetUpAttributeListeningFor(UAbilitySystemComponent* ASC);

	void OnPlayerStateValid();
};
