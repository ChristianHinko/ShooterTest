// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_WaitInputReleaseCust.h"
#include "AbilitySystemComponent.h"

UAT_WaitInputReleaseCust::UAT_WaitInputReleaseCust(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	callBackNumber = 0;
	StartTime = 0.f;
	bTestInitialState = false;
	bCanBroadcastMultibleTimes = false;
}

void UAT_WaitInputReleaseCust::OnReleaseCallback()
{
	callBackNumber++;
	float ElapsedTime = GetWorld()->GetTimeSeconds() - StartTime;

	if (!Ability || !AbilitySystemComponent)
	{
		return;
	}

	if (!bCanBroadcastMultibleTimes)
	{
		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey()).Remove(DelegateHandle);
	}

	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent, IsPredictingClient());

	if (IsPredictingClient())
	{
		// Tell the server about this
		AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
	}
	else
	{
		AbilitySystemComponent->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey());
	}

	// We are done. Kill us so we don't keep getting broadcast messages
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnRelease.Broadcast(ElapsedTime);
	}
}

UAT_WaitInputReleaseCust* UAT_WaitInputReleaseCust::WaitInputReleaseCust(class UGameplayAbility* OwningAbility, bool bTestAlreadyReleased, bool bCanBroadcastMultibleTimes)
{
	UAT_WaitInputReleaseCust* Task = NewAbilityTask<UAT_WaitInputReleaseCust>(OwningAbility);
	Task->bTestInitialState = bTestAlreadyReleased;
	Task->bCanBroadcastMultibleTimes = bCanBroadcastMultibleTimes;
	return Task;
}

void UAT_WaitInputReleaseCust::Activate()
{
	StartTime = GetWorld()->GetTimeSeconds();
	if (Ability)
	{
		if (bTestInitialState && IsLocallyControlled())
		{
			FGameplayAbilitySpec* Spec = Ability->GetCurrentAbilitySpec();
			if (Spec && !Spec->InputPressed)
			{
				OnReleaseCallback();
				return;
			}
		}

		DelegateHandle = AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UAT_WaitInputReleaseCust::OnReleaseCallback);
		if (IsForRemoteClient())
		{
			if (!AbilitySystemComponent->CallReplicatedEventDelegateIfSet(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey()))
			{
				SetWaitingOnRemotePlayerData();
			}
		}
	}
}







void UAT_WaitInputReleaseCust::OnDestroy(bool bInOwnerFinished)
{
	if (bCanBroadcastMultibleTimes)
	{
		AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputReleased, GetAbilitySpecHandle(), GetActivationPredictionKey()).Remove(DelegateHandle);
	}
}

