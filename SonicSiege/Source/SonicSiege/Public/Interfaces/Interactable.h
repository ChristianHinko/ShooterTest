// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayAbilitySpec.h"

#include "Interactable.generated.h"

class APawn;

/** Describes interact event */
UENUM()
enum class EDetectType
{
	TYPE_Sweep,				// Character did sweep for an Interactable to find this
	TYPE_Overlap			// Character checks Interactable overlaps to find this
};

/** Describes interact event */
UENUM()
enum class EDurationInteractEndReason
{
	REASON_Unknown,				// Used when the interaction ends for any unknown reason
	REASON_InputRelease,		// Player let go of interact input
	REASON_SweepMiss,			// Character's Interaction sweep missed. (Can't reach it)
	REASON_CharacterLeftInteractionOverlap,
	REASON_NewInteractionOverlapPriority,
	REASON_SuccessfulInteract	// After you've successfully interacted (Frame after the last frame of interaction)
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Might seem kind of unclear how to make an actor interactable, but all you have to do is choose a component to react to the interact channel (either Block or Overlap).
 *	As a quick overview: SSCharacter is what determines the CurrentInteractable. This interface is only for responding to any interaction that might occur. The only power this interface has in determining what the CurrentInteractable is is by setting bCanCurrentlyBeInteractedWith. 
 *	Having more than one component that are supposed to be interacted in different ways can get confusing. Might not work.
 *  All events are ran from within the interact abilities, besides sweep events. This Interface allows a fast implementation of custom logic for interaction, while still getting the benefits of abilities.
 *	You can treat these implementations the same way you would do logic in abilities. For instant interactions effects, montages, etc can be rolled back since InstantInteract ability is instant. Since DurationInteract is latent you only get rollback in OnDurationInteractBegin()
 *	---- Would love to eventually give all callbacks valid predicion keys, that way activation can be rolled back for durration interaction (at least for supported logic ie. Effects). Would also love to implement custom rollback and have a callback for that, but thats a topic on its own ----
 */
class SONICSIEGE_API IInteractable
{
	GENERATED_BODY()

public:
	IInteractable();

	
	bool GetCanCurrentlyBeInteractedWith();
	bool GetIsAutomaticInstantInteract();
	bool GetIsAutomaticDurationInteract();
	bool GetIsInstantInteract();
	bool GetIsDurationInteract();
	EDetectType GetDetectType();
	void SetInteractionType(EDetectType NewInteractionType);

	// Called from an interact ability's CanActivateAbility(). Gives implementor a chance to do some checks before activated.
	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const = 0;

	//virtual void OnDidNotActivate();


#pragma region AutomaticInteraction

	// Called from ActivateAbility() (valid prediction key)
	virtual void OnAutomaticInteract(APawn* InteractingPawn);
#pragma endregion





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
	bool bShouldInteractableTick;
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
	// Injected variable. Don't change. What the character detected this Interactable to be (set by character not implementor)
	EDetectType DetectType;
	
	bool bIsAutomaticInstantInteract;
	bool bIsAutomaticDurationInteract;
	bool bIsInstantInteract;
	bool bIsDurationInteract;
};
