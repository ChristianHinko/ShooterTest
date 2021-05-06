// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "ExampleAbilitySystemCharacter.generated.h"

class UAS_ExampleAbilitySystemCharacter;
class USSGameplayAbility;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AExampleAbilitySystemCharacter : public AAbilitySystemCharacter
{
	GENERATED_BODY()
	
public:
	AExampleAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer);

protected:
#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "AbilitySystem|Abilities")
		TSubclassOf<USSGameplayAbility> ExampleAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle ExampleAbilitySpecHandle;
#pragma endregion

#pragma region Effects
	// Store your startup and non-startup effects in this region
	// Startup effects don't need any C++ work. Just choose what gets applied in your BP


#pragma endregion

#pragma region AttributeSets
	UPROPERTY(Replicated)
		UAS_ExampleAbilitySystemCharacter* ExampleAbilitySystemCharacterAttributeSet;
#pragma endregion

	//BEGIN AbilitySystemCharacter interface
	virtual void CreateAttributeSets() override;
	virtual void RegisterAttributeSets() override;
	virtual bool GrantStartingAbilities() override;
	//End AbilitySystemCharacter interface


#pragma region Input Events
	virtual void OnPrimaryFirePressed() override;
#pragma endregion

};
