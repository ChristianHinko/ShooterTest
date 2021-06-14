// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"

#include "SSAbilityTask_WaitTargetData.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAbilityTask_WaitTargetData : public UAbilityTask_WaitTargetData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")
		static USSAbilityTask_WaitTargetData* SSWaitTargetDataUsingActor(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* InTargetActor);

protected:
	virtual void Activate() override;

	virtual void OnDestroy(bool AbilityEnded) override;
};
