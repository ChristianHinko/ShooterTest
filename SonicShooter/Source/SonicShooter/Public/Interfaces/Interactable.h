// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "Interactable.generated.h"

class AShooterCharacter;

/** Describes the detection state */
UENUM()
enum class EDetectType
{
	DETECTTYPE_NotDetected,
	DETECTTYPE_Sweeped,				// Character did sweep for an Interactable to find this
	DETECTTYPE_Overlapped			// Character checks Interactable overlaps to find this
};

/** Describes the reason the interact ended (Called from EndAbility()) */
UENUM()
enum class EDurationInteractEndReason
{
	REASON_Unknown,				// Used when the interaction ends for any unknown reason
	REASON_InputRelease,		// Player let go of interact input
	REASON_SweepMiss,			// Character's Interaction sweep missed. (Can't reach it)
	REASON_CharacterLeftInteractionOverlap,
	REASON_NewInteractionOverlapPriority,	// Not currently being used. May add this feature in the future
	REASON_PredictionCorrected,					// Used whenever the ability gets ended because the server rejected it (most likely due to one end not having valid variables on activation). Not a feature yet
	REASON_SuccessfulInteract	// After you've successfully interacted (Frame after the last frame of interaction)
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Might seem kind of unclear how to make an actor interactable but that is because the character is what finds interactables and assignes the it an EDetectType. You don't set the EDetectType, it gets set by the character who detected the interactable.
 *	Basicly you need to make the actor findable to the character (can be done with a Block or Overlap). For blocks, the interaction sweep will hit it and then interaction can happen. For overlaps, the actor will be added to a stack of current interactable overlaps
 *	and will be prioritized over the previous overlaps since this is the most recent.
 * 
 *  All events are ran from within the interact abilities, besides detection events. This Interface allows a fast implementation of custom logic for interaction, while still getting the benefits of abilities.
 *	You can treat these implementations the same way you would do logic in abilities. For instant interactions effects, montages, etc can be rolled back since InstantInteract ability is instant.
 *  Since DurationInteract is latent you only get rollback in OnDurationInteractBegin().
 */
class SONICSHOOTER_API IInteractable
{
	GENERATED_BODY()

public:
	IInteractable();

	/* This will be applied at the beginning of the ability and removed at the end (an infinite effect) */
	virtual TSubclassOf<UGameplayEffect> GetInteractableEffectTSub() =0;
	/** WARNING: Implementors don't touch! External use only! */
	void InjectDetectType(EDetectType newDetectType);
	/** WARNING: Implementors don't touch! External use only! */
	void InjectDurationInteractOccurring(bool newDurationInteractOccurring);

	// Injected variable. Implementors should not touch this
	bool GetDurationInteractOccurring();
	// Injected variable. What the character detected this Interactable to be. Implementors should not touch this
	EDetectType GetDetectType();

#pragma region ImplementorSetProperties
	// How long the player needs to hold interact input to interact with this interactable
	virtual float GetInteractDuration() = 0;

	// Time to wait between ticks to help performance. Be careful with this... longer wait between ticks means a less accurate duration end (might over/undershoot interactDuration).
	virtual float GetTickInterval() = 0;

	// Lets you make use of InteractingTick event
	virtual bool GetShouldDurationInteractableTick() = 0;

	// Skips first call to InteractingTick()
	virtual bool GetShouldSkipFirstTick() = 0;

	//// Allows events to be fired by the character's interaction scanner
	virtual bool GetShouldFireDetectionEvents() = 0;


	//// If set to false, character will ignore this interactable and find the next best option for the frame. This is different from returning false in CanActivateInteractAbility() in that this even prevents the player from even having the option to interact (ie. you've already interacted with this). Basicly this completely turns off the interactability until turned back on.
	virtual bool GetCanCurrentlyBeInteractedWith() = 0;






	// If set to manual and automatic CanActivateAbility() will return false. Automatic and Manual should maybe be separate abilities
	//-----------------------------------
	virtual bool GetIsManualInstantInteract() = 0;
	virtual bool GetIsAutomaticInstantInteract() = 0;
	virtual bool GetIsManualDurationInteract() = 0;
	virtual bool GetIsAutomaticDurationInteract() = 0;
#pragma endregion


	// Called from an interact ability's CanActivateAbility(). Gives implementor a chance to do some checks before activated. Only called on manual interacts since auto interacts utilizes a passiva ability to interact
	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const = 0;

	//virtual void OnDidNotActivate();


#pragma region InstantInteraction

	// Called from ActivateAbility() (valid prediction key)
	virtual void OnInstantInteract(AShooterCharacter* InteractingCharacter);
#pragma endregion





#pragma region DurationInteraction


	// Called the first frame of interaction (on press interact input) (valid prediction key)
	virtual void OnDurationInteractBegin(AShooterCharacter* InteractingCharacter);
	// Called every frame during a duration interaction (while interact input is down)
	virtual void InteractingTick(AShooterCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime);
	// Called anytime a duration interaction ends (whatever the reason may be)
	virtual void OnDurationInteractEnd(AShooterCharacter* InteractingCharacter, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime);
#pragma endregion





	// Detection events are called on both client and server from character tick (chance that only client calls but server doesn't or vice versa or that they have different interactables when called)
#pragma region Detection Events

	// This became the player's current interactable
	virtual void OnInitialDetect(AShooterCharacter* InteractingCharacter);
	// This remains the player's current interactable
	virtual void OnConsecutiveDetect(AShooterCharacter* InteractingCharacter);
	// This is no longer the player's current interactable
	virtual void OnEndDetect(AShooterCharacter* InteractingCharacter);
#pragma endregion
















protected:



	// Not yet sure if I want this implemented yet
	//bIsInstancedPerActor;		// All instant interacts could use this easilty. Just sorta weird since to interact with everything at once it loops through the stack in the ability
	//bIsInstancedPerExecution;	// All durration interacts might just always have to be this
	//
	//bIsLocallyPredicted;		// Should only be for manuals
	//bIsServerInitiated;			// Should be for autos
	//bIsServerOnly;				// This would be a nice option to have for the implementor
	//----------------------------------



private:
	// Injected variable. Implementors should not touch this
	bool bDurationInteractOccurring;
	// Injected variable. What the character detected this Interactable to be. Implementors should not touch this
	EDetectType DetectType;
};
