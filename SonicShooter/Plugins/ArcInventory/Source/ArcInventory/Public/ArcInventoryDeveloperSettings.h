// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTags.h"
#include "ArcInventoryDeveloperSettings.generated.h"

//Note: These Enums need to correspond to the Input config file
UENUM(BlueprintType)
enum class EArcAbilityInputs : uint8
{
	PrimaryUse,
	SecondaryUse,
	UseAbility1,
	UseAbility2,
	UseAbility3,
	UseAbility4,
	UseAbility5,

	Interact,
	NextWeapon,
	PreviousWeapon,

	Reload,


	ConfirmTarget,
	CancelTarget,

	//Jump, //TODO: Add Abilities
	//Crouch, 

};

/**
 * 
 */
UCLASS(config=Game, defaultconfig)
class ARCINVENTORY_API UArcInventoryDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UArcInventoryDeveloperSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities", config)
	TMap<FGameplayTag, EArcAbilityInputs> AbilityTagMappings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", config)
	TSubclassOf<class UArcItemStack> DefaultItemStackClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items", config)
	TSubclassOf<class AArcItemStackWorldObject> ItemStackWorldObjectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", config)
	FGameplayTag EquippedSlotTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", config)
	FGameplayTag ActiveItemSlotTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", config)
		FGameplayTag BagItemSlotTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", config)
	FGameplayTagContainer ItemSlotSwapAbilityTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags", config)
	FGameplayTagContainer ItemSlotDropAbilityTags;
		
};
