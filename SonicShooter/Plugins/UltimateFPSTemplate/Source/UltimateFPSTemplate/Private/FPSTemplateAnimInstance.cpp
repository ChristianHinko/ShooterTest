//Copyright 2021, Dakota Dawe, All rights reserved

#include "FPSTemplateAnimInstance.h"
#include "FPSTemplateFirearm.h"
#include "FPSTemplateCharacter.h"
#include "FPSTemplateProjectile.h"
#include "FirearmParts/BaseClasses/FPSTemplate_SightBase.h"

#include "DrawDebugHelpers.h"
#include "FPSTemplateStatics.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Curves/CurveVector.h"
#include "GameFramework/PawnMovementComponent.h"

UFPSTemplateAnimInstance::UFPSTemplateAnimInstance()
{
	AimInterpolationSpeed = 20.0f;
	CycleSightsInterpolationSpeed = 20.0f;
	RotationLagResetInterpolationSpeed = 20.0f;
	MotionLagResetInterpolationSpeed = 20.0f;

	bIsLocallyControlled = false;
	
	bInterpRelativeToHand = false;
	bFirstRun = true;
	bIsAiming = false;
	AimingAlpha = 0.0f;
	LeftHandIKAlpha = 1.0f;
	RotationAlpha = false;
	bInterpAiming = false;
	RightHandBone = FName("hand_r");

	CurrentLean = ELeaning::None;

	HeadAimingRotation = FRotator(45.0f, 0.0f, 0.0f);

	SightDistance = 0.0f;

	CurrentGripType = EFirearmGripType::None;

	CurveTimer = 1.0f;

	bCustomizingFirearm = false;
	bCanAim = true;

	bInterpPortPose = false;

	bFreeLook = false;

	ShortStockPoseAlpha = 0.0f;

	bUseProceduralSpine = true;
}

void UFPSTemplateAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	Character = Cast<AFPSTemplateCharacter>(GetOwningActor());
	if (Character)
	{
		DefaultCameraFOV = Character->GetFirstPersonCameraComponent()->FieldOfView;
		OldRotation = Character->GetControlRotation();
		SpineRotation = Character->GetBaseAimRotation();
		bIsLocallyControlled = Character->IsLocallyControlled();
	}
	
	FTimerHandle TTempRelative;
	GetWorld()->GetTimerManager().SetTimer(TTempRelative, this, &UFPSTemplateAnimInstance::SetRelativeToHand, 0.1f, false);
}

void UFPSTemplateAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!Character || bCustomizingFirearm) { return; }

	/*FVector Location = Character->GetInUseMesh()->GetSocketLocation(FName("VB Sight"));
	DrawDebugSphere(GetWorld(), Location, 4.0f, 12.0f, FColor::Blue);
	Location = Character->GetInUseMesh()->GetSocketLocation(FName("VB Hand_r"));
	DrawDebugSphere(GetWorld(), Location, 4.0f, 12.0f, FColor::Red);
	Location = Character->GetInUseMesh()->GetSocketLocation(FName("VB Hand_l"));
	DrawDebugSphere(GetWorld(), Location, 4.0f, 12.0f, FColor::Red);
	FVector PoseLocation = CurrentPose.GetLocation();
	UE_LOG(LogTemp, Warning, TEXT("X: %f	Y: %f	Z: %f"), PoseLocation.X, PoseLocation.Y, PoseLocation.Z);*/
	Firearm = Character->GetFirearm();
	if (Firearm)
	{
		if (PortPose == EPortPose::None)
		{
			InterpRelativeToHand(DeltaSeconds);
		}

		if (Firearm->UseLeftHandIK())
		{
			SetLeftHandIK();
		}
		else
		{
			LeftHandIKAlpha = 0.0f;
		}
		
		if (bInterpAiming)
		{
			InterpAimingAlpha(DeltaSeconds);
		}
		
		if (Character->IsLocallyControlled())
		{
			if (bInterpCameraZoom)
			{
				InterpCameraZoom(DeltaSeconds);
			}
			SetRotationLag(DeltaSeconds);
			if (Character->GetMovementComponent()->Velocity.Size() || !MovementLagTransform.Equals(FTransform()))
			{
				SetMovementLag(DeltaSeconds);
			}

			HandleMovementSway(DeltaSeconds);
		}

		HandleSprinting();

		if (!FinalRecoilTransform.GetRotation().Rotator().Equals(FRotator::ZeroRotator) && !FinalRecoilTransform.GetLocation().Equals(FVector::ZeroVector))
		{
			RecoilInterpToZero(DeltaSeconds);
			RecoilInterpTo(DeltaSeconds);
		}

		if (bInterpPortPose)
		{
			InterpPortPose(DeltaSeconds);
		}
		
		FVector Velocity = Character->GetMovementComponent()->Velocity;
		Velocity.Z = 0.0f;
		CharacterVelocity = Velocity.Size();
	}

	if (bFreeLook)
	{
		FRotator AimRotation = Character->GetBaseAimRotation();
		AimRotation.Yaw += Character->GetActorRotation().Yaw;
		AimRotation.Pitch *= -1.0f - SpineToInterpTo.Roll;
		
		SpineToInterpTo = SpineRotation;
		FreeLookRotation = AimRotation;
	}
	else if (bUseProceduralSpine)
	{
		SpineToInterpTo = Character->GetBaseAimRotation();
		SpineToInterpTo.Roll = SpineToInterpTo.Pitch * -1.0f;
		SpineToInterpTo.Pitch = 0.0f;
		SpineToInterpTo.Yaw = 0.0f;
		if (!Character->IsLocallyControlled())
		{
			SpineRotation = UKismetMathLibrary::RInterpTo(SpineRotation, SpineToInterpTo, DeltaSeconds, 10.0f);
		}
		else
		{
			SpineRotation = SpineToInterpTo;
		}
	}

	if (bUseProceduralSpine && bInterpLeaning)
	{
		InterpLeaning(DeltaSeconds);
	}
}

void UFPSTemplateAnimInstance::InterpRelativeToHand(float DeltaSeconds)
{
	// Change InterpSpeed to weight of firearm
	FirearmIndex = Firearm->GetFirearmIndex();
	
	float InterpSpeed = AimInterpolationSpeed;
	float Multiplier = Firearm->GetFirearmStats().Ergonomics * (10.0f / (Firearm->GetFirearmStats().Weight * 1.5f));
	Multiplier = UKismetMathLibrary::NormalizeToRange(Multiplier, -40.0f, 150.0f);
	Multiplier = FMath::Clamp(Multiplier, 0.0f, 1.0f);
	InterpSpeed *= Multiplier;
	
	// Change InterpSpeed to be modified by firearm in hand
	RelativeToHandTransform = UKismetMathLibrary::TInterpTo(RelativeToHandTransform, FinalRelativeHand, DeltaSeconds, InterpSpeed);
	
	float HandToSightDistance = 30.0f;
	if (Firearm)
	{
		HandToSightDistance = FinalRelativeHand.GetLocation().X;
		HandToSightDistance -= Firearm->GetStockLengthOfPull() / 2.0f;
		SightDistance = UKismetMathLibrary::FInterpTo(SightDistance, HandToSightDistance * -1.0f, DeltaSeconds, InterpSpeed);
		SetSightTransform();
	}

	if (RelativeToHandTransform.Equals(FinalRelativeHand))
	{
		bInterpRelativeToHand = false;
		SightDistance = HandToSightDistance * -1.0f;
		SetSightTransform();
	}
}

void UFPSTemplateAnimInstance::SetSightTransform()
{
	FTransform CameraTransform = Character->GetInUseMesh()->GetSocketTransform(Character->GetCameraSocket(), RTS_ParentBoneSpace);
	const FTransform NewTransform = Character->GetFirstPersonCameraComponent()->GetSocketTransform(NAME_None, RTS_ParentBoneSpace);

	FRotator NewRot = NewTransform.GetRotation().Rotator();
	NewRot.Roll += -90.0f;
	NewRot.Yaw += 90.0f;
	CameraTransform.SetRotation(NewRot.Quaternion());
	
	FVector CameraVector = CameraTransform.GetLocation();
	CameraVector.Y += SightDistance + 10.0f;

	if (!Character->IsLocallyControlled())
	{
		FVector StockOffset = FVector(-8.0f, 0.0f, 2.0f);
		StockOffset = Firearm->GetStockOffset() * -1.0f;
		StockOffset.Y += Firearm->GetStockLengthOfPull();
		
		CameraVector.X += StockOffset.Z * -1.0f;
		CameraVector.Z += StockOffset.X;
		CameraVector.Y += StockOffset.Y;
	}
		
	CameraTransform.SetLocation(CameraVector);
	SightTransform = CameraTransform;
}

void UFPSTemplateAnimInstance::SetRelativeToHand()
{
	if (Firearm)
	{
		const FTransform SightSocketTransform = Firearm->GetSightSocketTransform();
		const FTransform Hand_RTransform = Character->GetInUseMesh()->GetSocketTransform(RightHandBone);
		FinalRelativeHand = UKismetMathLibrary::MakeRelativeTransform(SightSocketTransform, Hand_RTransform);

		FTransform DefaultTransform = Firearm->GetMesh()->GetSocketTransform(Firearm->GetAimSocket());
		DefaultRelativeToHand = UKismetMathLibrary::MakeRelativeTransform(DefaultTransform, Hand_RTransform);
		bInterpRelativeToHand = true;
	}
}

void UFPSTemplateAnimInstance::SetLeftHandIK()
{
	if (!Firearm) { return; }
	const FTransform LeftHandIK = Firearm->GetLeftHandIKTransform();
	if (LeftHandIK.GetLocation().Equals(FVector::ZeroVector)) { LeftHandIKAlpha = 0.0f; return; }
	FVector OutPosition;
	FRotator OutRotation;

	Character->GetInUseMesh()->TransformToBoneSpace(RightHandBone, LeftHandIK.GetLocation(), LeftHandIK.Rotator(), OutPosition, OutRotation);

	LeftHandIKTransform.SetLocation(OutPosition);
	LeftHandIKTransform.SetRotation(OutRotation.Quaternion());
	LeftHandIKTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void UFPSTemplateAnimInstance::InterpPortPose(float DeltaSeconds)
{
	if (Firearm)
	{
		FTransform InterpTo = SightTransform;
		switch (PortPose)
		{
		case EPortPose::High: InterpTo = Firearm->GetHighPortPose(); break;
		case EPortPose::Low: InterpTo = Firearm->GetLowPortPose(); break;
		default: InterpTo = FTransform();
		}
	
		CurrentPose = UKismetMathLibrary::TInterpTo(CurrentPose, InterpTo, DeltaSeconds, 8.0f);
		
		if (CurrentPose.Equals(InterpTo, 12.0f) && PortPose == EPortPose::None)
		{
			PortPoseAlpha = 0.0f;
		}
		
		if (CurrentPose.Equals(InterpTo))
		{
			bInterpPortPose = false;
		}
	}
}

void UFPSTemplateAnimInstance::SetPortPose(EPortPose Pose)
{
	if (PortPose != Pose)
	{
		PortPose = Pose;
		if (PortPose != EPortPose::None)
		{
			CurrentPose = FTransform();
			SetIsAiming(false);
		}

		RelativeToHandTransform = DefaultRelativeToHand;
		PortPoseAlpha = 1.0f;
		bInterpPortPose = true;
	}
}

void UFPSTemplateAnimInstance::SetPortPoseBlend(EPortPose Pose, float Alpha)
{
	if (Firearm)
	{
		PortPose = Pose;
		PortPoseAlpha = Alpha;
	
		if (Pose == EPortPose::None)
		{
			return;
		}

		SetIsAiming(false);

		/*Alpha = FMath::Clamp(Alpha, 0.01f, 1.0f);
		FVector ShortPose = Firearm->GetShortStockPose() * Alpha;

		if (FVector::Distance(ShortStockPose, ShortPose) < Firearm->GetShortStockDistance() / 2.0f)
		{
			PortPose = EPortPose::None;
		}*/
	
		RelativeToHandTransform = DefaultRelativeToHand;
		bInterpPortPose = true;
	}
}

bool UFPSTemplateAnimInstance::HandleFirearmCollision(EPortPose Pose, float Alpha)
{
	if (Firearm)
	{
		if (PortPose == EPortPose::None)
		{
			FVector ShortPose = Firearm->GetShortStockPose();
			//Alpha = FMath::Clamp(Alpha, 0.01f, 1.0f);
			ShortStockPose = UKismetMathLibrary::VInterpTo(ShortStockPose, ShortPose * Alpha, GetWorld()->DeltaTimeSeconds, 10.0f);
			float Diff = FVector::Distance(ShortPose, ShortStockPose);
			
			ShortStockPoseAlpha = 1.0f;
			if (ShortStockPose.Equals(ShortPose, 5.0f))
			{
				ShortStockPoseAlpha = 0.0f;
				ShortStockPose = FVector::ZeroVector;
				SetPortPoseBlend(Pose, Alpha);
				return true;
			}
			return false;
		}
		else
		{
			ShortStockPoseAlpha = 0.0f;
			ShortStockPose = FVector::ZeroVector;
			SetPortPoseBlend(Pose, Alpha);
			return true;
		}
	}
	return false;
}

void UFPSTemplateAnimInstance::SetFreeLook(bool FreeLook)
{
	if (!FreeLook)
	{
		if (Character->IsLocallyControlled() && Character->Controller)
		{
			Character->Controller->SetControlRotation(FreeLookReleaseRotation);
		}
		FreeLookRotation = FRotator::ZeroRotator;
		SpineToInterpTo = Character->GetBaseAimRotation();
	}
	else
	{
		SpineToInterpTo = Character->GetBaseAimRotation();
		SpineToInterpTo.Roll = SpineToInterpTo.Pitch * -1.0f;
		SpineToInterpTo.Pitch = 0.0f;
		SpineToInterpTo.Yaw = 0.0f;
		FreeLookReleaseRotation = Character->GetControlRotation();
	}
	
	bFreeLook = FreeLook;
}

void UFPSTemplateAnimInstance::InterpCameraZoom(float DeltaSeconds)
{
	float CurrentFOV = Character->GetFirstPersonCameraComponent()->FieldOfView;
	float TargetFOV = DefaultCameraFOV;
	float InterpSpeed = 10.0f;
	if (bIsAiming && Firearm)
	{
		if (AFPSTemplate_SightBase* Sight = Firearm->GetCurrentSight())
		{
			TargetFOV -= Sight->GetCameraFOVZoom();
			InterpSpeed = Sight->GetCameraFOVZoomSpeed();
		}
	}
	CurrentFOV = UKismetMathLibrary::FInterpTo(CurrentFOV, TargetFOV, DeltaSeconds, InterpSpeed);
	Character->GetFirstPersonCameraComponent()->SetFieldOfView(CurrentFOV);
	if (CurrentFOV == TargetFOV)
	{
		bInterpCameraZoom = false;
	}
}

void UFPSTemplateAnimInstance::InterpAimingAlpha(float DeltaSeconds)
{
	// Change InterpSpeed to weight of firearm
	float InterpSpeed = AimInterpolationSpeed;
	float Multiplier = Firearm->GetFirearmStats().Ergonomics * (10.0f / (Firearm->GetFirearmStats().Weight * 1.5f));
	Multiplier = UKismetMathLibrary::NormalizeToRange(Multiplier, -40.0f, 150.0f);
	Multiplier = FMath::Clamp(Multiplier, 0.0f, 1.0f);
	InterpSpeed *= Multiplier;

	AimingAlpha = UKismetMathLibrary::FInterpTo(AimingAlpha, bIsAiming, DeltaSeconds, InterpSpeed);
		
	if ((bIsAiming && AimingAlpha >= 1.0f) || (!bIsAiming && AimingAlpha <= 0.0f))
	{
		bInterpAiming = false;
	}
}

void UFPSTemplateAnimInstance::SetRotationLag(float DeltaSeconds)
{
	float InterpSpeed = RotationLagResetInterpolationSpeed;
	float Multiplier = Firearm->GetFirearmStats().Ergonomics * (10.0f / (Firearm->GetFirearmStats().Weight * 1.5f));
	Multiplier = UKismetMathLibrary::NormalizeToRange(Multiplier, -40.0f, 150.0f);
	Multiplier = FMath::Clamp(Multiplier, 0.0f, 1.0f);
	InterpSpeed *= Multiplier;
	
	const FRotator CurrentRotation = Character->GetControlRotation();
	FRotator Rotation = UKismetMathLibrary::RInterpTo(UnmodifiedRotationLagTransform.Rotator(), CurrentRotation - OldRotation, DeltaSeconds, InterpSpeed);
	UnmodifiedRotationLagTransform.SetRotation(Rotation.Quaternion());

	// Modify on HELD weapon weight	
	float FirearmWeightMultiplier = UKismetMathLibrary::NormalizeToRange(Firearm->GetFirearmStats().Weight, 0.0f, 25.0f);
	FirearmWeightMultiplier = FirearmWeightMultiplier * (0.3f / Multiplier);

	Rotation *= 3.0f;
	Rotation *= FirearmWeightMultiplier;
	
	Rotation.Roll = Rotation.Pitch;
	Rotation.Pitch = 0.0f;
	Rotation.Yaw = FMath::Clamp(Rotation.Yaw, -7.0f, 7.0f) * -1.0f;	
	Rotation.Roll = FMath::Clamp(Rotation.Roll, -3.0f, 3.0f);

	RotationLagTransform.SetRotation(Rotation.Quaternion());
	RotationLagTransform.SetLocation(FVector(Rotation.Yaw / 4.0f, 0.0f, Rotation.Roll / 1.5));

	OldRotation = CurrentRotation;
}

void UFPSTemplateAnimInstance::SetMovementLag(float DeltaSeconds)
{
	const FVector Velocity = Character->GetMovementComponent()->Velocity;
	float FowardSpeed = FVector::DotProduct(Velocity, Character->GetActorForwardVector());
	float RightSpeed = FVector::DotProduct(Velocity, Character->GetActorRightVector());
	float VerticalSpeed = Velocity.Z;
	FowardSpeed = UKismetMathLibrary::NormalizeToRange(FowardSpeed, 0.0f, 5.0f);
	RightSpeed = UKismetMathLibrary::NormalizeToRange(RightSpeed, 0.0f, 75.0f);
	VerticalSpeed = UKismetMathLibrary::NormalizeToRange(VerticalSpeed, 0.0f, 75.0f);
	
	float InterpSpeed = MotionLagResetInterpolationSpeed;
	float Multiplier = Firearm->GetFirearmStats().Ergonomics * (10.0f / (Firearm->GetFirearmStats().Weight * 1.5f));
	Multiplier = UKismetMathLibrary::NormalizeToRange(Multiplier, -40.0f, 150.0f);
	Multiplier = FMath::Clamp(Multiplier, 0.0f, 1.0f);
	InterpSpeed *= Multiplier;
	InterpSpeed *= 0.1f;

	FRotator NewRot = MovementLagTransform.GetRotation().Rotator();
	NewRot.Pitch = UKismetMathLibrary::FInterpTo(NewRot.Pitch, RightSpeed, DeltaSeconds, 10.0f);
	NewRot.Roll = UKismetMathLibrary::FInterpTo(NewRot.Roll, VerticalSpeed, DeltaSeconds, 10.0f);
	
	MovementLagTransform.SetRotation(NewRot.Quaternion());
}

void UFPSTemplateAnimInstance::InterpLeaning(float DeltaSeconds)
{
	float LeanAngle = 0.0f;
	const float MaxAngle = Character->GetMaxLeanAngle();
	float CurrentLeanAngle = LeanRotation.Pitch;
	switch (CurrentLean)
	{
		case ELeaning::None : break;
		case ELeaning::Left : LeanAngle = MaxAngle * -1.0f; break;
		case ELeaning::Right : LeanAngle = MaxAngle; break;
	}

	CurrentLeanAngle = UKismetMathLibrary::FInterpTo(CurrentLeanAngle, LeanAngle / 2.0f, DeltaSeconds, 10.0f);
	
	LeanRotation.Pitch = CurrentLeanAngle;
	if (CurrentLeanAngle >= MaxAngle || CurrentLeanAngle <= MaxAngle * -1.0f)
	{
		bInterpLeaning = false;
	}
}

void UFPSTemplateAnimInstance::HandleMovementSway(float DeltaSeconds)
{
	if (Firearm)
	{
		if (UCurveVector* Curve = Firearm->GetMovementSwayCurve())
		{
			const float OldVelocityMultiplier = VelocityMultiplier;
			VelocityMultiplier = UKismetMathLibrary::NormalizeToRange(CharacterVelocity, 0.0f, Character->GetSprintSpeed());
			if (VelocityMultiplier < OldVelocityMultiplier)
			{
				VelocityMultiplier = UKismetMathLibrary::FInterpTo(OldVelocityMultiplier, VelocityMultiplier, DeltaSeconds, 3.2f);
			}
			if (VelocityMultiplier < 0.25f)
			{
				VelocityMultiplier = 0.25f;
			}
			float Multiplier = 1.1f;
			if (Firearm->UseStatsForMovementSway())
			{
				FFirearmStats Stats = Firearm->GetFirearmStats();
				Multiplier = Stats.Weight * (Stats.Weight * 3.0f / (Stats.Ergonomics * 1.5f)) + 1.0f;
			}
			
			CurveTimer += (DeltaSeconds * VelocityMultiplier);
			FVector Graph = Curve->GetVectorValue(CurveTimer);
			Graph *= VelocityMultiplier * Multiplier;
			FRotator Rotation = FRotator(Graph.Y, Graph.X, Graph.Z);
			Rotation *= Firearm->GetAimSwayMultiplier();
			SwayTransform.SetLocation(Graph);
			SwayTransform.SetRotation(Rotation.Quaternion());
		}
	}
}

void UFPSTemplateAnimInstance::HandleSprinting()
{
	if (Character->GetIsSprinting() && CharacterVelocity > Character->GetSprintSpeed() / 2.0f)
	{
		SprintAlpha = 1.0f;
		SetIsAiming(false);
		SprintPoseTransform = Firearm->GetSprintPose();
	}
	else
	{
		if (Character->GetIsAiming())
		{
			SetIsAiming(true);
		}
		SprintAlpha = 0.0f;
	}
}

void UFPSTemplateAnimInstance::SetIsAiming(bool IsAiming)
{
	if ((IsAiming && !bCanAim) || PortPoseAlpha || SprintAlpha)
	{
		bIsAiming = false;
		bInterpAiming = true;
		return;
	}

	if (bIsAiming != IsAiming)
	{
		bIsAiming = IsAiming;
		bInterpAiming = true;
		bInterpCameraZoom = true;
	}
}

void UFPSTemplateAnimInstance::SetLeaning(ELeaning Lean)
{
	if (CurrentLean != Lean)
	{
		CurrentLean = Lean;
		bInterpLeaning = true;
	}
}

void UFPSTemplateAnimInstance::SetIsReloading(bool IsReloading, float BlendAlpha)
{
	if (IsReloading)
	{
		RotationAlpha = BlendAlpha;
		LeftHandIKAlpha = 0.0f;
	}
	else
	{
		RotationAlpha = 0.0f;
		LeftHandIKAlpha = 1.0f;
	}
}

void UFPSTemplateAnimInstance::SetCanAim(bool CanAim)
{
	bCanAim = CanAim;
}

void UFPSTemplateAnimInstance::ChangingFireMode(bool IsChanging)
{
	if (IsChanging)
	{
		RotationAlpha = 0.55f;
	}
	else
	{
		RotationAlpha = 0.0f;
	}
}

void UFPSTemplateAnimInstance::ChamberingRound(bool IsChambering)
{
	if (IsChambering)
	{
		RotationAlpha = 0.55f;
		LeftHandIKAlpha = 0.0f;
	}
	else
	{
		RotationAlpha = 0.55f;
		LeftHandIKAlpha = 1.0f;
	}
}

void UFPSTemplateAnimInstance::CycledSights()
{
	SetRelativeToHand();
	bInterpCameraZoom = true;
}

void UFPSTemplateAnimInstance::SetGripType(EFirearmGripType NewGripType)
{
	CurrentGripType = NewGripType;
}

void UFPSTemplateAnimInstance::StopMontages(float BlendOutTime)
{
	Montage_Stop(BlendOutTime);
}

void UFPSTemplateAnimInstance::SetCustomization(bool CustomizeFirearm)
{
	bCustomizingFirearm = CustomizeFirearm;
	if (bCustomizingFirearm)
	{
		LeftHandIKAlpha = 0.0f;
		AimingAlpha = 0.0f;
		PortPoseAlpha = 0.0f;
	}
	else
	{
		LeftHandIKAlpha = 1.0f;
	}
}

void UFPSTemplateAnimInstance::RecoilInterpToZero(float DeltaSeconds)
{
	FinalRecoilTransform = UKismetMathLibrary::TInterpTo(FinalRecoilTransform, FTransform(), DeltaSeconds, 8.0f); // def = 6
}

void UFPSTemplateAnimInstance::RecoilInterpTo(float DeltaSeconds)
{
	float Push = RecoilTransform.GetLocation().Y;
	FFloatSpringState SpringState;
	Push = UKismetMathLibrary::FloatSpringInterp(Push, FinalRecoilTransform.GetLocation().Y, SpringState,
		1.0f, 1.0f, DeltaSeconds, 1.0f);
	
	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FinalRecoilTransform, DeltaSeconds, 25.0f);// def = 15
	FVector Vec = RecoilTransform.GetLocation();
	Vec.Y = Push;
	RecoilTransform.SetLocation(Vec);
}

void UFPSTemplateAnimInstance::PerformRecoil(float Multiplier)
{
	if (Firearm)
	{
		if (AFPSTemplateProjectile* Projectile = Firearm->GetInUseProjectile().GetDefaultObject())
		{
			float TotalRecoil = 0.0f;
			Multiplier = FMath::Clamp(Multiplier, 0.01f, 4.0f);
			
			float RecoilVerticalMultiplier = Firearm->GetFirearmStats().VerticalRecoil * (1 / (Firearm->GetFirearmStats().Weight / 2.0f));
			RecoilVerticalMultiplier = UKismetMathLibrary::NormalizeToRange(RecoilVerticalMultiplier, 0.0f, 160.0f);
			RecoilVerticalMultiplier *= Multiplier;
			TotalRecoil += RecoilVerticalMultiplier;
			
			float RecoilHorizontalMultiplier = Firearm->GetFirearmStats().HorizontalRecoil * (1 / (Firearm->GetFirearmStats().Weight / 2.0f));
			RecoilHorizontalMultiplier = UKismetMathLibrary::NormalizeToRange(RecoilHorizontalMultiplier, 0.0f, 260.0f);
			RecoilHorizontalMultiplier *= Multiplier;
			TotalRecoil += RecoilHorizontalMultiplier;

			
			FVector RecoilLoc = FinalRecoilTransform.GetLocation();
			RecoilLoc += FVector(0.0f, FMath::RandRange(-3.0f, -2.0f) * TotalRecoil, FMath::RandRange(0.0f, 0.5f) * TotalRecoil);

			FRotator RecoilRot = FinalRecoilTransform.GetRotation().Rotator();
			// Pitch = Roll,		Yaw = Yaw,		Roll = Pitch
			RecoilRot += FRotator(FMath::RandRange(-0.0f, 0.0f),
				FMath::RandRange(-1.0f, 2.5f) * RecoilHorizontalMultiplier,
				FMath::RandRange(-5.0f, -2.0f) * RecoilVerticalMultiplier);
			RecoilRot.Roll = FMath::Clamp(RecoilRot.Roll, -15.0f, 0.0f);

			FinalRecoilTransform.SetLocation(RecoilLoc);
			FinalRecoilTransform.SetRotation(RecoilRot.Quaternion());
		}
	}
}
