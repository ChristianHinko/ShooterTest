// 2017-2018 Puny Human Games

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "ArcAbilityTask_SimpleTarget.generated.h"




/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcInvAbilityTask_SimpleTarget : public UAbilityTask
{
	GENERATED_BODY()
public:
	UArcInvAbilityTask_SimpleTarget(const FObjectInitializer& ObjectInitializer);

	virtual FGameplayAbilityTargetDataHandle GenerateTargetHandle();
	virtual void HandleTargetData(const FGameplayAbilityTargetDataHandle& Data);
	virtual void HandleCancelled();


	virtual void Activate() override;
	virtual void OnTargetDataCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
	virtual void OnTargetDataCancelled();

protected:
	FGameplayAbilityTargetDataHandle ServerTargetData;
	
};
