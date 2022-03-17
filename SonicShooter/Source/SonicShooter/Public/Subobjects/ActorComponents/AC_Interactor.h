// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Interactor.generated.h"

class AC_Shooter;
class IInteractable;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFrameOverlapStackChangeDelegate, IInteractable*&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SONICSHOOTER_API UAC_Interactor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Interactor();

	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Treated as a stack. Not fully a stack because OnEndOverlap of an interactable we allow removing the element from whatever position it may be
	TArray<IInteractable*> CurrentOverlapInteractablesStack;
	FOnFrameOverlapStackChangeDelegate OnElementRemovedFromFrameOverlapInteractablesStack;

	IInteractable* CurrentPrioritizedInteractable;
	IInteractable* LastPrioritizedInteractable;

	void TryInteract();

protected:
	UPROPERTY(EditAnywhere)
		float InteractSweepDistance;
	UPROPERTY(EditAnywhere)
		float InteractSweepRadius;
	FHitResult InteractSweepHitResult;

	UFUNCTION()
		void OnComponentBeginOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	IInteractable* ScanForCurrentPrioritizedInteractable(FHitResult& OutHit);

private:
	AC_Shooter* OwningShooterCharacter;
};
