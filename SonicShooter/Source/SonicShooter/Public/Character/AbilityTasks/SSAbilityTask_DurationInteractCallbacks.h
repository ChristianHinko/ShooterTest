// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilityTask.h"
#include "Interfaces/SSInteractableInterface.h"
#include "UObject/ScriptInterface.h"

#include "SSAbilityTask_DurationInteractCallbacks.generated.h"

class ASSCharacter_Shooter;


DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractingTickDelegate, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionEndDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewInteractionPriorityDelegate, float);
//DECLARE_MULTICAST_DELEGATE(FOnInteractionBeginDelegate);
/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAbilityTask_DurationInteractCallbacks : public UASSAbilityTask
{
	GENERATED_BODY()

public:
	USSAbilityTask_DurationInteractCallbacks(const FObjectInitializer& ObjectInitializer);

	FInteractingTickDelegate OnInteractTickDelegate;
	//FOnInteractionEndDelegate OnInputReleaseDelegate   ----The ability will handle input release event for us----
	FOnInteractionEndDelegate OnInteractionSweepMissDelegate;
	FOnInteractionEndDelegate OnCharacterLeftInteractionOverlapDelegate;
	FOnNewInteractionPriorityDelegate OnNewInteractionPriorityDelegate;
	FOnInteractionEndDelegate OnSuccessfulInteractDelegate;

	void RemoveAllDelegates();

	UPROPERTY()
		TWeakObjectPtr<ASSCharacter_Shooter> ShooterCharacter;

	virtual void TickTask(float DeltaTime) override;

	FDelegateHandle OnPawnLeftOverlapInteractableDelegateHandle;
	void OnPawnLeftOverlapInteractable(ISSInteractableInterface*& InteractableThePawnLeft);

	/** Start a task that repeats an action or set of actions. */
	static USSAbilityTask_DurationInteractCallbacks* DurationInteractCallbacks(UGameplayAbility* OwningAbility, ASSCharacter_Shooter* ShooterCharacter, ISSInteractableInterface*& InInteract);

	void Activate() override;

	ISSInteractableInterface* Interactable;
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
