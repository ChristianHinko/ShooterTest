// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_Ticker.h"

#include "Character/AbilitySystemCharacter.h"

UAT_Ticker::UAT_Ticker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;
	
}


UAT_Ticker* UAT_Ticker::Ticker(UGameplayAbility* OwningAbility, AAbilitySystemCharacter* GASCharactor, float Duration, float Interval, bool SkipFirstTick)
{
	UAT_Ticker* MyObj = NewAbilityTask<UAT_Ticker>(OwningAbility);
	MyObj->duration = Duration;
	MyObj->tickInterval = Interval;
	MyObj->skipFirstTick = SkipFirstTick;
	MyObj->GASCharacter = GASCharactor;

	return MyObj;
}

void UAT_Ticker::Activate()
{

	currentTime = 0;
	timeRemaining = duration;
	continueTimestamp = 0;
}

void UAT_Ticker::TickTask(float DeltaTime)
{
	if (currentTime >= duration)
	{
		OnDurationEnded();
		return;
	}

	if ((continueTimestamp == 0) && skipFirstTick)
	{
		skipFirstTick = false;

		////
		currentTime = currentTime + DeltaTime;
		timeRemaining = timeRemaining - DeltaTime;
		continueTimestamp = continueTimestamp + tickInterval;
		////
		return;
	}
	if (currentTime < continueTimestamp)
	{
		currentTime = currentTime + DeltaTime;
		timeRemaining = timeRemaining - DeltaTime;
		return;
	}

	if (!IsPendingKill())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInteractTickDelegate.Broadcast(DeltaTime, currentTime, timeRemaining);
		}
	}

	////
	currentTime = currentTime + DeltaTime;
	timeRemaining = timeRemaining - DeltaTime;
	continueTimestamp = continueTimestamp + tickInterval;
	////
}

void UAT_Ticker::OnDurationEnded()
{
	if (!IsPendingKill())
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInteractCompletedDelegate.Broadcast();
		}
	}
	EndTask();
}

FString UAT_Ticker::GetDebugString() const
{
	return FString::Printf(TEXT("Ticker"));
}

