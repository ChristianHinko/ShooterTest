// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSAnimInstance.h"
#include "ShooterCharacterAnimInstance.generated.h"

class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UShooterCharacterAnimInstance : public USSAnimInstance
{
	GENERATED_BODY()

		UShooterCharacterAnimInstance();

	public:
		virtual void NativeUpdateAnimation(float DeltaTimeX) override;
		AShooterCharacter* OwningShooterCharacter;

	protected:
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
#pragma region REyeTurning
		UPROPERTY(BlueprintReadOnly)
			FRotator rEyeLookAtRot;
		UPROPERTY(BlueprintReadWrite)
			float rEyeLookAtAlpha;
		UPROPERTY(BlueprintReadWrite)
			float rEyeLookSpeed;
		UPROPERTY(BlueprintReadWrite)
			float rEyeMaxRollRot;
		UPROPERTY(BlueprintReadWrite)
			float rEyeMaxPitchRot;
		UPROPERTY(BlueprintReadWrite)
			float rEyeMaxYawRot;
#pragma endregion
#pragma region LEyeTurning
		UPROPERTY(BlueprintReadOnly)
			FRotator lEyeLookAtRot;
		UPROPERTY(BlueprintReadWrite)
			float lEyeLookAtAlpha;
		UPROPERTY(BlueprintReadWrite)
			float lEyeLookSpeed;
		UPROPERTY(BlueprintReadWrite)
			float lEyeMaxRollRot;
		UPROPERTY(BlueprintReadWrite)
			float lEyeMaxPitchRot;
		UPROPERTY(BlueprintReadWrite)
			float lEyeMaxYawRot;
#pragma endregion



		FRotator GetHeadLookAtTargetRot(AActor* Target, float deltaTime);
		FRotator GetREyeLookAtTargetRot(AActor* Target, float deltaTime);
		FRotator GetLEyeLookAtTargetRot(AActor* Target, float deltaTime);
};
