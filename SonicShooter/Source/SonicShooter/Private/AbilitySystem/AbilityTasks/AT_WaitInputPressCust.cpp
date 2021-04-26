// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_WaitInputPressCust.h"

#include "AbilitySystemComponent.h"

UAT_WaitInputPressCust::UAT_WaitInputPressCust(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	callBackNumber = 0;
	StartTime = 0.f;
	bTestInitialState = false;
	bCanBroadcastMultibleTimes = false;
}

void UAT_WaitInputPressCust::OnPressCallback()
{
	++callBackNumber;
	float ElapsedTime = GetWorld()->GetTimeSeconds() - StartTime;

	if (!Ability || !AbilitySystemComponent)
	{
		return;
	}

	if (!bCanBroadcastMultibleTimes)
	{
		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey()).Remove(DelegateHandle);
	}

	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent, IsPredictingClient());

	if (IsPredictingClient())
	{
		// Tell the server about this
		AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
	}
	else
	{
		AbilitySystemComponent->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey());
	}

	// We are done. Kill us so we don't keep getting broadcast messages
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnPress.Broadcast(ElapsedTime);
	}
}

UAT_WaitInputPressCust* UAT_WaitInputPressCust::WaitInputPressCust(class UGameplayAbility* OwningAbility, bool bTestAlreadyPressed, bool bCanBroadcastMultibleTimes)
{
	UAT_WaitInputPressCust* Task = NewAbilityTask<UAT_WaitInputPressCust>(OwningAbility);
	Task->bTestInitialState = bTestAlreadyPressed;
	Task->bCanBroadcastMultibleTimes = bCanBroadcastMultibleTimes;
	return Task;
}

void UAT_WaitInputPressCust::Activate()
{
	StartTime = GetWorld()->GetTimeSeconds();
	if (Ability)
	{
		if (bTestInitialState && IsLocallyControlled())
		{
			FGameplayAbilitySpec* Spec = Ability->GetCurrentAbilitySpec();
			if (Spec && Spec->InputPressed)
			{
				OnPressCallback();
				return;
			}
		}

		DelegateHandle = AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UAT_WaitInputPressCust::OnPressCallback);
		if (IsForRemoteClient())
		{
			if (!AbilitySystemComponent->CallReplicatedEventDelegateIfSet(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey()))
			{
				SetWaitingOnRemotePlayerData();
			}
		}
	}
}






void UAT_WaitInputPressCust::OnDestroy(bool bInOwnerFinished)
{
	if (bCanBroadcastMultibleTimes)
	{
		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputPressed, GetAbilitySpecHandle(), GetActivationPredictionKey()).Remove(DelegateHandle);
	}
}


