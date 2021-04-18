// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"

#include "SSUserWidget.generated.h"


struct FGameplayAttribute;
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


	/**
	 * Add to this array in constructor to have it listened for
	 */
	TArray<FGameplayAttribute> AttributesToListenFor;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UAbilitySystemComponent* PlayerASC;

	/** Called when PlayerASC becomes valid */
	virtual void OnPlayerASCValid();
	/** Called when the owning Player Controller has a valid Player State */
	virtual void OnPlayerStateValid();

	/**
	 * Event called whenever one of the AttributesToListenFor has changed.
	 * Check the Data.Attribute to see which of the attributes has changed.
	 */
	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data);

private:
	ASSPlayerController* SSOwningPlayerController; // we only have this for the PS valid delegate

	/** Bind to the AttributeValueChangeDelegate for all of the AttributesToListenFor (and manually call OnAttributeChanged() for initial updates) */
	void SetUpAttributeListeningFor(UAbilitySystemComponent* ASC);

};
