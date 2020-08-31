// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilityTask.h"
#include "Interfaces/Interactable.h"
#include "UObject/ScriptInterface.h"

#include "AT_InteractableInterfaceCaller.generated.h"

class AAbilitySystemCharacter;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractingTickDelegate, float, DeltaTime, float, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEndDelegate, float, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionBeginDelegate);
/**
 * 
 */
UCLASS()
class SONICSIEGE_API UAT_InteractableInterfaceCaller : public USSAbilityTask
{
	GENERATED_BODY()

public:
	UAT_InteractableInterfaceCaller(const FObjectInitializer& ObjectInitializer);

	FOnInteractionBeginDelegate OnInteractionBeginDelegate;
	FInteractingTickDelegate OnInteractTickDelegate;
	//FOnInteractionEndDelegate OnInputReleaseDelegate   ----The ability will handle input release event for us----
	FOnInteractionEndDelegate OnInteractionSweepMissDelegate;
	FOnInteractionEndDelegate OnSuccessfulInteractDelegate;

	UPROPERTY()
		AAbilitySystemCharacter* GASCharacter;

	virtual void TickTask(float DeltaTime) override;


	/** Start a task that repeats an action or set of actions. */
	static UAT_InteractableInterfaceCaller* InteractableInterfaceCaller(UGameplayAbility* OwningAbility, AAbilitySystemCharacter* GASCharactor, IInteractable*& InInteract);

	void Activate() override;

	IInteractable* Interact;
	FString GetDebugString() const override;
protected:

	float duration;
	float tickInterval;
	bool skipFirstTick;
	bool shouldCallTickEvent;

	float currentTime;
	float continueTimestamp;
	float timeRemaining;
};
