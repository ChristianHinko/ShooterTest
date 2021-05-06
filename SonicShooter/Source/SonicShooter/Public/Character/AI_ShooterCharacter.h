// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSAnimInstance.h"
#include "AI_ShooterCharacter.generated.h"

class AShooterCharacter;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UAI_ShooterCharacter : public USSAnimInstance
{
	GENERATED_BODY()


	public:
		UAI_ShooterCharacter();
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




		FRotator GetHeadLookAtTargetRot(AActor* Target, float deltaTime);
};
