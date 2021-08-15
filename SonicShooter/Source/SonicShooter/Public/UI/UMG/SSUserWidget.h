// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeSet.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"

#include "SSUserWidget.generated.h"


class USSUserWidget;

/**
 * For checking on tick until the Player State is valid
 */
USTRUCT()
struct FTF_PlayerStateValid : public FTickFunction
{
	GENERATED_BODY()


	FTF_PlayerStateValid()
	{
		// This bool doesn't actually do anything for some reason so we have to call SetTickFunctionEnable() after
		bStartWithTickEnabled = true;
		SetTickFunctionEnable(bStartWithTickEnabled);

		TickGroup = ETickingGroup::TG_PrePhysics; // as soon as possible


		// Optimizations:

		bAllowTickOnDedicatedServer = false;
		//bRunOnAnyThread = true; // i want to do this but we can't because we call the OnPlayerStateValid() event in this
	}

	USSUserWidget* Target;

	virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;


	virtual FString DiagnosticMessage() override
	{
		return FString(TEXT("FTF_PlayerStateValid"));
	}

	virtual FName DiagnosticContext(bool bDetailed) override
	{
		return FName(TEXT("USSUserWidget"));
	}
};

template<>
struct TStructOpsTypeTraits<FTF_PlayerStateValid> : public TStructOpsTypeTraitsBase2<FTF_PlayerStateValid>
{
	enum
	{
		WithCopy = false
	};
};



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

	friend struct FTF_PlayerStateValid;
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
	FTF_PlayerStateValid PlayerStateValidTickFunction;

};
