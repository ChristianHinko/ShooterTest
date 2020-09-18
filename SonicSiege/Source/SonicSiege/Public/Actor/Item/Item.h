// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AbilitySystemActor.h"
#include "Interfaces/Interactable.h"

#include "Item.generated.h"

class USSGameplayAbility;

enum class EItemType : uint8
{
	TYPE_None,
	TYPE_Gun,
	TYPE_Melee,
	TYPE_
};

/**
 * This should store the info for an Item so we can avoid casting for no reason.
 */
USTRUCT()
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

public:
	AItem* Item;

	EItemType ItemType;
};

/**
 * 
 */
UCLASS()
class SONICSIEGE_API AItem : public AAbilitySystemActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AItem();

	virtual bool CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual TSubclassOf<UGameplayEffect> GetInteractableEffectTSub() override;


	virtual void OnInstantInteract(APawn* InteractingPawn) override;

	virtual void OnDurationInteractBegin(APawn* InteractingPawn) override;
	virtual void InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime) override;
	virtual void OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime) override;

	virtual void OnInitialDetect(APawn* InteractingPawn) override;
	virtual void OnConsecutiveDetect(APawn* InteractingPawn) override;
	virtual void OnEndDetect(APawn* InteractingPawn) override;

protected:
	virtual void PostInitializeComponents() override;
};
