// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ShooterCharacterAnimInstance.h"
#include "SonicAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USonicAnimInstance : public UShooterCharacterAnimInstance
{
	GENERATED_BODY()

protected:
#pragma region REyeTurning
	UPROPERTY(BlueprintReadOnly)
		FRotator lookAtTargetRot;

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

public:
	USonicAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	UMaterialInstanceDynamic* REyeDynamicMat;
	UMaterialInstanceDynamic* LEyeDynamicMat;

};
