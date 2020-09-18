// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Interactable.h"
#include "Character/AbilitySystemCharacter.h"

AItem::AItem()
{
	bWithoutAbilitySystemComponentSubobject = true;

	bShouldFireDetectionEvents = true;
	
	bIsAutomaticInstantInteract = false;
	bIsAutomaticDurationInteract = false;
	bIsManualInstantInteract = false;
	bIsManualDurationInteract = true;
}
void AItem::PostInitializeComponents()
{
	AAbilitySystemActor::Super::PostInitializeComponents();		// skip AAbilitySystemActor's call on SetupWithAbilitySystem()


}




bool AItem::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

TSubclassOf<UGameplayEffect> AItem::GetInteractableEffectTSub()
{
	return nullptr;
}








void AItem::OnInstantInteract(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Instant Interact", true, false, FLinearColor::Yellow);
	Destroy();
}



void AItem::OnDurationInteractBegin(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnDurationInteractBegin", true, false, FLinearColor::Gray);
}
void AItem::InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime)
{
	ENetRole role = GetLocalRole();
	UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + FString::SanitizeFloat(CurrentInteractionTime), true, false, FLinearColor::Gray);
}

void AItem::OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
	ENetRole role = GetLocalRole();
	if (DurationInteractEndReason == EDurationInteractEndReason::REASON_SuccessfulInteract)
	{
		//bCanCurrentlyBeInteractedWith = false;
		Destroy();	// Destroying on complete causes that weird problem where (im guessing the next interactable in the stack) doesn't stop ticking if you leave. And completes.
		//UKismetSystemLibrary::PrintString(this, "OnDurationInteractEnd", true, false, FLinearColor::Gray);
	}
	
}







void AItem::OnInitialDetect(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "Become CurrentInteract", true, false, FLinearColor::Green, 20);
}
void AItem::OnConsecutiveDetect(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "Tick", true, false, FLinearColor::Blue);
}
void AItem::OnEndDetect(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, GetActorLabel() + " ---->" + "End being CurrentInteract", true, false, FLinearColor::Red, 20);
}
