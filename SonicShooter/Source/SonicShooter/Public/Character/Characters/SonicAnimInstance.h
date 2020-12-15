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

	AActor* LookTarget;

	UPROPERTY(BlueprintReadOnly)
		FRotator lookRot;


	UPROPERTY(BlueprintReadWrite)
		float eyeMaxPitchRot;
	UPROPERTY(BlueprintReadWrite)
		float eyeMaxYawRot;
	
	UPROPERTY(BlueprintReadWrite)
		float rEyeLookAtAlpha;
	UPROPERTY(BlueprintReadWrite)
		float eyeLookSpeed;

	UPROPERTY(BlueprintReadWrite)
		float lEyeLookAtAlpha;


	FRotator Look(AActor* lookTarget, float deltaTime);

public:
	USonicAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

	UMaterialInstanceDynamic* REyeDynamicMat;
	UMaterialInstanceDynamic* LEyeDynamicMat;

};
