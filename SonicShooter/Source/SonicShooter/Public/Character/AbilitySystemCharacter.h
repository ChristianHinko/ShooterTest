// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacter.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"

#include "AbilitySystemCharacter.generated.h"


class ASSPlayerState;
class USSAttributeSet;
class USSGameplayAbility;
class UAS_Character;
class UAS_Health;



DECLARE_MULTICAST_DELEGATE(FSetupWithAbilitySystemDelegate);

/**
 * A Base GAS class
 * Note: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this character. Having the ASC on the playerstate can make unpossesion and repossesion a pain
 * since granted abilities and attribute sets exist on the PlayerState's ASC (because the character doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:
 * bUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemoveCharacterTagsOnUnpossessed.

 Some tips:
	1) on EndPlay of this actor (so before it gets destroyed)
		- Removes Character owned Abilities and AttributeSets
	2) Levels
		- Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.
				You could even have multible GetLevel() functions, one for the character class and one that persists throughtout different characters in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your character or playerstate level, you will have to think of a way to keep track of each individual ability level.
	3) Abilities
		- Any Abilities added with its SourceObject being the character will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between characters make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)
		- We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle
		- If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic
	4) Attribute Sets
		- Any AttributeSets owned by this character will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between characters make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)
		- Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one
	4) Gameplay Effects
		- Every character should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.
		- Any gameplay effects that this character should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)
	5) Gmeplay Tags		=@REVIEW MARKER@=
		- Right now I have a setup for it calling RemoveAllCharacterTags() to remove any character tags from the player's ASC on Unpossess if bRemoveCharacterTagsOnUnpossessed is set to true, but the function is NOT implemented.
				There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this character which is why it is not implemented. If we can figure out a way to give an owner to
				specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of "Character" so we know all
				the "Character" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature
				implemented somehow, it might be better to just make a new GAS setup with the ASC on the character class.
		- Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has "Character" as one of the parents in the tag, but then this limits us
				us into only using tags with the parent of "Character" for character related stuff (ie. we wouldn't be able to throw a generic "Actor.IsOnFire" tag onto the character because then on Unpossess it wouldn't get removed).
				Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of
				replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an
				option but not prefered, (not very efficient).
				if that tag is on our ASC, it wouldn't be removed.
	6) AIAbilitySystemComponent
		- Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer
 Some problems to avoid:
	1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)
		- Have a different attribute set for every character and avoid inheriting attributes from a parent attribute set
	2) If you unpossess a character and unregister his attribute sets, his attributes are no longer associated with an ASC
		- Don't apply effects to characters that have unregistered attribute sets (it will crash)
			-(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a character and unregisters its attributes and register those attribute sets with the AI ASC)
			-(Possible work around: have an AI controller possess the unpossessed character which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)
*/
UCLASS()
class SONICSHOOTER_API AAbilitySystemCharacter : public ASSCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer);


	/** Inherited via IAbilitySystemInterface. Returns the ASC (either the AI one or the PS one) */
	USSAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAS_Character* GetCharacterAttributeSet() const { return CharacterAttributeSet; }
	UAS_Health* GetHealthAttributeSet() const { return HealthAttributeSet; }

#pragma region AbilitySystemSetup Delegates
	FSetupWithAbilitySystemDelegate SetupWithAbilitySystemCompleted;
	/**
	 * This is broadcasted when the ability system is set up but startup effects aren't applied, default attributes aren't initialized, and
	 * starting abilities aren't granted.
	 */
	FSetupWithAbilitySystemDelegate PreApplyStartupEffects;
	FSetupWithAbilitySystemDelegate OnServerAknowledgeClientSetupAbilitySystem;			// bad idea, server shouldnt have to wait for client
#pragma endregion

	/** These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen) */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Effects")
		TArray<TSubclassOf<UGameplayEffect>> EffectsToApplyOnStartup;

#pragma region Effects
	/** Default attributes values for a Character on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Character's starting attribute values will be on spawn */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Effects")
		TSubclassOf<UGameplayEffect> DefaultAttributeValuesEffectTSub;
#pragma endregion

#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<USSGameplayAbility> CharacterJumpAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterJumpAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<USSGameplayAbility> CharacterCrouchAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterCrouchAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TSubclassOf<USSGameplayAbility> CharacterRunAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterRunAbilitySpecHandle;
#pragma endregion

protected:
	/** Note: No AbilitySpecHandles are tracked upon grant. These are good for passive abilities. These abilities are assigned EAbilityInputID::None */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Abilities")
		TArray<TSubclassOf<USSGameplayAbility>> NonHandleStartingAbilities;



	/** Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|AI")
		EGameplayEffectReplicationMode AIAbilitySystemComponentReplicationMode;

	UPROPERTY()
		ASSPlayerState* SSPlayerState;


	

	virtual void Tick(float DeltaTime) override;

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
	   ---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllCharacterTags() FOR THIS TO DO SOMETHING--- 
	 * Removes all tags relating to this specific character from the PlayerState's ASC
	 * Remove all tags related to the character, that way when we possess a new character,
	 * the old tags don't interfere with the new character.
	 */
	UPROPERTY(EditAnywhere, Category = "AbilitySystemSetup|Config")
		uint8 bRemoveCharacterTagsOnUnpossessed : 1;


	/** Removes all attribute sets that this Character added to the PlayerState's ASC */
	int32 UnregisterCharacterOwnedAttributeSets();
	/** Removes all abilities that this Character added to the PlayerState's ASC */
	int32 RemoveCharacterOwnedAbilities();
	/** NOT IMPLEMENTED YET! Removes all tags relating to this specific character from the PlayerState's ASC */
	void RemoveAllCharacterTags();

	/** Called on the server and client. Override this to create new AttributeSets using NewObject(). This is if you have more than the default one. (call super in the beginning, then add your own logic) */
	virtual void CreateAttributeSets();
	/** Called on the server and client. Override this to register your created AttributeSets (from CreateAttributeSets()) with the ASC. This is if you have more than the default one. (call super in the beginning, then add your own logic) */
	virtual void RegisterAttributeSets();
	/*  Grant abilities from NonHandleStartingAbilities. These are good for passive abilities that don't need to be referenced later. They are granted and do not give back an AbilitySpecHandle. */
	void GrantNonHandleStartingAbilities();
	/** Called only on server. This is the earliest place you can grant an ability. (If overriding, return false if the Super returnes false, then add your own logic) */
	virtual bool GrantStartingAbilities();


#pragma region Input Events
	//Actions
	virtual void OnConfirmTargetPressed();
	virtual void OnConfirmTargetReleased();

	virtual void OnCancelTargetPressed();
	virtual void OnCancelTargetReleased();

	virtual void OnInteractPressed() override;
	virtual void OnInteractReleased() override;

	virtual void OnJumpPressed() override;
	virtual void OnJumpReleased() override;

	virtual void OnCrouchPressed() override;
	virtual void OnCrouchReleased() override;

	virtual void OnRunPressed() override;
	virtual void OnRunReleased() override;

	virtual void OnPrimaryFirePressed() override;
	virtual void OnPrimaryFireReleased() override;

#pragma endregion


private:
	// only one of these ASC will be active at a time
	UPROPERTY(/*Replicated*/)	// Replicated can be helpful for debugging issues
		USSAbilitySystemComponent* PlayerAbilitySystemComponent;
	UPROPERTY()
		USSAbilitySystemComponent* AIAbilitySystemComponent;

	/** Every character will have this attribute set. This is useful because this gives you a place for common attributes that every character should have. Children can make another attribute set specific to their character (ie. UAS_Demoman, UAS_Ganondorf) */
	UPROPERTY(Replicated)
		UAS_Character* CharacterAttributeSet;
	UPROPERTY(Replicated)
		UAS_Health* HealthAttributeSet;


	/** The function that hooks this Character to the ASC. Calls most functions in this base Character class */
	void SetupWithAbilitySystem();
	/** Initialize the Character's attributes using the DefaultAttributeValuesEffect */
	void InitializeAttributes();
	/** Will apply all effects in EffectsToApplyOnStartup. */
	void ApplyStartupEffects();
	/** Notifies server that the client has his ability system all setup. */
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerOnSetupWithAbilitySystemCompletedOnOwningClient();

	/** Indicates that we already created attribute sets and registered them, Initialized the attributes, and applied the startup effects */
	uint8 bAttributesAndStartupEffectsInitialized : 1;
	/** Shows that we already have input binded with the ability system */
	uint8 bASCInputBound : 1;
	/** Indicates we currently should be dealing with the AIAbilitySystemComponent (this is commonly paired with "!IsPlayerControlled()") */
	uint8 bShouldHandleAIAbilitySystemSetup : 1;
};
