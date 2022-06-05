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



/**
 * Base Shooter Character
 */
UCLASS()
class SONICSHOOTER_API AC_Shooter : public ASSCharacter, public IArcInventoryInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory")
		TObjectPtr<UArcInventoryComponent> InventoryComponent;
	static const FName InventoryComponentName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interactor")
		TObjectPtr<UAC_Interactor> Interactor;

public:
	AC_Shooter(const FObjectInitializer& ObjectInitializer);


	// Subobject getters
	UArcInventoryComponent* GetInventoryComponent() const override { return InventoryComponent; }
	UAC_Interactor* GetInteractorComponent() const { return Interactor; }

protected:
	//BEGIN AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//END AActor Interface


	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;


	//BEGIN Input actions
	virtual void OnPressedInteract() override;

	virtual void OnPressedPrimaryFire() override;

	virtual void OnPressedReload() override;

	virtual void OnPressedSwapToPreviousSlot() override;
	virtual void OnPressedSwapToLayout1st() override;
	virtual void OnPressedSwapToLayout2nd() override;
	virtual void OnPressedSwapToLayout3rd() override;
	virtual void OnPressedSwapToLayout4th() override;
	virtual void OnPressedSwapToLayout5th() override;
	virtual void OnPressedSwapToLayoutForward() override;
	virtual void OnPressedSwapToLayoutBackward() override;

	virtual void OnPressedPause() override;
	virtual void OnPressedScoreSheet() override;

	virtual void OnPressedDropItem() override;
	//END Input actions

private:
	// Cached Inventory
	UPROPERTY()
		TWeakObjectPtr<UArcInventoryComponent_Shooter> ShooterInventoryComponent;

};
