// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilityTask.h"
#include "Interfaces/STInteractableInterface.h"
#include "UObject/ScriptInterface.h"

#include "STAbilityTask_DurationInteractCallbacks.generated.h"

class ASTCharacter_Shooter;


DECLARE_MULTICAST_DELEGATE_TwoParams(FInteractingTickDelegate, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionEndDelegate, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNewInteractionPriorityDelegate, float);
//DECLARE_MULTICAST_DELEGATE(FOnInteractionBeginDelegate);
/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTAbilityTask_DurationInteractCallbacks : public UASSAbilityTask
{
	GENERATED_BODY()

public:
	USTAbilityTask_DurationInteractCallbacks(const FObjectInitializer& ObjectInitializer);

	FInteractingTickDelegate OnInteractTickDelegate;
	//FOnInteractionEndDelegate OnInputReleaseDelegate   ----The ability will handle input release event for us----
	FOnInteractionEndDelegate OnInteractionSweepMissDelegate;
	FOnInteractionEndDelegate OnCharacterLeftInteractionOverlapDelegate;
	FOnNewInteractionPriorityDelegate OnNewInteractionPriorityDelegate;
	FOnInteractionEndDelegate OnSuccessfulInteractDelegate;

	void RemoveAllDelegates();

	UPROPERTY()
		TWeakObjectPtr<ASTCharacter_Shooter> ShooterCharacter;

	virtual void TickTask(float DeltaTime) override;

	FDelegateHandle OnPawnLeftOverlapInteractableDelegateHandle;
	void OnPawnLeftOverlapInteractable(ISTInteractableInterface*& InteractableThePawnLeft);

	/** Start a task that repeats an action or set of actions. */
	static USTAbilityTask_DurationInteractCallbacks* DurationInteractCallbacks(UGameplayAbility* OwningAbility, ASTCharacter_Shooter* ShooterCharacter, ISTInteractableInterface*& InInteract);

	void Activate() override;

	ISTInteractableInterface* Interactable;
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
