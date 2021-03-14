// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"

#include "AT_SSWaitTargetData.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAT_SSWaitTargetData : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
		static UAT_SSWaitTargetData* SSWaitTargetDataUsingActor(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* InTargetActor);

protected:
	virtual void OnDestroy(bool AbilityEnded) override;
};
