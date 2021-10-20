//Copyright 2021, Dakota Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataTypes.h"
#include "Camera/CameraShakeBase.h"
#include "FPSTemplateCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AFPSTemplateFirearm;

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplateCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* HeadMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	bool bIsTrueFirstPerson;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	bool bUseParentSocketForAiming;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	FName CameraSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	FName CameraSocketParentBone;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	FName WeaponGripSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	float SprintSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	float MaxLookUpAngle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	float MaxLookDownAngle;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentFirearm)
	AFPSTemplateFirearm* CurrentFirearm;
	UFUNCTION()
	void OnRep_CurrentFirearm();

public:
	AFPSTemplateCharacter();

protected:
	virtual void BeginPlay();
	virtual void PostInitProperties() override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly)
	class UFPSTemplateAnimInstance* AnimationInstance;
	
	UPROPERTY(ReplicatedUsing = OnRep_IsAiming)
	bool bIsAiming;
	UFUNCTION()
	void OnRep_IsAiming();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetAiming(bool IsAiming);

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StartAiming();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StopAiming();

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StartSprinting();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StopSprinting();
	UPROPERTY(ReplicatedUsing = OnRep_IsSprinting)
	bool bIsSprinting;
	UFUNCTION()
	void OnRep_IsSprinting();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetSprinting(bool IsSprinting);
	float DefaultWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate")
	float MaxLeanAngle;
	UPROPERTY(ReplicatedUsing = OnRep_Lean)
	ELeaning CurrentLean;
	UFUNCTION()
	void OnRep_Lean();

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void LeanLeft();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void LeanRight();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StopLeanLeft();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StopLeanRight();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetLean(ELeaning Lean);
	bool bLeanLeftDown;
	bool bLeanRightDown;
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void CycleSights();

	UPROPERTY(ReplicatedUsing = OnRep_FreeLook)
	bool bFreeLook;
	UFUNCTION()
	void OnRep_FreeLook();
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Pose")
	void SetFreeLook(bool FreeLook);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetFreeLook(bool FreeLook);

	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	bool bUseAutoPort;
	bool bAutoPortIsHitting;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	float PortDistanceChecking;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	TEnumAsByte<ECollisionChannel> PoseCollision;
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | HighLowPort")
	void SetHighPortPose();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | HighLowPort")
	void SetLowPortPose();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | HighLowPort")
	void StopLowPortPose();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | HighLowPort")
	void StopHighPortPose();
	bool bHighPort;
	bool bLowPort;
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetPortPose(EPortPose NewPortPose);
	UPROPERTY(ReplicatedUsing = OnRep_PortPose)
	EPortPose PortPose;
	UFUNCTION()
	void OnRep_PortPose();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddFirearm(TSubclassOf<AFPSTemplateFirearm> FirearmClass, bool SetAsCurrent = false);

	void SetMinMaxPitch();

	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void MoveForward(float Val);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void MoveRight(float Val);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void TurnAtRate(float Rate);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void LookUpAtRate(float Rate);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	
public:
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Firearm")
	AFPSTemplateFirearm* GetFirearm() const { return CurrentFirearm; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Firearm")
	void SetCurrentFirearm(AFPSTemplateFirearm* Firearm);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Firearm")
	bool IsUsingAutoPort() const { return bUseAutoPort; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Firearm")
	void SetAutoPort(bool UseAutoPort) { bUseAutoPort = UseAutoPort; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Firearm")
	void AddFirearm(TSubclassOf<AFPSTemplateFirearm> FirearmClass, bool SetAsCurrent = false);

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	UFPSTemplateAnimInstance* GetAnimationInstance() const { return AnimationInstance; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	bool GetIsAiming() const { return bIsAiming; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	bool GetIsSprinting() const { return bIsSprinting; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	bool IsTrueFirstPersonCharacter() const { return bIsTrueFirstPerson; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	USkeletalMeshComponent* GetInUseMesh() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	float GetMaxLeanAngle() const { return MaxLeanAngle; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Character")
	float GetSprintSpeed() const { return SprintSpeed; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void PlayCameraShake(TSubclassOf<UCameraShakeBase> CameraShake, float Scale = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	bool UseThirdPersonFirearmMontage() const;
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void RagdollWithImpact(FVector ImpactLocation = FVector::ZeroVector, float ImpactForce = 0.0f);

	FName GetCameraSocket() const;
	
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
