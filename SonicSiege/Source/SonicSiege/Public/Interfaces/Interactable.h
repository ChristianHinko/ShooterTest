// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/SSGameplayAbility.h"

#include "Interactable.generated.h"

class APawn;

/** Describes interaction that took place */
UENUM()
enum class EDetectType
{
	DETECTTYPE_NotYetDetected,
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
	REASON_AbilityCanceled,					// Used whenever the ability gets canceled (most likely due to one end not having valid variables on activation)
	REASON_SuccessfulInteract	// After you've successfully interacted (Frame after the last frame of interaction)
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Might seem kind of unclear how to make an actor interactable but that is because the character is what finds interactables and assignes the it an EDetectType. You don't set the EDetectType, it gets set by the character who detected the interactable.
 *	Basicly you need to make the actor findable to the character (can be done with a Block or Overlap). For blocks, the interaction sweep will hit it and then interaction can happen. For overlaps, the actor will be added to a stack of current interactable overlaps
 *	and will be prioritized over the previous overlaps since this is the most recent.
 * 
 *  All events are ran from within the interact abilities, besides sweep events. This Interface allows a fast implementation of custom logic for interaction, while still getting the benefits of abilities.
 *	You can treat these implementations the same way you would do logic in abilities. For instant interactions effects, montages, etc can be rolled back since InstantInteract ability is instant.
 *  Since DurationInteract is latent you only get rollback in OnDurationInteractBegin().
 */
class SONICSIEGE_API IInteractable
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
	
	bool GetCanCurrentlyBeInteractedWith();

	bool GetIsManualInstantInteract();
	bool GetIsAutomaticInstantInteract();
	bool GetIsManualDurationInteract();
	bool GetIsAutomaticDurationInteract();
	bool GetDurationInteractOccurring();
	EDetectType GetDetectType();

	// Called from an interact ability's CanActivateAbility(). Gives implementor a chance to do some checks before activated.
	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const = 0;

	//virtual void OnDidNotActivate();


#pragma region InstantInteraction

	// Called from ActivateAbility() (valid prediction key)
	virtual void OnInstantInteract(APawn* InteractingPawn);
#pragma endregion





#pragma region DurationInteraction

	// How long the player needs to hold interact input to interact with this interactable
	float interactDuration;
	// Time to wait between ticks to help performance. Be careful with this... longer wait between ticks means a less accurate duration end (might over/undershoot interactDuration).
	float tickInterval;
	// Lets you make use of InteractingTick event
	bool bShouldDurationInteractableTick;
	// Skips first call to InteractingTick()
	bool bShouldSkipFirstTick;
	// Called the first frame of interaction (on press interact input) (valid prediction key)
	virtual void OnDurationInteractBegin(APawn* InteractingPawn);
	// Called every frame during a duration interaction (while interact input is down)
	virtual void InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime);
	// Called anytime a duration interaction ends (whatever the reason may be)
	virtual void OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime);
#pragma endregion





// Sweep events are called on both client and server from character tick (chance that only client calls but server doesn't or vice versa)
#pragma region SweepEvents

	// Allows events to be fired by the character's InteractionSweep
	bool bShouldFireSweepEvents;
	// Interaction sweep hit this interactable (a one frame fire)
	virtual void OnInteractSweepInitialHit(APawn* InteractingPawn);
	// Interaction sweep hit this interactable again
	virtual void OnInteractSweepConsecutiveHit(APawn* InteractingPawn);
	// Interaction sweep stopped hitting (a one frame fire)
	virtual void OnInteractSweepEndHitting(APawn* InteractingPawn);
#pragma endregion















protected:
	// If set to false, character will ignore this interactable and find the next best option for the frame. This is different from returning false in CanActivateInteractAbility() in that this even prevents the player from even having the option to interact (ie. you've already interacted with this). Basicly this completely turns off the interactability until turned back on.
	bool bCanCurrentlyBeInteractedWith;


	
	


	// If set to manual and automatic CanActivateAbility() will return false. Automatic and Manual should maybe be separate abilities
	//-----------------------------------
	bool bIsManualInstantInteract;			
	bool bIsAutomaticInstantInteract;
	bool bIsManualDurationInteract;			
	bool bIsAutomaticDurationInteract;	

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
