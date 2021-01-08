// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ArcAbilityTask_WaitItemSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitItemSwitchDelegate);

/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcAbilityTask_WaitItemSwitch : public UAbilityTask
{
	GENERATED_BODY()
public:
	UArcAbilityTask_WaitItemSwitch(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static 	UArcAbilityTask_WaitItemSwitch* WaitActiveItemSwitch(UGameplayAbility* OwningAbility, int32 ItemIndex);

	
	virtual void Activate() override;
	virtual void BeginDestroy() override;


	virtual void DoItemEquip();

	UPROPERTY(BlueprintAssignable)
	FWaitItemSwitchDelegate OnItemSwitched;
protected: 

	class UArcInventoryComponent_Active* Inventory; 
	int32 ItemIndex;

	FTimerHandle TimerHandle;
	
};
