// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "Interfaces/ArcInventoryInterface.h"
#include "ShooterCharacter.generated.h"


class IInteractable;
class UInteractorComponent;
class UArcInventoryComponent;
class UArcInventoryComponent_Active;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
		class UArcInventoryComponent_Active* InventoryComponentActive;
	/**
	 * This setup, with the static FName InventoryComponentName and SetDefaultSubobjectClass in the constructor allows you to
	 * have a bit of a heirarchy for your character classes. For example, you can have a base class that uses a basic
	 * inventory component and a 'PlayerCharacter' subclass that has an Active inventory component.
	 * It is up to you if you want to go this route.
	*/
	static FName InventoryComponentName;

	class UArcInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }


	UPROPERTY()
		UInteractorComponent* Interactor;

#pragma region Tags
	//FGameplayTag 
#pragma endregion


#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<UGameplayAbility> SwapItemSlotAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle SwapActiveItemAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<UGameplayAbility> InteractInstantAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle InteractInstantAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "ShooterCharacterSetup|Abilities")
		TSubclassOf<UGameplayAbility> InteractDurationAbilityTSub;
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
	virtual void OnSwitchWeaponPressed();

	virtual void OnInteractPressed() override;

	virtual void OnPrimaryFirePressed() override;
#pragma endregion

};
