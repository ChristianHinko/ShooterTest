//Copyright 2021, Dakota Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "Camera/CameraShakeBase.h"
#include "FPSTemplateProjectile.h"
#include "FPSTemplateFirearm.generated.h"

class AFPSTemplate_Muzzle;
class UFPSTemplate_PartComponent;
class UAnimationAsset;
class UAnimMontage;
class UCurveVector;

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplateFirearm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSTemplateFirearm();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate")
	class AFPSTemplateCharacter* OwningCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPSTemplate")
	USkeletalMeshComponent* FirearmMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	int32 FirearmIndex;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Default")
	FFirearmStats DefaultFirearmStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	TArray<EFirearmFireMode> FireModes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Default")
	float FireRateRPM;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Default")
	int32 BurstCount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Default")
	bool bUseLeftHandIK;
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Default")
	EFirearmGripType GripType;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | Default")
	TEnumAsByte<ECollisionChannel> PoseCollision;

	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Fire")
	float TimerAutoFireRate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FName MuzzleSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FName AimSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Sockets")
	FName LeftHandIKSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Aiming")
	FVector ShoulderStockOffset;
	
	UPROPERTY(ReplicatedUsing = OnRep_FireMode, BlueprintReadOnly)
	EFirearmFireMode FireMode;
	int32 FireModeIndex;
	FTimerHandle TFAHandle;
	uint8 BurstFireCount;

	UFUNCTION()
	void OnRep_FireMode();

	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	float ShortStockPoseDistance;

	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform FirstPersonSprintPose;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform FirstPersonHighPortPose;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform FirstPersonLowPortPose;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform ThirdPersonSprintPose;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform ThirdPersonHighPortPose;
	UPROPERTY(EditDefaultsOnly, Category = "FPSTemplate | HighLowPort")
	FTransform ThirdPersonLowPortPose;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Animation")
	UCurveVector* MovementSwayCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Animation")
	bool ControlMovementSwayByStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate | Animation")
	bool ScaleCameraShakeByStats;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Default")
	TSubclassOf<UCameraShakeBase> FireCameraShake;

	UPROPERTY(Replicated)
	FFirearmStats FirearmStats;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPSTemplate | PartComponents")
	TArray<UFPSTemplate_PartComponent*> PartComponents;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPSTemplate | PartComponents")
	TArray<UFPSTemplate_PartComponent*> SightComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Animation")
	float AimSwayMultiplier;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentSightComponent)
	UFPSTemplate_PartComponent* CurrentSightComponent;
	UFUNCTION()
	void OnRep_CurrentSightComponent();
	int32 SightComponentIndex;
	
	UPROPERTY(Replicated)
	UFPSTemplate_PartComponent* BarrelComponent;
	UPROPERTY(Replicated)
	UFPSTemplate_PartComponent* HandguardComponent;
	UPROPERTY(Replicated)
	UFPSTemplate_PartComponent* ForwardGripComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitProperties() override;
	virtual void OnRep_Owner() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_CycleSights(UFPSTemplate_PartComponent* SightComponent);

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	void PerformProceduralRecoil(float Multiplier = 1.0f, bool PlayCameraShake = true);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetFireMode(EFirearmFireMode NewFireMode);

	UFPSTemplate_PartComponent* GetSightComponent();

	void HandleSightComponents();

	UFUNCTION(BlueprintImplementableEvent, Category = "FPSTemplate | Events")
	void OnFireModeChanged();
	UFUNCTION(BlueprintImplementableEvent, Category = "FPSTemplate | Events")
	void OnPartsChanged();

	bool bCanFire;
	bool bCanReFire;
	float TimeSinceLastShot;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "FPSTemplate | Ammo")
	TSubclassOf<AFPSTemplateProjectile> ProjectileToSpawn;

	bool bCanCycleSights;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FPSTemplate | Implementable")
	void Fire();
	virtual void Fire_Implementation() { UE_LOG(LogTemp, Warning, TEXT("Fire Implementation Example")); }
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FPSTemplate | Implementable")
	void StopFire();
	virtual void StopFire_Implementation() { UE_LOG(LogTemp, Warning, TEXT("StopFire Implementation Example")); }
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FPSTemplate | Implementable")
	void Reload();
	virtual void Reload_Implementation() { UE_LOG(LogTemp, Warning, TEXT("Reload Implementation Example")); }
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "FPSTemplate | Implementable")
	void ReloadDropMagazine();
	virtual void ReloadDropMagazine_Implementation() { UE_LOG(LogTemp, Warning, TEXT("ReloadDropMagazine Implementation Example")); }
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Firearm")
	virtual void CycleFireMode();
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Firearm")
	bool IsFirearmDisabled() const { return bCanFire; }

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Attachments")
	AFPSTemplate_SightBase* GetCurrentSight() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Attachments")
	FVector GetStockOffset() const { return ShoulderStockOffset; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Attachments")
	TArray<UFPSTemplate_PartComponent*> GetPartComponents() const;

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Projectile")
	FTransform GetMuzzleSocketTransform();
	// MOA = Minute of angle. 1 MOA = 1 inch of shift at 100 yards
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Projectile")
	FTransform GetMuzzleProjectileSocketTransform(float RangeMeters, float MOA = 1.0f);
	
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	void EnableSightCycling() { bCanCycleSights = true; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	void DisableSightCycling() { bCanCycleSights = false; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	FTransform GetSightSocketTransform();
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	virtual FTransform GetLeftHandIKTransform();
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	EFirearmGripType GetGripState() const { return GripType; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	void CycleSights();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	void RefreshCurrentSight();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	UCurveVector* GetMovementSwayCurve() const { return MovementSwayCurve; }
	bool UseStatsForMovementSway() const { return ControlMovementSwayByStats; }
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	float GetStockLengthOfPull();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Animation")
	float GetAimSwayMultiplier() const { return AimSwayMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Stats")
	void UpdateFirearmStats();
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Stats")
	FFirearmStats GetFirearmStats() const { return FirearmStats; }

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Default")
	int32 GetFirearmIndex() const { return FirearmIndex; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Default")
	USkeletalMeshComponent* GetMesh() const { return FirearmMesh; }
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Default")
	AFPSTemplateCharacter* GetOwningCharacter() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Default")
	EFirearmFireMode GetFireMode() const { return FireMode; };
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Default")
	bool IsSuppressed() const;

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void CycleFlipMount();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void UseLight();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void UseLaser();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void CycleLaserColor();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void CycleReticle();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void ZoomOptic(bool Zoom);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void IncreaseReticleBrightness(bool Increase);
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Part")
	float GetOpticMagnification() const;
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	void IncreaseVerticalZero(bool Increase);
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Part")
	AFPSTemplate_Muzzle* GetMuzzleDevice() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Part")
	AActor* GetMuzzleDeviceActor() const;

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Ammo")
	TSubclassOf<AFPSTemplateProjectile> GetInUseProjectile() const { return ProjectileToSpawn; }

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Render")
	void DisableAllRenderTargets(bool Disable);
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Render")
	void DisableSightRenderTargets(bool Disable);
	
	void PartsChanged();

	TArray<AFPSTemplate_PartBase*> GetPartsList() const;

	FTransform GetSprintPose() const;
	FTransform GetHighPortPose() const;
	FTransform GetLowPortPose() const;
	FVector GetShortStockPose() const;
	float GetShortStockDistance() const { return ShortStockPoseDistance; }

	bool UseLeftHandIK() const { return bUseLeftHandIK; }

	const FName& GetAimSocket() const { return AimSocket; }
};