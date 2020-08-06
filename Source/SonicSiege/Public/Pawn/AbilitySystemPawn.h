// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawn/SSPawn.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"

#include "AbilitySystemPawn.generated.h"


class ASSPlayerState;
class USSGameplayAbility;
class USSAttributeSet;
class UAS_Pawn;



/**
 * A Base GAS class
   
   Code in this class is just copied from the AbilitySystemPawn class. This is just the pawn version of that code. Only thing that really needs changing after copying the code is replace all instances of "Pawn" and "pawn" with "Pawn" and "pawn" respectively.

   Note: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this pawn. Having the ASC on the playerstate can make unpossesion and repossesion a pain
   since granted abilities and attribute sets exist on the PlayerState's ASC (because the pawn doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:
   bUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemovePawnTagsOnUnpossessed.
 
   
 Some tips:
	1) on EndPlay of this actor (so before it gets destroyed)
		- Removes Pawn owned Abilities and AttributeSets
	2) Levels
		- Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.
				You could even have multible GetLevel() functions, one for the pawn class and one that persists throughtout different pawns in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your pawn or playerstate level, you will have to think of a way to keep track of each individual ability level.
	3) Abilities
		- Any Abilities added with its SourceObject being the pawn will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between pawns make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)
		- We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle
		- If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic
	4) Attribute Sets
		- Any AttributeSets owned by this pawn will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between pawns make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)
		- Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one
	4) Gameplay Effects
		- Every pawn should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.
		- Any gameplay effects that this pawn should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)
	5) Gmeplay Tags		=@REVIEW MARKER@=
		- Right now I have a setup for it calling RemoveAllPawnTags() to remove any pawn tags from the player's ASC on Unpossess if bRemovePawnTagsOnUnpossessed is set to true, but the function is NOT implemented.
				There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this pawn which is why it is not implemented. If we can figure out a way to give an owner to
				specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of "Pawn" so we know all
				the "Pawn" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature
				implemented somehow, it might be better to just make a new GAS setup with the ASC on the pawn class.
		- Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has "Pawn" as one of the parents in the tag, but then this limits us
				us into only using tags with the parent of "Pawn" for pawn related stuff (ie. we wouldn't be able to throw a generic "Actor.IsOnFire" tag onto the pawn because then on Unpossess it wouldn't get removed).
				Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of
				replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an
				option but not prefered, (not very efficient).
				if that tag is on our ASC, it wouldn't be removed.
	6) AIAbilitySystemComponent
		- Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer
 Some problems to avoid:
	1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)
		- Have a different attribute set for every pawn and avoid inheriting attributes from a parent attribute set
	2) If you unpossess a pawn and unregister his attribute sets, his attributes are no longer associated with an ASC
		- Don't apply effects to pawns that have unregistered attribute sets (it will crash)
			-(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a pawn and unregisters its attributes and register those attribute sets with the AI ASC)
			-(Possible work around: have an AI controller possess the unpossessed pawn which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)
*/
UCLASS()
class SONICSIEGE_API AAbilitySystemPawn : public ASSPawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAbilitySystemPawn();


	/** Inherited via IAbilitySystemInterface. Returns the ASC (either the AI one or the PS one) */
	USSAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAS_Pawn* GetPawnAttributeSet() const { return PawnAttributeSet; }

protected:
#pragma region Abilities
	
#pragma endregion

#pragma region Effects
	/** Default attributes values for a Pawn on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Pawn's starting attribute values will be on spawn */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Effects")
		TSubclassOf<UGameplayEffect> DefaultAttributeValuesEffect;
	/** These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen) */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Effects")
		TArray<TSubclassOf<UGameplayEffect>> EffectsToApplyOnStartup;
#pragma endregion

	/** Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|AI")
		EGameplayEffectReplicationMode AIAbilitySystemComponentReplicationMode;

	UPROPERTY()
		ASSPlayerState* SSPlayerState;


	//BEGIN APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void OnRep_Controller() override;
	virtual void UnPossessed() override;
	//END APawn Interface

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	/**
	 * Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	 * call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is repped to the client so the PlayerState would be null in SetupPlayerInputComponent.
	 * Conversely, the PlayerState might be repped before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	 */
	void BindASCInput();


	/**
	 * Takes this object's AttributeSet(s) away from the player's ASC. This is on by default to prevent the potential problem of the ASC having 2 attribute sets of the same class.
	 * However if the ASC no longer has this object's AttributeSet, GameplayEffects can no longet modify their attributes.
	 */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Config")
		uint8 bUnregisterAttributeSetsOnUnpossessed : 1;
	/** Remove all abilities that this object owns on unpossess */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Config")
		uint8 bRemoveAbilitiesOnUnpossessed : 1;
	/**
	   ---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllPawnTags() FOR THIS TO DO SOMETHING---
	 * Removes all tags relating to this specific pawn from the PlayerState's ASC
	 * Remove all tags related to the pawn, that way when we possess a new pawn,
	 * the old tags don't interfere with the new pawn.
	 */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Config")
		uint8 bRemovePawnTagsOnUnpossessed : 1;


	/** Removes all attribute sets that this Pawn added to the PlayerState's ASC */
	int32 UnregisterPawnOwnedAttributeSets();
	/** Removes all abilities that this Pawn added to the PlayerState's ASC */
	int32 RemovePawnOwnedAbilities();
	/** NOT IMPLEMENTED YET! Removes all tags relating to this specific pawn from the PlayerState's ASC */
	void RemoveAllPawnTags();

	/** Called on the server and client. Override this to create new AttributeSets using NewObject(). This is if you have more than the default one. (call super in the beginning, then add your own logic) */
	virtual void CreateAttributeSets();
	/** Called on the server and client. Override this to register your created AttributeSets (from CreateAttributeSets()) with the ASC. This is if you have more than the default one. (call super in the beginning, then add your own logic) */
	virtual void RegisterAttributeSets();
	/** Called only on server. This is the earliest place you can grant an ability. (If overriding, return false if the Super returnes false, then add your own logic) */
	virtual bool GrantStartingAbilities();


#pragma region Input Events
	//Actions
	virtual void OnConfirmTargetPressed();
	virtual void OnConfirmTargetReleased();

	virtual void OnCancelTargetPressed();
	virtual void OnCancelTargetReleased();

	virtual void OnJumpPressed() override;
	virtual void OnJumpReleased() override;

	virtual void OnRunPressed() override;
	virtual void OnRunReleased() override;

#pragma endregion

private:
	// only one of these ASC will be active at a time
	UPROPERTY(/*Replicated*/)	// Replicated can be helpful for debugging issues
		USSAbilitySystemComponent* PlayerAbilitySystemComponent;
	UPROPERTY()
		USSAbilitySystemComponent* AIAbilitySystemComponent;

	/** Every pawn will have this attribute set. This is useful because this gives you a place for common attributes that every pawn should have. Children can make another attribute set specific to their pawn (ie. UAS_Demoman, UAS_Ganondorf) */
	UPROPERTY(Replicated)
		UAS_Pawn* PawnAttributeSet;


	/** The function that hooks this Pawn to the ASC. Calls most functions in this base Pawn class */
	void SetupWithAbilitySystem();
	/** Initialize the Pawn's attributes using the DefaultAttributeValuesEffect */
	void InitializeAttributes();
	/** Will apply all effects in EffectsToApplyOnStartup. */
	void ApplyStartupEffects();

	/** Indicates that we already created attribute sets and registered them, Initialized the attributes, and applied the startup effects */
	uint8 bAttributesAndStartupEffectsInitialized : 1;
	/** Shows that we already have input binded with the ability system */
	uint8 bASCInputBound : 1;
	/** Indicates we currently should be dealing with the AIAbilitySystemComponent (this is commonly paired with "!IsPlayerControlled()") */
	uint8 bShouldHandleAIAbilitySystemSetup : 1;
};
