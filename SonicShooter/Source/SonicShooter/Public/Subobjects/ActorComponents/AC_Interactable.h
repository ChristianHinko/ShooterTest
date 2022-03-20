// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces\InteractableInterface.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "AC_Interactable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SONICSHOOTER_API UAC_Interactable : public UActorComponent, public IInteractableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Interactable();


	// BEGIN IInteractableInterface interface
	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual TSubclassOf<UGameplayEffect> GetInteractableEffectTSub() override;

	virtual void OnInstantInteract(AC_Shooter* InteractingCharacter) override;

	virtual void OnDurationInteractBegin(AC_Shooter* InteractingCharacter) override;
	virtual void InteractingTick(AC_Shooter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime) override;
	virtual void OnDurationInteractEnd(AC_Shooter* InteractingCharacter, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime) override;

	virtual void OnInitialDetect(AC_Shooter* InteractingCharacter) override;
	virtual void OnConsecutiveDetect(AC_Shooter* InteractingCharacter) override;
	virtual void OnEndDetect(AC_Shooter* InteractingCharacter) override;


	// If set to manual and automatic CanActivateAbility() will return false. Automatic and Manual should maybe be separate abilities
	virtual bool GetIsManualInstantInteract() override;
	virtual bool GetIsAutomaticInstantInteract() override;
	virtual bool GetIsManualDurationInteract() override;
	virtual bool GetIsAutomaticDurationInteract() override;

	virtual float GetInteractDuration() override;
	virtual float GetTickInterval() override;
	virtual bool GetShouldDurationInteractableTick() override;
	virtual bool GetShouldSkipFirstTick() override;
	virtual bool GetShouldFireDetectionEvents() override;
	virtual bool GetCanCurrentlyBeInteractedWith() override;
	// END IInteractableInterface interface


protected:



#pragma region ImplementorSetProperties
	// If set to false, character will ignore this interactable and find the next best option for the frame. This is different from returning false in CanActivateInteractAbility() in that this even prevents the player from even having the option to interact (ie. you've already interacted with this). Basicly this completely turns off the interactability until turned back on.
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bCanCurrentlyBeInteractedWith;

	// If set to manual and automatic CanActivateAbility() will return false. Automatic and Manual should maybe be separate abilities
	//-----------------------------------
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bIsManualInstantInteract;
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bIsAutomaticInstantInteract;   //Code to make this work is currently not hooked up
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bIsManualDurationInteract;
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bIsAutomaticDurationInteract;	//Code to make this work is currently not hooked up


	// How long the player needs to hold interact input to interact with this interactable
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		float interactDuration;
	// Time to wait between ticks to help performance. Be careful with this... longer wait between ticks means a less accurate duration end (might over/undershoot interactDuration).
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		float tickInterval;
	// Lets you make use of InteractingTick event
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bShouldDurationInteractableTick;
	// Skips first call to InteractingTick()
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bShouldSkipFirstTick;

	// Allows events to be fired by the character's interaction scanner
	UPROPERTY(EditAnywhere, Category = "InteractableConfig")
		bool bShouldFireDetectionEvents;

#pragma endregion			

};
