// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"

#include "SSUserWidget.generated.h"


struct FGameplayAttribute;
struct FGameplayTag;

class UAbilitySystemComponent;
struct FOnAttributeChangeData;



/**
 * Base User Widget class.
 * 
 * Has ability to listen to ASC events
 */
UCLASS()
class SONICSHOOTER_API USSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USSUserWidget(const FObjectInitializer& ObjectInitializer);


	/**
	 * Add attributes to this array in constructor to have it listened to for OnAttributeChanged()
	 */
	TArray<FGameplayAttribute> AttributesToListenFor;

	/**
	 * Add tags to this array in constructor to have them listened to for OnTagChanged()
	 */
	TArray<FGameplayTag> TagsToListenFor;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override; // for checking on tick until the Player State is valid (NOTE: this won't work for DisableNativeTick meta flag so maybe make a separate tick function)

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
	/**
	 * Event called whenever one of the TagsToListenFor has changed tag count.
	 * Check the Data.Attribute to see which of the attributes has changed.
	 */
	virtual void OnTagChanged(const FGameplayTag Tag, int32 NewCount);

private:
	/** Bind to the AttributeValueChangeDelegate for all of the AttributesToListenFor (and manually call OnAttributeChanged() for initial updates) */
	void SetUpAttributeListeningFor(UAbilitySystemComponent* ASC);
	/** Bind to the GameplayTag events for all of the TagsToListenFor (and manually call OnTagChanged() for initial updates) */
	void SetUpTagListeningFor(UAbilitySystemComponent* ASC);


	/** For checking on tick until the Player State is valid */
	uint8 bPlayerStateBecameValid : 1;

};
