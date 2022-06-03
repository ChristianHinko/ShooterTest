// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem\ASSGameplayAbility.h"
#include "Interfaces/InteractableInterface.h"
#include "GA_CharacterAutoInteract.generated.h"

class AC_Shooter;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGA_CharacterAutoInteract : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_CharacterAutoInteract();

	UPROPERTY()
		TWeakObjectPtr<AC_Shooter> ShooterCharacter;

protected:

	//BEGIN UGameplayAbility Interface
	virtual void OnAvatarSetThatWorks(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//END UGameplayAbility Interface


	void HandleDurationInteractEnded();


#pragma region Gameplay Tags

#pragma endregion
	/*UFUNCTION()
		void OnInteractTick(float DeltaTime, float TimeHeld);
	UFUNCTION()
		void OnRelease(float TimeHeld);
	UFUNCTION()
		void OnInteractionSweepMiss(float TimeHeld);
	UFUNCTION()
		void OnCharacterLeftInteractionOverlap(float TimeHeld);
	UFUNCTION()
		void OnNewInteractionPriority(float TimeHeld);
	UFUNCTION()
		void OnSuccessfullInteract(float TimeHeld);*/
};
