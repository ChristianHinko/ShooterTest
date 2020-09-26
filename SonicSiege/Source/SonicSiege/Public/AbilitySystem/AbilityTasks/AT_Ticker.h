// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "AT_Ticker.generated.h"

class AAbilitySystemCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTickDelegate, float, DeltaTime, float, CurrentTime, float, TimeRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDurationEnded);
/**
 * 
 */
UCLASS()
class SONICSIEGE_API UAT_Ticker : public USSAbilityTask
{
	GENERATED_BODY()

public:
	UAT_Ticker(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable)
		FTickDelegate OnInteractTickDelegate;
	UPROPERTY(BlueprintAssignable)
		FDurationEnded OnInteractCompletedDelegate;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	virtual void TickTask(float DeltaTime) override;


	/** Start a task that repeats an action or set of actions. */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Ticker", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAT_Ticker* Ticker(UGameplayAbility* OwningAbility, AAbilitySystemCharacter* GASCharactor, float Duration, float Interval, bool skipFirstTick);

	void Activate() override;

	FString GetDebugString() const override;
protected:
	float duration;
	bool skipFirstTick;
	float tickInterval;

	float currentTime;
	float continueTimestamp;
	float timeRemaining;

	void OnDurationEnded();

};