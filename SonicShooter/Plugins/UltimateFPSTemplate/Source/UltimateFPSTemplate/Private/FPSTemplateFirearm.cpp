//Copyright 2021, Dakota Dawe, All rights reserved

#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"
#include "FPSTemplateAnimInstance.h"
#include "FPSTemplateStatics.h"
#include "FirearmParts/BaseClasses/FPSTemplate_SightBase.h"
#include "FirearmParts/FPSTemplate_Barrel.h"
#include "FirearmParts/FPSTemplate_Handguard.h"
#include "FirearmParts/FPSTemplate_ForwardGrip.h"
#include "FirearmParts/FPSTemplate_Muzzle.h"
#include "FirearmParts/BaseClasses/FPSTemplate_LightLaserBase.h"
#include "FPSTemplate_PartComponent.h"
#include "FirearmParts/FPSTemplate_FlipMount.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartBase.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSTemplateFirearm::AFPSTemplateFirearm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FirearmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	FirearmMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = FirearmMesh;
	PoseCollision = ECollisionChannel::ECC_GameTraceChannel2;
	
	bReplicates = true;

	FirearmIndex = 0;

	MuzzleSocket = FName("S_Muzzle");
	LeftHandIKSocket = FName("S_LeftHandIK");
	AimSocket = FName("S_Aim");

	bUseLeftHandIK = false;
	GripType = EFirearmGripType::None;

	DefaultFirearmStats.Weight = 7.0f;
	DefaultFirearmStats.Ergonomics = 50.0f;
	DefaultFirearmStats.VerticalRecoil = 110.0f;
	DefaultFirearmStats.HorizontalRecoil = 180.0f;

	ShoulderStockOffset = FVector(-8.0f, 0.0f, 2.0f);

	ControlMovementSwayByStats = true;
	ScaleCameraShakeByStats = true;

	bCanFire = true;
	bCanReFire = true;
	bCanCycleSights = true;
	
	FireModeIndex = 0;
	BurstFireCount = 0;
	BurstCount = 3;

	FireRateRPM = 800.0f;

	TimeSinceLastShot = 0.0f;

	ShortStockPoseDistance = 18.0f;
	FirstPersonSprintPose.SetLocation(FVector(-5.0f, 0.0f, -10.0f));
	FirstPersonSprintPose.SetRotation(FRotator(-45.0f, 0.0f, 20.0f).Quaternion());
	FirstPersonHighPortPose.SetLocation(FVector(-10.0f, 0.0f, -10.0f));
	FirstPersonHighPortPose.SetRotation(FRotator(80.0f, 45.0f, 0.0f).Quaternion());
	FirstPersonLowPortPose.SetLocation(FVector(-10.0f, 0.0f, -10.0f));
	FirstPersonLowPortPose.SetRotation(FRotator(80.0f, -45.0f, 0.0f).Quaternion());

	ThirdPersonSprintPose.SetLocation(FVector(-5.0f, 0.0f, -10.0f));
	ThirdPersonSprintPose.SetRotation(FRotator(-45.0f, 0.0f, 20.0f).Quaternion());
	ThirdPersonHighPortPose.SetLocation(FVector(-10.0f, 0.0f, -3.0f));
	ThirdPersonHighPortPose.SetRotation(FRotator(80.0f, 45.0f, 0.0f).Quaternion());
	ThirdPersonLowPortPose.SetLocation(FVector(0.0f, 8.0f, 8.0f));
	ThirdPersonLowPortPose.SetRotation(FRotator(80.0f, -45.0f, 0.0f).Quaternion());

	AimSwayMultiplier = 0.2f;
}

// Called when the game starts or when spawned
void AFPSTemplateFirearm::BeginPlay()
{
	Super::BeginPlay();

	OwningCharacter = Cast<AFPSTemplateCharacter>(GetOwner());

	if (HasAuthority())
	{
		GetComponents<UFPSTemplate_PartComponent>(PartComponents);
	}
	if (OwningCharacter && OwningCharacter->IsLocallyControlled())
	{
		CycleSights();
	}

	HandleSightComponents();

	// Update initial Default Parts
	FTimerHandle TTemp;
	GetWorldTimerManager().SetTimer(TTemp, this, &AFPSTemplateFirearm::PartsChanged, 0.1f, false);
}

void AFPSTemplateFirearm::PostInitProperties()
{
	Super::PostInitProperties();
	FirearmStats = DefaultFirearmStats;
	if (FireModes.Num())
	{
		FireMode = FireModes[0];
	}
	TimerAutoFireRate = 60 / FireRateRPM;
	FirearmMesh->SetCollisionResponseToChannel(PoseCollision, ECollisionResponse::ECR_Ignore);
}

void AFPSTemplateFirearm::OnRep_Owner()
{
	OwningCharacter = Cast<AFPSTemplateCharacter>(GetOwner());
	RefreshCurrentSight();
}

void AFPSTemplateFirearm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFPSTemplateFirearm, ProjectileToSpawn);
	DOREPLIFETIME(AFPSTemplateFirearm, PartComponents);
	DOREPLIFETIME(AFPSTemplateFirearm, ForwardGripComponent);
	DOREPLIFETIME(AFPSTemplateFirearm, BarrelComponent);
	DOREPLIFETIME(AFPSTemplateFirearm, HandguardComponent);
	DOREPLIFETIME(AFPSTemplateFirearm, SightComponents);
	DOREPLIFETIME(AFPSTemplateFirearm, CurrentSightComponent);
	DOREPLIFETIME(AFPSTemplateFirearm, GripType);
	DOREPLIFETIME(AFPSTemplateFirearm, FirearmStats);
	DOREPLIFETIME_CONDITION(AFPSTemplateFirearm, FireMode, COND_SkipOwner);
}

float AFPSTemplateFirearm::GetStockLengthOfPull()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart() && PartComponent->GetPart()->GetPartType() == EPartType::Stock)
		{
			return PartComponent->GetPart()->GetPartOffset();
		}
	}
	return 0.0f;
}

void AFPSTemplateFirearm::UpdateFirearmStats()
{
	if (HasAuthority())
	{
		FirearmStats = DefaultFirearmStats;
		FFirearmPartStats PartStats;
		for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
		{
			if (PartComponent && IsValid(PartComponent->GetPart()))
			{
				PartStats += PartComponent->GetPart()->GetPartStats();
			}
		}

		FirearmStats.Weight += PartStats.Weight;
		float PercentMultiplier = 1.0f + (PartStats.RecoilChangePercentage / 100.0f);
		FirearmStats.VerticalRecoil *= PercentMultiplier;
		FirearmStats.HorizontalRecoil *= PercentMultiplier;

		PercentMultiplier = 1.0f + (PartStats.ErgonomicsChangePercentage / 100.0f);
		FirearmStats.Ergonomics *= PercentMultiplier;
	}
}

void AFPSTemplateFirearm::HandleSightComponents()
{
	SightComponents.Empty();
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && IsValid(PartComponent->GetPart()))
		{
			if (PartComponent->GetPart()->IsAimable())
			{
				SightComponents.Add(PartComponent);
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetSightComponents())
			{
				if (PartPartComponent && IsValid(PartPartComponent->GetPart()))
				{
					if (PartPartComponent->GetPart()->IsAimable())
					{
						SightComponents.Add(PartPartComponent);
					}
				}
			}
		}
	}
	if (!CurrentSightComponent || (CurrentSightComponent && !IsValid(CurrentSightComponent->GetPart())))
	{
		CycleSights();
	}
}

AFPSTemplateCharacter* AFPSTemplateFirearm::GetOwningCharacter() const
{
	return GetOwner<AFPSTemplateCharacter>();
}

bool AFPSTemplateFirearm::IsSuppressed() const
{
	if (BarrelComponent)
	{
		if (AFPSTemplate_Barrel* Barrel = BarrelComponent->GetPart<AFPSTemplate_Barrel>())
		{
			AFPSTemplate_Muzzle* MuzzleDevice = Barrel->GetMuzzleDevice();
			if (IsValid(MuzzleDevice))
			{
				return MuzzleDevice->IsSuppressor();
			}
		}
	}
	return false;
}

void AFPSTemplateFirearm::CycleFlipMount()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart())
		{
			if (PartComponent->GetPart()->GetPartType() == EPartType::FlipMount)
			{
				if(AFPSTemplate_FlipMount* FlipMount = PartComponent->GetPart<AFPSTemplate_FlipMount>())
				{
					FlipMount->Use();
					return;
				}
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if(AFPSTemplate_FlipMount* FlipMount = PartPartComponent->GetPart<AFPSTemplate_FlipMount>())
				{
					FlipMount->Use();
					return;
				}
			}
		}
	}
}

void AFPSTemplateFirearm::UseLight()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart())
		{
			if (PartComponent->GetPart()->GetPartType() == EPartType::LightLaser)
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->ToggleLight();
				}
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartPartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->ToggleLight();
				}
			}
		}
	}
}

void AFPSTemplateFirearm::UseLaser()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart())
		{
			if (PartComponent->GetPart()->GetPartType() == EPartType::LightLaser)
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->ToggleLaser();
				}
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartPartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->ToggleLaser();
				}
			}
		}
	}
}

void AFPSTemplateFirearm::CycleLaserColor()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && PartComponent->GetPart())
		{
			if (PartComponent->GetPart()->GetPartType() == EPartType::LightLaser)
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->CycleLaserColor();
				}
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if(AFPSTemplate_LightLaserBase* LightLaser = PartPartComponent->GetPart<AFPSTemplate_LightLaserBase>())
				{
					LightLaser->CycleLaserColor();
				}
			}
		}
	}
}

void AFPSTemplateFirearm::CycleReticle()
{
	if (AFPSTemplate_SightBase* Sight = GetCurrentSight())
	{
		Sight->CycleReticle();
	}
}

void AFPSTemplateFirearm::ZoomOptic(bool Zoom)
{
	if (AFPSTemplate_SightBase* Sight = GetCurrentSight())
	{
		if (Zoom)
		{
			Sight->ZoomIn();
		}
		else
		{
			Sight->ZoomOut();
		}
	}
}

void AFPSTemplateFirearm::IncreaseReticleBrightness(bool Increase)
{
	if (AFPSTemplate_SightBase* Sight = GetCurrentSight())
	{
		if (Increase)
		{
			Sight->IncreaseBrightness();
		}
		else
		{
			Sight->DecreaseBrightness();
		}
	}
}

float AFPSTemplateFirearm::GetOpticMagnification() const
{
	if (AFPSTemplate_SightBase* Sight = GetCurrentSight())
	{
		return Sight->GetMagnification();
	}
	return 1.0f;
}

void AFPSTemplateFirearm::IncreaseVerticalZero(bool Increase)
{
	if (AFPSTemplate_SightBase* Sight = GetCurrentSight())
	{
		if (Increase)
		{
			Sight->IncreaseVerticalZero();
		}
		else
		{
			Sight->DecreaseVerticalZero();
		}
	}
}

AFPSTemplate_Muzzle* AFPSTemplateFirearm::GetMuzzleDevice() const
{
	if (BarrelComponent)
	{
		if (AFPSTemplate_Barrel* Barrel = BarrelComponent->GetPart<AFPSTemplate_Barrel>())
		{
			if (Barrel->DoesMuzzleSocketExist())
			{
				return Barrel->GetMuzzleDevice();
			}
		}
	}
	return nullptr;
}

AActor* AFPSTemplateFirearm::GetMuzzleDeviceActor() const
{
	if (BarrelComponent)
	{
		if (AFPSTemplate_Barrel* Barrel = BarrelComponent->GetPart<AFPSTemplate_Barrel>())
		{
			if (Barrel->DoesMuzzleSocketExist())
			{
				return Barrel->GetMuzzleDeviceActor();
			}
		}
	}
	return nullptr;
}

void AFPSTemplateFirearm::DisableAllRenderTargets(bool Disable)
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && IsValid(PartComponent->GetPart()))
		{
			if (PartComponent->GetPart()->HasRenderTarget())
			{
				PartComponent->GetPart()->DisableRenderTarget(Disable);
			}
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if (PartPartComponent && IsValid(PartPartComponent->GetPart()))
				{
					if (PartPartComponent->GetPart()->HasRenderTarget())
					{
						PartPartComponent->GetPart()->DisableRenderTarget(Disable);
					}
				}
			}
		}
	}
}

void AFPSTemplateFirearm::DisableSightRenderTargets(bool Disable)
{
	for (UFPSTemplate_PartComponent* PartComponent : SightComponents)
	{
		if (PartComponent && IsValid(PartComponent->GetPart()))
		{
			if (PartComponent->GetPart()->HasRenderTarget())
			{
				PartComponent->GetPart()->DisableRenderTarget(Disable);
			}
		}
	}
}

void AFPSTemplateFirearm::PartsChanged()
{
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && IsValid(PartComponent->GetPart()))
		{
			switch (PartComponent->GetPart()->GetPartType())
			{
				case EPartType::Barrel : BarrelComponent = PartComponent; break;
				case EPartType::Handguard :
					{
						HandguardComponent = PartComponent;
						if (OwningCharacter && OwningCharacter->GetAnimationInstance())
						{
							OwningCharacter->GetAnimationInstance()->SetGripType(HandguardComponent->GetPart<AFPSTemplate_Handguard>()->GetGripType());
						}
						break;
					}
				case EPartType::ForwardGrip :
					{
						ForwardGripComponent = PartComponent;
						if (OwningCharacter->GetAnimationInstance())
						{
							OwningCharacter->GetAnimationInstance()->SetGripType(ForwardGripComponent->GetPart<AFPSTemplate_ForwardGrip>()->GetGripType());
						}
						break;
					}
			}
		}
	}
	
	HandleSightComponents();
	UpdateFirearmStats();
	OnPartsChanged();
}

TArray<AFPSTemplate_PartBase*> AFPSTemplateFirearm::GetPartsList() const
{
	TArray<AFPSTemplate_PartBase*> Parts;
	for (UFPSTemplate_PartComponent* PartComponent : PartComponents)
	{
		if (PartComponent && IsValid(PartComponent->GetPart()))
		{
			Parts.Add(PartComponent->GetPart());
			for (UFPSTemplate_PartComponent* PartPartComponent : PartComponent->GetPart()->GetPartComponents())
			{
				if (PartPartComponent && IsValid(PartPartComponent->GetPart()))
				{
					Parts.Add(PartPartComponent->GetPart());
				}
			}
		}
	}
	return Parts;
}

FTransform AFPSTemplateFirearm::GetSprintPose() const
{
	if (OwningCharacter)
	{
		if (!OwningCharacter->IsLocallyControlled() || OwningCharacter->IsTrueFirstPersonCharacter())
		{
			return ThirdPersonSprintPose; // THIRD PERSON HERE
		}
		else
		{
			return FirstPersonSprintPose;
		}
	}
	return FirstPersonSprintPose;
}

FTransform AFPSTemplateFirearm::GetHighPortPose() const
{
	if (OwningCharacter)
	{
		if (!OwningCharacter->IsLocallyControlled() || OwningCharacter->IsTrueFirstPersonCharacter())
		{
			return ThirdPersonHighPortPose;
		}
		else
		{
			return FirstPersonHighPortPose;
		}
	}
	return FirstPersonHighPortPose;
}

FTransform AFPSTemplateFirearm::GetLowPortPose() const
{
	if (OwningCharacter)
	{
		if (!OwningCharacter->IsLocallyControlled() || OwningCharacter->IsTrueFirstPersonCharacter())
		{
			return ThirdPersonLowPortPose;
		}
		else
		{
			return FirstPersonLowPortPose;
		}
	}
	return FirstPersonLowPortPose;
}

FVector AFPSTemplateFirearm::GetShortStockPose() const
{
	return FVector(0.0f, ShortStockPoseDistance * -1.0f, 0.0f);
}

void AFPSTemplateFirearm::OnRep_FireMode()
{
	if (OwningCharacter && OwningCharacter->IsLocallyControlled())
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("FIRE MODE CHANGED"));
	OnFireModeChanged();
}

bool AFPSTemplateFirearm::Server_SetFireMode_Validate(EFirearmFireMode NewFireMode)
{
	return true;
}

void AFPSTemplateFirearm::Server_SetFireMode_Implementation(EFirearmFireMode NewFireMode)
{
	FireMode = NewFireMode;
	OnRep_FireMode();
	UE_LOG(LogTemp, Warning, TEXT("Server_SetFireMode_Implementation"));
}

void AFPSTemplateFirearm::CycleFireMode()
{
	if (FireModes.Num() > 1)
	{
		if (++FireModeIndex > FireModes.Num() - 1)
		{
			FireModeIndex = 0;
		}
		FireMode = FireModes[FireModeIndex];
		OnFireModeChanged();
		if (!HasAuthority())
		{
			Server_SetFireMode(FireMode);
		}
	}
}

void AFPSTemplateFirearm::PerformProceduralRecoil(float Multiplier, bool PlayCameraShake)
{
	if (OwningCharacter && OwningCharacter->GetAnimationInstance())
	{
		OwningCharacter->GetAnimationInstance()->PerformRecoil(Multiplier);
		if (PlayCameraShake && FireCameraShake)
		{
			OwningCharacter->PlayCameraShake(FireCameraShake, Multiplier * 1.2f);
		}
	}
}

TArray<UFPSTemplate_PartComponent*> AFPSTemplateFirearm::GetPartComponents() const
{
	TArray<UFPSTemplate_PartComponent*> Parts = PartComponents;
	for (UFPSTemplate_PartComponent* Part : PartComponents)
	{
		if (Part && Part->GetPart())
		{
			Parts.Append(Part->GetPart()->GetPartComponents());
		}
	}
	return Parts;
}

FTransform AFPSTemplateFirearm::GetSightSocketTransform()
{
	if (CurrentSightComponent && IsValid(CurrentSightComponent->GetPart()))
	{
		return CurrentSightComponent->GetPart()->GetAimSocketTransform();
	}
	if (SightComponents.Num() && SightComponents[0] && IsValid(SightComponents[0]->GetPart()))
	{
		return SightComponents[0]->GetPart()->GetAimSocketTransform();
	}
	return FirearmMesh->GetSocketTransform(AimSocket);
}

FTransform AFPSTemplateFirearm::GetLeftHandIKTransform()
{
	if (HandguardComponent)
	{
		AFPSTemplate_Handguard* Handguard = HandguardComponent->GetPart<AFPSTemplate_Handguard>();
		if (IsValid(Handguard))
		{
			return Handguard->GetGripTransform();
		}
	}
	else if (ForwardGripComponent)
	{
		AFPSTemplate_ForwardGrip* ForwardGrip = ForwardGripComponent->GetPart<AFPSTemplate_ForwardGrip>();
		if (IsValid(ForwardGrip))
		{
			return ForwardGrip->GetGripTransform();
		}
	}
	return FirearmMesh->GetSocketTransform(LeftHandIKSocket);
}

FTransform AFPSTemplateFirearm::GetMuzzleSocketTransform()
{
	if (BarrelComponent)
	{
		if (AFPSTemplate_Barrel* Barrel = BarrelComponent->GetPart<AFPSTemplate_Barrel>())
		{
			if (Barrel->DoesMuzzleSocketExist())
			{
				return Barrel->GetMuzzleSocketTransform();
			}
		}
	}
	return FirearmMesh->GetSocketTransform(MuzzleSocket);
}

FTransform AFPSTemplateFirearm::GetMuzzleProjectileSocketTransform(float RangeMeters, float MOA)
{
	RangeMeters *= 100.0f;
	if (RangeMeters > 10000)
	{
		RangeMeters = 10000;
	}
	else if (RangeMeters < 2500)
	{
		RangeMeters = 2500;
	}
	
	FTransform SightTransform = GetSightSocketTransform();
	FTransform MuzzleTransform = GetMuzzleSocketTransform();

	FRotator MuzzleRotation = UFPSTemplateStatics::GetEstimatedMuzzleToScopeZero(MuzzleTransform, SightTransform, RangeMeters);	
	MuzzleRotation = UFPSTemplateStatics::SetMuzzleMOA(MuzzleRotation, MOA);

	MuzzleTransform.SetRotation(MuzzleRotation.Quaternion());
	return MuzzleTransform;
}

void AFPSTemplateFirearm::OnRep_CurrentSightComponent()
{
	if (OwningCharacter && OwningCharacter->GetAnimationInstance())
	{
		if (!OwningCharacter->IsLocallyControlled())
		{
			OwningCharacter->GetAnimationInstance()->CycledSights();
		}
	}
}

bool AFPSTemplateFirearm::Server_CycleSights_Validate(UFPSTemplate_PartComponent* SightComponent)
{
	return true;
}

void AFPSTemplateFirearm::Server_CycleSights_Implementation(UFPSTemplate_PartComponent* SightComponent)
{
	if (SightComponent)
	{
		CurrentSightComponent = SightComponent;
		OnRep_CurrentSightComponent();
	}
}

UFPSTemplate_PartComponent* AFPSTemplateFirearm::GetSightComponent()
{
	for (SightComponentIndex; SightComponentIndex < PartComponents.Num(); ++SightComponentIndex)
	{
		if (UFPSTemplate_PartComponent* PartComponent = SightComponents[SightComponentIndex])
		{
			UE_LOG(LogTemp, Warning, TEXT("Index: %d"), SightComponentIndex);
			if (PartComponent != CurrentSightComponent)
			{
				if (AFPSTemplate_PartBase* Part = PartComponent->GetPart())
				{
					UE_LOG(LogTemp, Warning, TEXT("Part: %s"), *Part->GetName());
					if (Part->GetPartType() == EPartType::Sight)
					{
						UE_LOG(LogTemp, Warning, TEXT("FOUND SIGHT"));
						CurrentSightComponent = PartComponent;
						return CurrentSightComponent;
					}
				}
			}
		}
	}
	return nullptr;
}

void AFPSTemplateFirearm::CycleSights()
{
	if (!bCanCycleSights)
	{
		return;
	}
	
	bool FoundValidSight = false;
	if (SightComponents.Num())
	{
		if (++SightComponentIndex >= SightComponents.Num())
		{
			SightComponentIndex = 0;
		}
		if (UFPSTemplate_PartComponent* SightComponent = SightComponents[SightComponentIndex])
		{
			CurrentSightComponent = SightComponent;
			FoundValidSight = true;
		}
	}
	if (FoundValidSight)
	{
		if (!HasAuthority())
		{
			Server_CycleSights(CurrentSightComponent);
		}
	}
	if (OwningCharacter)
	{
		if (UFPSTemplateAnimInstance* AnimInstance = OwningCharacter->GetAnimationInstance())
		{
			AnimInstance->CycledSights();
		}
	}
}

void AFPSTemplateFirearm::RefreshCurrentSight()
{
	if (!bCanCycleSights)
	{
		return;
	}
	
	if (CurrentSightComponent)
	{
		if (!HasAuthority())
		{
			Server_CycleSights(CurrentSightComponent);
		}
		if (OwningCharacter)
		{
			if (UFPSTemplateAnimInstance* AnimInstance = OwningCharacter->GetAnimationInstance())
			{
				AnimInstance->CycledSights();
			}
		}
	}
}

AFPSTemplate_SightBase* AFPSTemplateFirearm::GetCurrentSight() const
{
	if (CurrentSightComponent)
	{
		return CurrentSightComponent->GetPart<AFPSTemplate_SightBase>();
	}
	return nullptr;
}
