// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "AT_WaitInputPressCust.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputPressCustDelegate, float, TimeWaited);

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAT_WaitInputPressCust : public USSAbilityTask
{
	GENERATED_UCLASS_BODY()

		UPROPERTY(BlueprintAssignable)
		FInputPressCustDelegate		OnPress;

	UFUNCTION()
		void OnPressCallback();

	virtual void Activate() override;

	/** Wait until the user presses the input button for this ability's activation. Returns time this node spent waiting for the press. Will return 0 if input was already down. */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAT_WaitInputPressCust* WaitInputPressCust(UGameplayAbility* OwningAbility, bool bTestAlreadyPressed = false, bool bCanBroadcastMultibleTimes = false);

	virtual void OnDestroy(bool bInOwnerFinished) override;

public:
	int32 callBackNumber;

protected:

	float StartTime;
	uint8 bTestInitialState;
	uint8 bCanBroadcastMultibleTimes;
	FDelegateHandle DelegateHandle;
};
