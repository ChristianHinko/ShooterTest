// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_SSWaitTargetData.h"



UAT_SSWaitTargetData* UAT_SSWaitTargetData::SSWaitTargetDataUsingActor(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* InTargetActor)
{
	UAT_SSWaitTargetData* MyObj = NewAbilityTask<UAT_SSWaitTargetData>(OwningAbility, TaskInstanceName);		//Register for task list here, providing a given FName as a key
	MyObj->TargetClass = nullptr;
	MyObj->TargetActor = InTargetActor;
	MyObj->ConfirmationType = ConfirmationType;
	return MyObj;
}

void UAT_SSWaitTargetData::OnDestroy(bool AbilityEnded)
{
	if (TargetActor)
	{
		if (TargetActor->bDestroyOnConfirmation)
		{
			TargetActor->Destroy();
		}
		else
		{
			TargetActor->SourceActor = nullptr; // instead of destroying it, just deactivate it
		}
	}
	
	if (Super::StaticClass() == UAbilityTask_WaitTargetData::StaticClass())
	{
		UAbilityTask_WaitTargetData::Super::OnDestroy(AbilityEnded);	// skip UAbilityTask_WaitTargetData's call on OnDestroy()
	}
	else
	{
		Super::OnDestroy(AbilityEnded);
	}
}
