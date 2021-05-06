// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/SSAbilityTask_WaitTargetData.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TargetActor/SSGameplayAbilityTargetActor.h"



USSAbilityTask_WaitTargetData* USSAbilityTask_WaitTargetData::SSWaitTargetDataUsingActor(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* InTargetActor)
{
	USSAbilityTask_WaitTargetData* MyObj = NewAbilityTask<USSAbilityTask_WaitTargetData>(OwningAbility, TaskInstanceName);		//Register for task list here, providing a given FName as a key
	MyObj->TargetClass = nullptr;
	MyObj->TargetActor = InTargetActor;
	MyObj->ConfirmationType = ConfirmationType;
	return MyObj;
}

void USSAbilityTask_WaitTargetData::OnDestroy(bool AbilityEnded)
{
	if (TargetActor)
	{
		if (TargetActor->bDestroyOnConfirmation)
		{
			TargetActor->Destroy();
		}
		else
		{
			// Instead of destroying it, just deactivate it:


			if (ASSGameplayAbilityTargetActor* SSTargetActor = Cast<ASSGameplayAbilityTargetActor>(TargetActor))
			{
				// Tell the Target Actor he is being deactivated
				SSTargetActor->StopTargeting();
			}

			// Clear added callbacks
			TargetActor->TargetDataReadyDelegate.RemoveAll(this);
			TargetActor->CanceledDelegate.RemoveAll(this);

			AbilitySystemComponent->GenericLocalConfirmCallbacks.RemoveDynamic(TargetActor, &AGameplayAbilityTargetActor::ConfirmTargeting);
			AbilitySystemComponent->GenericLocalCancelCallbacks.RemoveDynamic(TargetActor, &AGameplayAbilityTargetActor::CancelTargeting);
			TargetActor->GenericDelegateBoundASC = nullptr;
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
