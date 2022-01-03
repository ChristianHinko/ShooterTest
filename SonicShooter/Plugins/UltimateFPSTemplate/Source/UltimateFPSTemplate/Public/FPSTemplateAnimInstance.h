//Copyright 2021, Dakota Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DataTypes.h"

#include "FPSTemplateAnimInstance.generated.h"

class AFPSTemplateFirearm;

UCLASS()
class ULTIMATEFPSTEMPLATE_API UFPSTemplateAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		
public:
	UFPSTemplateAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:	
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	class AFPSTemplateCharacter* Character;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	bool bIsLocallyControlled;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | LeftHandIK")
	int32 FirearmIndex;

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Firearm")
	AFPSTemplateFirearm* Firearm;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Default")
	class UAnimSequence* LeftHandPose;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Toggles")
	bool bUseProceduralSpine;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	float AimInterpolationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	float CycleSightsInterpolationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	float RotationLagResetInterpolationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	float MotionLagResetInterpolationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	FName RightHandBone;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	FTransform RelativeToHandTransform;
	FTransform FinalRelativeHand;
	bool bInterpRelativeToHand;

	bool bFirstRun;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	FTransform SightTransform;
	float SightDistance;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	float AimingAlpha;
	bool bIsAiming;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	FRotator HeadAimingRotation;

	void SetSightTransform();
	void SetRelativeToHand();
	void InterpRelativeToHand(float DeltaSeconds);

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | LeftHandIK")
	FTransform LeftHandIKTransform;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | LeftHandIK")
	EFirearmGripType CurrentGripType;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | LeftHandIK")
	float LeftHandIKAlpha;
	void SetLeftHandIK();

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Actions")
	float RotationAlpha;
	
	bool bInterpAiming;
	bool bInterpCameraZoom;
	void InterpCameraZoom(float DeltaSeconds);
	float DefaultCameraFOV;

	void InterpAimingAlpha(float DeltaSeconds);

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Lag")
	FTransform RotationLagTransform;
	FTransform UnmodifiedRotationLagTransform;
	FRotator OldRotation;
	void SetRotationLag(float DeltaSeconds);

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Lag")
	FTransform MovementLagTransform;
	FTransform UnmodifiedMovementLagTransform;
	FVector OldMovement;
	void SetMovementLag(float DeltaSeconds);
	FVector OldCharacterLocation;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FFirearmStats FirearmStats;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FRotator SpineRotation;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Recoil")
	FTransform RecoilTransform;
	FTransform FinalRecoilTransform;

	void RecoilInterpToZero(float DeltaSeconds);
	void RecoilInterpTo(float DeltaSeconds);

	ELeaning CurrentLean;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FRotator LeanRotation;
	bool bInterpLeaning;
	void InterpLeaning(float DeltaSeconds);
	
	float CurveTimer;
	float VelocityMultiplier;
	void HandleMovementSway(float DeltaSeconds);
	void HandleSprinting();
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FTransform SwayTransform;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FTransform SprintPoseTransform;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	float SprintAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	float CharacterVelocity;

	bool bCustomizingFirearm;

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FTransform WeaponCustomizingTransform;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	float WeaponCustomizingAlpha;

	bool bCanAim;

	bool bInterpPortPose;
	EPortPose PortPose;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	float PortPoseAlpha;

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Poses")
	FTransform CurrentPose;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Poses")
	FVector ShortStockPose;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Poses")
	float ShortStockPoseAlpha;

	FTransform DefaultRelativeToHand;

	bool bFreeLook;

	void InterpPortPose(float DeltaSeconds);
	FRotator OldFreeLookRotation;
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Default")
	FRotator FreeLookRotation;

	FRotator FreeLookReleaseRotation;

	FRotator SpineToInterpTo;
	
public:
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Aiming")
	void SetIsAiming(bool IsAiming);

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Aiming")
	void SetLeaning(ELeaning Lean);
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Actions")
	void SetIsReloading(bool IsReloading, float BlendAlpha = 0.35f);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Actions")
	void SetCanAim(bool CanAim);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Actions")
	void PerformRecoil(float Multiplier = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Actions")
	void ChangingFireMode(bool IsChanging);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Actions")
	void ChamberingRound(bool IsChambering);

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Aiming")
	void CycledSights();

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Default")
	void SetGripType(EFirearmGripType NewGripType);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Default")
	void StopMontages(float BlendOutTime);
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Extra")
	void SetCustomization(bool CustomizeFirearm);
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Extra")
	void SetPortPose(EPortPose Pose);
	void SetPortPoseBlend(EPortPose Pose, float Alpha);
	bool HandleFirearmCollision(EPortPose Pose, float Alpha);
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Extra")
	void SetFreeLook(bool FreeLook);
};
