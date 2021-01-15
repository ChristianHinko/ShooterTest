// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "Interfaces/ArcInventoryInterface.h"
#include "ShooterCharacter.generated.h"


class IInteractable;
class UInteractorComponent;

/**
 *
 */
UCLASS()
class SONICSHOOTER_API AShooterCharacter : public AAbilitySystemCharacter, public IArcInventoryInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
		class UArcInventoryComponent* InventoryComponent;

public:
	AShooterCharacter(const FObjectInitializer& ObjectInitializer);


	static FName InventoryComponentName;

	class UArcInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }


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
#pragma endregion

protected:

	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;

	//BEGIN AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	//END AActor Interface

	virtual bool GrantStartingAbilities() override;

#pragma region Input Events
	virtual void OnInteractPressed() override;

	virtual void OnPrimaryFirePressed() override;
#pragma endregion

};
