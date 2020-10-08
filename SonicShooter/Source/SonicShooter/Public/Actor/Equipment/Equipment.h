// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AbilitySystemActor.h"
#include "Interfaces/Interactable.h"

#include "Equipment.generated.h"

class USSGameplayAbility;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AEquipment : public AAbilitySystemActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AEquipment();

	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual TSubclassOf<UGameplayEffect> GetInteractableEffectTSub() override;


	virtual void OnInstantInteract(AShooterCharacter* InteractingCharacter) override;

	virtual void OnDurationInteractBegin(AShooterCharacter* InteractingCharacter) override;
	virtual void InteractingTick(AShooterCharacter* InteractingCharacter, float DeltaTime, float CurrentInteractionTime) override;
	virtual void OnDurationInteractEnd(AShooterCharacter* InteractingCharacter, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime) override;

	virtual void OnInitialDetect(AShooterCharacter* InteractingCharacter) override;
	virtual void OnConsecutiveDetect(AShooterCharacter* InteractingCharacter) override;
	virtual void OnEndDetect(AShooterCharacter* InteractingCharacter) override;

protected:
	virtual void PostInitializeComponents() override;
};
