// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Equipment/Equipment.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Interactable.h"
#include "Character/AbilitySystemCharacter.h"

AEquipment::AEquipment()
{
	bWithoutAbilitySystemComponentSubobject = true;

	bShouldFireDetectionEvents = true;
	
	bIsAutomaticInstantInteract = false;
	bIsAutomaticDurationInteract = false;
	bIsManualInstantInteract = false;
	bIsManualDurationInteract = true;
}
void AEquipment::PostInitializeComponents()
{
	if (Super::StaticClass() == AAbilitySystemActor::StaticClass())
	{
		AAbilitySystemActor::Super::PostInitializeComponents();	// skip AAbilitySystemActor's call on SetupWithAbilitySystem()
	}
	else
	{
		Super::PostInitializeComponents();
	}


}




bool AEquipment::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

TSubclassOf<UGameplayEffect> AEquipment::GetInteractableEffectTSub()
{
	return nullptr;
}








void AEquipment::OnInstantInteract(AShooterCharacter* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Instant Interact", true, false, FLinearColor::Yellow);
	Destroy();
}



void AEquipment::OnDurationInteractBegin(AShooterCharacter* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnDurationInteractBegin", true, false, FLinearColor::Gray);
}
void AEquipment::InteractingTick(AShooterCharacter* InteractingPawn, float DeltaTime, float CurrentInteractionTime)
{
	ENetRole role = GetLocalRole();
	UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + FString::SanitizeFloat(CurrentInteractionTime), true, false, FLinearColor::Gray);
}

void AEquipment::OnDurationInteractEnd(AShooterCharacter* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
	ENetRole role = GetLocalRole();
	if (DurationInteractEndReason == EDurationInteractEndReason::REASON_SuccessfulInteract)
	{
		//bCanCurrentlyBeInteractedWith = false;
		Destroy();	// Destroying on complete causes that weird problem where (im guessing the next interactable in the stack) doesn't stop ticking if you leave. And completes.
		//UKismetSystemLibrary::PrintString(this, "OnDurationInteractEnd", true, false, FLinearColor::Gray);
	}
	
}







void AEquipment::OnInitialDetect(AShooterCharacter* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "Become CurrentInteract", true, false, FLinearColor::Green, 20);
}
void AEquipment::OnConsecutiveDetect(AShooterCharacter* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "Tick", true, false, FLinearColor::Blue);
}
void AEquipment::OnEndDetect(AShooterCharacter* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "End being CurrentInteract", true, false, FLinearColor::Red, 20);
}
