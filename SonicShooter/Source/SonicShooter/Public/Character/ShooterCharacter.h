// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "ShooterCharacter.generated.h"

class IInteractable;
class UInventoryComponent;
class UInteractorComponent;

/**
 *
 */
UCLASS()
class SONICSHOOTER_API AShooterCharacter : public AAbilitySystemCharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(/*Replicated*/)
		UInventoryComponent* Inventory;
	UPROPERTY()
		UInteractorComponent* Interactor;

#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<USSGameplayAbility> InteractInstantAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle InteractInstantAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<USSGameplayAbility> InteractDurationAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle InteractDurationAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<USSGameplayAbility> CharacterCrouchAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle CharacterCrouchAbilitySpecHandle;
#pragma endregion

	virtual void OnStartCrouch(float HeightAdjust, float ScaledHeightAdjust) override;
	virtual void OnEndCrouch(float HeightAdjust, float ScaledHeightAdjust) override;

protected:

	/*UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;*/

	//BEGIN AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	//END AActor Interface

	virtual bool GrantStartingAbilities() override;

#pragma region Input Events
	virtual void OnInteractPressed() override;

	virtual void OnCrouchPressed() override;

	virtual void OnPrimaryFirePressed() override;
#pragma endregion

};
