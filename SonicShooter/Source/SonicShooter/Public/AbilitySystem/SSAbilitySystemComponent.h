// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "SSAbilitySystemComponent.generated.h"



class USSGameplayAbility;


/**
 *	Enum that makes GAS aware of which abilities are binded to which input in your project settings.
 *	Each ability must be assigned one of these when granting an ability (unless you don't care about using some of UE4's wait for input AbilityTasks).
 *
 *	Do not forget to update this enum whenever you modify the inputs in your project settings. They must match exactly. =@REVIEW MARKER@=
 *	Also I do not know yet if you need to do a normal input bind in the SetupPlayerInputComponent() for ConfirmTarget and CancelTarget to
 *	manually call the confirm and cancel functions for target actors or if GAS internally listens for those inputs when a TargetActor is active without
 *	the need for you to call a function to activate a confirm or cancel. My guess though is that it does it internally for you when a target actor is active.
 *	Confirm and cancel target was not looked into enough yet to know if it works fully or not yet.
 */
UENUM()
enum class EAbilityInputID : uint8
{
	// 0
	// This means the ability implementor forgot to set an AbilityInputId in their ability's constructor
	Unset				UMETA(DisplayName = "Unset"),
	// 1
	// This means the ability is triggered without input (probably gameplay code)
	NoInput				UMETA(DisplayName = "NoInput"),
	// 2
	Jump				UMETA(DisplayName = "Jump"),
	// 3
	Interact			UMETA(DisplayName = "Interact"),
	// 4
	Run					UMETA(DisplayName = "Run"),
	// 5
	PrimaryFire			UMETA(DisplayName = "Primary Fire"),
	// 6
	SecondaryFire		UMETA(DisplayName = "Secondary Fire"),
	// 7
	Reload				UMETA(DisplayName = "Reload"),
	// 8
	Crouch				UMETA(DisplayName = "Crouch"),
	// 9
	SwitchWeapon		UMETA(DisplayName = "Switch Weapon"),
	// 10
	Item0				UMETA(DisplayName = "Item0"),
	// 11
	Item1				UMETA(DisplayName = "Item1"),
	// 12
	Item2				UMETA(DisplayName = "Item2"),
	// 13
	Item3				UMETA(DisplayName = "Item3"),
	// 14
	Item4				UMETA(DisplayName = "Item4"),
	// 15
	NextItem			UMETA(DisplayName = "NextItem"),
	// 16
	PreviousItem		UMETA(DisplayName = "PreviousItem"),
	// 17
	Pause				UMETA(DisplayName = "Pause"),
	// 18
	ScoreSheet			UMETA(DisplayName = "ScoreSheet"),
	// 19
	DropItem			UMETA(DisplayName = "DropItem")
};

/**
 * Our custom base ability system component
 */
UCLASS()
class SONICSHOOTER_API USSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USSAbilitySystemComponent();


	virtual bool ShouldDoServerAbilityRPCBatch() const override { return true; }

	FGameplayAbilitySpecHandle GrantAbility(TSubclassOf<USSGameplayAbility> NewAbility, UObject* InSourceObject, int32 level = 1);
	void GrantAbilities(TArray<FGameplayAbilitySpec> Abilities);

	/** Gives abilities that an other given ASC has */
	void RecieveAbilitiesFrom(UAbilitySystemComponent* From);

	virtual void TargetConfirmByAbility(UGameplayAbility* AbilityToConfirmTargetOn);
	virtual void TargetCancelByAbility(UGameplayAbility* AbilityToCancelTargetOn);

	/** This override adds a check to see if we should confirm/cancel target actors associated with the InputID on keypress */
	virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo) override;

	/** Version of function in AbilitySystemGlobals that returns correct type */
	static USSAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UGameplayAbility*>& ActiveAbilities);

	/** Returns an ability spec handle from a class. If modifying call MarkAbilitySpecDirty */
	FGameplayAbilitySpecHandle FindAbilitySpecHandleFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject = nullptr);

	// Gameplay Cue Helpers
	void ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	void AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	void RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	/** Not tested yet!!!!!!! Beware. Could also be better optimized I'm sure. Anyways this function resets the ASC as if it were new again. */
	void FullReset();

protected:
	/** This override adds a check to see if we should activate the ability associated with the InputID on keypress, according to bDoNotAutoActivateFromGASBindings*/
	virtual void AbilityLocalInputPressed(int32 InputID) override;


	/**
	 * If false, abilities will activate when a bound input is pressed. Keep this enabled if you don't want this but still want input binded
	 * (because you may want to manually control when it gets called but still want to use the tasks that binded input gives you)
	 */
	uint8 bDoNotAutoActivateFromGASBindings : 1;
	/**
	 * If false, target actors will confirm/cancel when a bound input is pressed. Keep enabled if you don't want this but still want input binded
	 * (because you may want to manually control when confirm/cancel get called but still want to use the tasks that binded input gives you)
	 */
	uint8 bDoNotAutoConfirmAndCancelFromGASBindings : 1;
};