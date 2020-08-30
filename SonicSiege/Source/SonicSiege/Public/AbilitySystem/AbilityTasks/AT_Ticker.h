// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "AT_Ticker.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickDelegate, float, DeltaTime);
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
		FTickDelegate OnTickDelegate;
	UPROPERTY(BlueprintAssignable)
		FDurationEnded OnFinish;


	virtual void TickTask(float DeltaTime) override;


	/** Start a task that repeats an action or set of actions. */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Ticker", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAT_Ticker* Ticker(UGameplayAbility* OwningAbility, float Duration);

	void Activate() override;

	FString GetDebugString() const override;
protected:
	float tickDuration;
	float currentTime;

	void OnDurationEnded();
	void OnDestroy(bool AbilityIsEnding) override;

};
