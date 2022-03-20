// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacter.h"
#include "Interfaces/ArcInventoryInterface.h"

#include "C_Shooter.generated.h"


class IInteractableInterface;
class UAC_Interactor;
class UArcInventoryComponent;
class UArcInventoryComponent_Shooter;
class UAS_Health;
class UAS_Stamina;



/**
 * Base Shooter Character
 */
UCLASS()
class SONICSHOOTER_API AC_Shooter : public ASSCharacter, public IArcInventoryInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
		UArcInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interactor")
		UAC_Interactor* Interactor;

public:
	AC_Shooter(const FObjectInitializer& ObjectInitializer);


	static const FName InventoryComponentName;
	UArcInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }

	UAC_Interactor* GetInteractorComponent() const { return Interactor; }


	UAS_Health* GetHealthAttributeSet() const { return HealthAttributeSet; }
	UAS_Stamina* GetStaminaAttributeSet() const { return StaminaAttributeSet; }


#pragma region Abilities
	// Inventory Abilities
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToLastActiveItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToLastActiveItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToNextItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToNextItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToPreviousItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToPreviousItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToFirstItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToFirstItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToSecondItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToSecondItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToThirdItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToThirdItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToFourthItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToFourthItemAbilitySpecHandle;
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> SwapToFifthItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapToFifthItemAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Inventory")
		TSubclassOf<UASSGameplayAbility> DropItemAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle DropItemAbilitySpecHandle;
	// -----------------------





	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Interact")
		TSubclassOf<UASSGameplayAbility> InteractInstantAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle InteractInstantAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities|Interact")
		TSubclassOf<UASSGameplayAbility> InteractDurationAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle InteractDurationAbilitySpecHandle;
#pragma endregion

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;

	// BEGIN APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// END APawn Interface

	//BEGIN AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	//END AActor Interface

	virtual void CreateAttributeSets() override;
	virtual void RegisterAttributeSets() override;
	virtual void GiveStartingAbilities() override;

#pragma region Input Events
	virtual void OnInteractPressed() override;

	virtual void OnPrimaryFirePressed() override;

	virtual void OnReloadPressed() override;

	virtual void OnSwitchWeaponPressed() override;
	virtual void OnFirstItemPressed() override;
	virtual void OnSecondItemPressed() override;
	virtual void OnThirdItemPressed() override;
	virtual void OnFourthItemPressed() override;
	virtual void OnFifthItemPressed() override;
	virtual void OnNextItemPressed() override;
	virtual void OnPreviousItemPressed() override;

	virtual void OnPausePressed() override;
	virtual void OnScoreSheetPressed() override;

	virtual void OnDropItemPressed() override;

#pragma endregion

private:
	UPROPERTY(Replicated)
		UAS_Health* HealthAttributeSet;
	UPROPERTY(Replicated)
		UAS_Stamina* StaminaAttributeSet;


	// Cached Inventory
	UArcInventoryComponent_Shooter* ShooterInventoryComponent;

};
