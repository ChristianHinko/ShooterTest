// Copyright 2021, Dakota Dawe, All rights reserved


#include "FPSTemplateStatics.h"

#include "FPSTemplate_PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"

void UFPSTemplateStatics::SpawnProjectileImpactEffects(const AActor* WorldActor, const FHitResult& HitResult, float DecalScaleMultiplier)
{
	if (UFPSTemplate_PhysicalMaterial* PhysMat = Cast<UFPSTemplate_PhysicalMaterial>(HitResult.PhysMaterial))
	{
		SpawnEffects(WorldActor, HitResult, PhysMat->ProjectileImpactEffects, DecalScaleMultiplier);
	}
}

void UFPSTemplateStatics::SpawnFootstepImpactEffects(const AActor* WorldActor, const FHitResult& HitResult,
	float DecalScaleMultiplier)
{
	if (UFPSTemplate_PhysicalMaterial* PhysMat = Cast<UFPSTemplate_PhysicalMaterial>(HitResult.PhysMaterial))
	{
		SpawnEffects(WorldActor, HitResult, PhysMat->FootstepImpactEffect, DecalScaleMultiplier);
	}
}

void UFPSTemplateStatics::SpawnEffects(const AActor* WorldActor, const FHitResult& HitResult,
                                       const FImpactEffects& ImpactEffects, float DecalScaleMultiplier)
{
	if (WorldActor)
	{
		if (UWorld* World = WorldActor->GetWorld())
		{
			if (UFPSTemplate_PhysicalMaterial* PhysMat = Cast<UFPSTemplate_PhysicalMaterial>(HitResult.PhysMaterial))
			{
				if (USoundBase* ImpactSound = ImpactEffects.ImpactSound)
				{
					UGameplayStatics::SpawnSoundAtLocation(World, ImpactSound, HitResult.Location);
				}
				
				if (UFXSystemAsset* ImpactEffect = ImpactEffects.ImpactEffect)
				{
					FRotator Rotation = FRotator::ZeroRotator;
					if (!ImpactEffects.bUseParticlesRotation)
					{
						Rotation = UKismetMathLibrary::MakeRotFromX(HitResult.Normal);
					}
					if (UNiagaraSystem* NEffect = Cast<UNiagaraSystem>(ImpactEffect))
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, NEffect, HitResult.Location, Rotation);
					}
					else if (UParticleSystem* PEffect = Cast<UParticleSystem>(ImpactEffect))
					{
						UGameplayStatics::SpawnEmitterAtLocation(World, PEffect, HitResult.Location, Rotation);
					}
				}
				
				if (UMaterialInstance* ImpactDecal = ImpactEffects.ImpactDecal)
				{
					if (USceneComponent* HitComponent = HitResult.GetComponent())
					{
						FRotator Rotation = UKismetMathLibrary::MakeRotFromX(HitResult.Normal);
						Rotation.Pitch += 180.0f;
						FVector DecalSize = ImpactEffects.DecalSize * DecalScaleMultiplier;
						float DecalLifetime = ImpactEffects.DecalLifeTime;
						
						UGameplayStatics::SpawnDecalAttached(ImpactDecal, DecalSize, HitComponent, NAME_None,
							HitResult.Location, Rotation, EAttachLocation::KeepWorldPosition, DecalLifetime);
					}
				}
			}
		}
	}
}

void UFPSTemplateStatics::SpawnEmptyCaseSound(const AActor* WorldActor, const FHitResult& HitResult)
{
	if (WorldActor)
	{
		if (UWorld* World = WorldActor->GetWorld())
		{
			if (UFPSTemplate_PhysicalMaterial* PhysMat = Cast<UFPSTemplate_PhysicalMaterial>(HitResult.PhysMaterial))
			{
				if (PhysMat->EmptyCaseImpactSound)
				{
					UGameplayStatics::SpawnSoundAtLocation(World, PhysMat->EmptyCaseImpactSound, HitResult.Location);
				}
			}
		}
	}
}

FRotator UFPSTemplateStatics::SetMuzzleMOA(FRotator MuzzleRotation, float MOA)
{
	MOA /= 100.0f;
	float MOAChange = (FMath::RandRange(-MOA / 2.0f, MOA / 2.0f) * 2.54f); // 1 inch at 100 yards
	MuzzleRotation.Yaw += MOAChange;
	MOAChange = (FMath::RandRange(-MOA / 2.0f, MOA / 2.0f) * 2.54f);
	MuzzleRotation.Pitch += MOAChange * 0.6f; // reduce vertical MOA shift for consistency

	return MuzzleRotation;
}

FRotator UFPSTemplateStatics::GetEstimatedMuzzleToScopeZero(const FTransform& MuzzleTransform,
	const FTransform& SightTransform, const float RangeMeters)
{
	FVector EndLocation = SightTransform.GetLocation() + SightTransform.GetRotation().Vector() * RangeMeters;
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleTransform.GetLocation(), EndLocation);
	LookAtRotation.Pitch += 0.04f; // Increase vertical projectile launch angle (thanks gravity)
	return LookAtRotation;
}

bool UFPSTemplateStatics::Ragdoll(UPrimitiveComponent* MeshComponent)
{
	if (Cast<USkeletalMeshComponent>(MeshComponent))
	{
		if (ACharacter* Character = Cast<ACharacter>(MeshComponent->GetOwner()))
		{
			Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComponent->SetSimulatePhysics(true);
		return true;
	}
	return false;
}

void UFPSTemplateStatics::RagdollWithImpact(UPrimitiveComponent* MeshComponent, FVector ImpactLocation, float ImpactForce)
{
	if (Ragdoll(MeshComponent) && ImpactLocation != FVector::ZeroVector && ImpactForce != 0.0f)
	{
		ImpactForce *= MeshComponent->GetMass();
		MeshComponent->AddRadialImpulse(ImpactLocation, 100.0f, ImpactForce, ERadialImpulseFalloff::RIF_Linear);
	}
}
