// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "Interfaces/Interactable.h"
#include "UObject/ScriptInterface.h"

#include "AT_DurationInteractCallbacks.generated.h"

class AShooterCharacter;


DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractingTickDelegate, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionEndDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewInteractionPriorityDelegate, float);
//DECLARE_MULTICAST_DELEGATE(FOnInteractionBeginDelegate);
/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAT_DurationInteractCallbacks : public USSAbilityTask
{
	GENERATED_BODY()

public:
	UAT_DurationInteractCallbacks(const FObjectInitializer& ObjectInitializer);

	FInteractingTickDelegate OnInteractTickDelegate;
	//FOnInteractionEndDelegate OnInputReleaseDelegate   ----The ability will handle input release event for us----
	FOnInteractionEndDelegate OnInteractionSweepMissDelegate;
	FOnInteractionEndDelegate OnCharacterLeftInteractionOverlapDelegate;
	FOnNewInteractionPriorityDelegate OnNewInteractionPriorityDelegate;
	FOnInteractionEndDelegate OnSuccessfulInteractDelegate;

	void RemoveAllDelegates();

	UPROPERTY()
		AShooterCharacter* ShooterCharacter;

	virtual void TickTask(float DeltaTime) override;

	FDelegateHandle OnPawnLeftOverlapInteractableDelegateHandle;
	void OnPawnLeftOverlapInteractable(IInteractable*& InteractableThePawnLeft);

	/** Start a task that repeats an action or set of actions. */
	static UAT_DurationInteractCallbacks* DurationInteractCallbacks(UGameplayAbility* OwningAbility, AShooterCharacter* ShooterCharacter, IInteractable*& InInteract);

	void Activate() override;

	IInteractable* Interactable;
	FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;
protected:

	float duration;
	float tickInterval;
	bool skipFirstTick;
	bool shouldCallTickEvent;

	float currentTime;
	float continueTimestamp;
	float timeRemaining;
	int32 stackPosition;
};
