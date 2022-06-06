// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSAnimInstance_ShooterCharacter.h"

#include "SSAnimInstance_Sonic.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSAnimInstance_Sonic : public USSAnimInstance_ShooterCharacter
{
	GENERATED_BODY()

public:
	USSAnimInstance_Sonic(const FObjectInitializer& ObjectInitializer);

	UMaterialInstanceDynamic* REyeDynamicMat;
	UMaterialInstanceDynamic* LEyeDynamicMat;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;


	UPROPERTY()
		TWeakObjectPtr<AActor> LookTarget;

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
