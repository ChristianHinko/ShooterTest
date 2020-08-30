// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_Ticker.h"

UAT_Ticker::UAT_Ticker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;
}


UAT_Ticker* UAT_Ticker::Ticker(UGameplayAbility* OwningAbility, float Duration)
{
	UAT_Ticker* MyObj = NewAbilityTask<UAT_Ticker>(OwningAbility);
	MyObj->tickDuration = Duration;

	return MyObj;
}

void UAT_Ticker::Activate()
{
	currentTime = 0;
	if (!Ability || !AbilitySystemComponent)
	{
		return;
	}
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_PerformAction, this, &UAT_Ticker::PerformAction, DelayBetweenRepeats, shouldLoop, firstDelay);
}

void UAT_Ticker::TickTask(float DeltaTime)
{
	currentTime = currentTime + DeltaTime;
	if (currentTime >= tickDuration)
	{
		OnDurationEnded();
	}

	if (!IsPendingKill())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnTickDelegate.Broadcast(DeltaTime);
		}
	}
}

void UAT_Ticker::OnDurationEnded() const
{
	if (!Ability || !AbilitySystemComponent)
	{
		return;
	}


	if (!IsPendingKill())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnFinish.Broadcast();
		}
	}
}



void UAT_Ticker::OnDestroy(bool AbilityIsEnding)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_PerformAction);

	Super::OnDestroy(AbilityIsEnding);
}

FString UAT_Ticker::GetDebugString() const
{
	return FString::Printf(TEXT("Ticker"));
}


