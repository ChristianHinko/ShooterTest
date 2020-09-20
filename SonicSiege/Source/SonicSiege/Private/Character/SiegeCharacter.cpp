// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SiegeCharacter.h"

#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Interfaces/Interactable.h"
#include "Utilities/CollisionChannels.h"
#include "Camera/CameraComponent.h"


ASiegeCharacter::ASiegeCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractSweepDistance = 150.f;
	CurrentPrioritizedInteractable = nullptr;
	LastPrioritizedInteractable = nullptr;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASiegeCharacter::OnComponentBeginOverlapCharacterCapsule);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASiegeCharacter::OnComponentEndOverlapCharacterCapsule);
}


void ASiegeCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	//float frameHorizontalMouseRate = 0;
	//float frameVerticalMouseRate = 0;
	//Cast<APlayerController>(GetController())-> GetInputMouseDelta(frameHorizontalMouseRate, frameVerticalMouseRate);
	//

	//// Weapon sway
	//if (POVMesh/* && AbilitySystem && !AbilitySystem->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("WeaponState.ADS")))*/)
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector FrameMouseRate = FVector(0, -frameHorizontalMouseRate, -frameVerticalMouseRate);
	//	FVector NewCameraLocation = CameraSocketLocation - (FrameMouseRate * CameraSwayAmount);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaTime, 10));
	//	}

	//	
	//}
	//else
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector NewCameraLocation = FVector(0, 0, 0);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		float yaw = CurrentCameraLocation.Y - frameHorizontalMouseRate;
	//		float pitch = CurrentCameraLocation.Z - frameVerticalMouseRate;
	//		FVector Sway = FVector(CurrentCameraLocation.X, yaw, pitch);

	//		FVector ADSCameraSwayAmount = CameraSwayAmount + AddedCameraSwayDuringADS;

	//		NewCameraLocation = CameraSocketLocation - (Sway * ADSCameraSwayAmount);




	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaTime, 10));
	//	}




	//}

	if (HasAuthority() || IsLocallyControlled())	// Don't run for simulated proxies
	{
		CurrentPrioritizedInteractable = ScanForCurrentPrioritizedInteractable(InteractSweepHitResult);
		if (CurrentPrioritizedInteractable)
		{
			if (CurrentPrioritizedInteractable != LastPrioritizedInteractable)
			{

				if (CurrentPrioritizedInteractable->bShouldFireDetectionEvents)
					CurrentPrioritizedInteractable->OnInitialDetect(this);

				if (LastPrioritizedInteractable)
				{
					if (LastPrioritizedInteractable->bShouldFireDetectionEvents)
						LastPrioritizedInteractable->OnEndDetect(this);
				}

				// Automatic interact activation might be nice here
			}
			else
			{
				if (CurrentPrioritizedInteractable->bShouldFireDetectionEvents)
					CurrentPrioritizedInteractable->OnConsecutiveDetect(this);
			}





			LastPrioritizedInteractable = CurrentPrioritizedInteractable;
		}
		else
		{
			if (LastPrioritizedInteractable != nullptr)	// If the last frame had something to interact with
			{
				if (LastPrioritizedInteractable->bShouldFireDetectionEvents)
					LastPrioritizedInteractable->OnEndDetect(this);
				LastPrioritizedInteractable = nullptr;
			}
		}
	}
}

IInteractable* ASiegeCharacter::ScanForCurrentPrioritizedInteractable(FHitResult& OutHit)
{
	// Check if sphere sweep detects blocking hit as an interactable (a blocking hit doesn't necessarily mean the object is collidable. It's can just be collidable to the Interact trace channel).
	if (GetWorld() && GetFollowCamera())
	{
		FVector StartLocation = GetFollowCamera()->GetComponentLocation();
		FVector EndLocation = StartLocation + (GetFollowCamera()->GetForwardVector() * InteractSweepDistance);

		const bool bBlockingHit = GetWorld()->SweepSingleByChannel(OutHit, StartLocation, EndLocation, FQuat::Identity, COLLISION_INTERACT, FCollisionShape::MakeSphere(InteractSweepRadius), FCollisionQueryParams());
		if (bBlockingHit)
		{
			if (IInteractable* BlockingHitInteractable = Cast<IInteractable>(OutHit.GetActor()))
			{
				if (BlockingHitInteractable->GetCanCurrentlyBeInteractedWith())
				{
					BlockingHitInteractable->InjectDetectType(EDetectType::DETECTTYPE_Sweeped);
					return BlockingHitInteractable;
				}
			}
		}
	}


	// Try to return an interactable that is overlapping with the capsule component. It chooses the most recent one you overlap with (top of the stack). 
	if (CurrentOverlapInteractablesStack.Num() > 0)
	{
		for (int32 i = CurrentOverlapInteractablesStack.Num() - 1; i >= 0; i--)
		{
			if (CurrentOverlapInteractablesStack.IsValidIndex(i))
			{
				if (CurrentOverlapInteractablesStack[i])
				{
					if (CurrentOverlapInteractablesStack[i]->GetCanCurrentlyBeInteractedWith())
					{
						//UKismetSystemLibrary::PrintString(this, "Using = " + FString::SanitizeFloat(i), true, false, FLinearColor::Green);
						return CurrentOverlapInteractablesStack[i];
					}
				}
				else
				{
					CurrentOverlapInteractablesStack.RemoveAt(i);	// (edge case) just remove the useless element
				}
			}
		}
	}





	// If no blocking or overlap interactables found return NULL
	return nullptr;
}

void ASiegeCharacter::OnComponentBeginOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		// If we knew at this point weather this interactable is the current one, we would be able to fire off a more helpful event in the interface.
		Interactable->InjectDetectType(EDetectType::DETECTTYPE_Overlapped);
		CurrentOverlapInteractablesStack.Push(Interactable);
	}
}
void ASiegeCharacter::OnComponentEndOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* Interactable = Cast<IInteractable>(OtherActor))
	{
		if (CurrentOverlapInteractablesStack.Num() > 0)
		{
			CurrentOverlapInteractablesStack.RemoveSingle(Interactable);	// Not using pop because there is a chance a character might be interacting with an overlap that isn't the current detected one (meaning it's not at the top of the stack)
			OnElementRemovedFromFrameOverlapInteractablesStack.Broadcast(Interactable);
			Interactable->InjectDetectType(EDetectType::DETECTTYPE_NotDetected);		// Give a value of not detected just in case (maybe implementor is trying something weird where they change how it's detected at runtime)
		}
	}
}



void ASiegeCharacter::OnInteractPressed()
{
	if (CurrentPrioritizedInteractable)
	{
		if (CurrentPrioritizedInteractable->GetIsManualInstantInteract())
		{
			GetAbilitySystemComponent()->TryActivateAbility(InteractInstantAbilitySpecHandle);
		}
		if (CurrentPrioritizedInteractable->GetIsManualDurationInteract())
		{
			GetAbilitySystemComponent()->TryActivateAbility(InteractDurationAbilitySpecHandle);
		}

	}
}

void ASiegeCharacter::OnPrimaryFirePressed()
{
	//if (GetAbilitySystemComponent())
	//{
	//	GetAbilitySystemComponent()->TryActivateAbility(CurrentWeapon->FireAbilitySpecHandle);		for when we add inventory system
	//}
}
