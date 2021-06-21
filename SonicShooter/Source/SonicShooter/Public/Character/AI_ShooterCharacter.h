// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSAnimInstance.h"

#include "AI_ShooterCharacter.generated.h"


class ACharacter;
class AShooterCharacter;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAI_ShooterCharacter : public USSAnimInstance
{
	GENERATED_BODY()

public:
	UAI_ShooterCharacter(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;


	AActor* OwningActor;
	APawn* OwningPawn;
	ACharacter* OwningCharacter;
	AShooterCharacter* OwningShooterCharacter;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		FVector Velocity;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		uint8 bGrounded : 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		uint8 bInAir : 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		uint8 bIsFlying : 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		uint8 bIsSwimming : 1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		uint8 bIsCrouching : 1;

#pragma region HeadTurning
	UPROPERTY(BlueprintReadOnly)
		FRotator headLookAtRot;
	UPROPERTY(BlueprintReadWrite)
		float headLookAtAlpha;
	UPROPERTY(BlueprintReadWrite)
		float headLookSpeed;
	UPROPERTY(BlueprintReadWrite)
		float headMaxRollRot;
	UPROPERTY(BlueprintReadWrite)
		float headMaxPitchRot;
	UPROPERTY(BlueprintReadWrite)
		float headMaxYawRot;
#pragma endregion


	FRotator GetHeadLookAtTargetRot(AActor* Target, float deltaTime);

};
