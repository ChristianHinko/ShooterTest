// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"
#include "SiegeCharacter.generated.h"



/**
 *
 */
UCLASS()
class SONICSIEGE_API ASiegeCharacter : public AAbilitySystemCharacter
{
	GENERATED_BODY()

public:
	ASiegeCharacter(const FObjectInitializer& ObjectInitializer);

	// Treated as a stack. Not fully a stack because OnEndOverlap of an interactable we allow removing the element from whatever position it may be
	TArray<IInteractable*> CurrentOverlapInteractablesStack;
	//TArray<IInteractable*> CurrentTriggerBoxesStack;
	FOnFrameOverlapStackChangeDelegate OnElementRemovedFromFrameOverlapInteractablesStack;

	IInteractable* CurrentDetectedInteract;
	IInteractable* LastDetectedInteract;

protected:

	/*UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector CameraSwayAmount;
	UPROPERTY(EditAnywhere, Category = "Config|WeaponSway")
		FVector AddedCameraSwayDuringADS;*/

	//BEGIN AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	//END AActor Interface

	UPROPERTY(EditAnywhere)
		float InteractSweepDistance;
	UPROPERTY(EditAnywhere)
		float InteractSweepRadius;
	FHitResult InteractSweepHitResult;

	UFUNCTION()
		void OnComponentBeginOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IInteractable* ScanForCurrentInteractable(FHitResult& OutHit);

#pragma region Input Events
	virtual void OnInteractPressed() override;

	virtual void OnPrimaryFirePressed() override;
#pragma endregion

};
