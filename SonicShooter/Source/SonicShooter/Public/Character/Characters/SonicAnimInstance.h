// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AI_ShooterCharacter.h"

#include "SonicAnimInstance.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USonicAnimInstance : public UAI_ShooterCharacter
{
	GENERATED_BODY()

public:
	USonicAnimInstance(const FObjectInitializer& ObjectInitializer);

	UMaterialInstanceDynamic* REyeDynamicMat;
	UMaterialInstanceDynamic* LEyeDynamicMat;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;



	AActor* LookTarget;

	UPROPERTY(BlueprintReadOnly)
		FRotator RightEyelookRot;
	UPROPERTY(BlueprintReadOnly)
		FRotator LeftEyelookRot;


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


	FRotator Look(FName boneName, AActor* lookTarget, float deltaTime);

};
