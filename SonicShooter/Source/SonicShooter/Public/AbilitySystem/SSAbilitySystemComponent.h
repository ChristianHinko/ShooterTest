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
	// 0 None
	None				UMETA(DisplayName = "None"),
	// 1 Jump
	Jump				UMETA(DisplayName = "Jump"),
	// 2 Interact
	Interact			UMETA(DisplayName = "Interact"),
	// 3 Run
	Run					UMETA(DisplayName = "Sprint"),
	// 4 PrimaryFire
	PrimaryFire			UMETA(DisplayName = "Primary Fire"),
	// 5 SecondaryFire
	SecondaryFire		UMETA(DisplayName = "Secondary Fire"),
	// 6 Reload
	Reload				UMETA(DisplayName = "Reload"),
	// 7 Crouch
	Crouch				UMETA(DisplayName = "Crouch"),
	// 8 Switch Weapon
	SwitchWeapon		UMETA(DisplayName = "Switch Weapon"),
	// 9 Item0
	Item0				UMETA(DisplayName = "Item0"),
	// 10 Item1
	Item1				UMETA(DisplayName = "Item1"),
	// 11 Item2
	Item2				UMETA(DisplayName = "Item2"),
	// 12 Item3
	Item3				UMETA(DisplayName = "Item3"),
	// 13 Item4
	Item4				UMETA(DisplayName = "Item4"),
	// 14 NextItem
	NextItem			UMETA(DisplayName = "NextItem"),
	// 15 PreviousItem
	PreviousItem		UMETA(DisplayName = "PreviousItem"),
	// 16 Pause
	Pause				UMETA(DisplayName = "Pause"),
	// 17 ScoreSheet
	ScoreSheet			UMETA(DisplayName = "ScoreSheet"),
	// 18 DropItem
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



	FGameplayAbilitySpecHandle GrantAbility(TSubclassOf<UGameplayAbility> NewAbility, UObject* InSourceObject, EAbilityInputID inputID, int32 level = 1);

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
