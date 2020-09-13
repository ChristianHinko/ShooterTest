// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Interactable.h"
#include "Character/AbilitySystemCharacter.h"

AItem::AItem()
{
	bShouldFireSweepEvents = true;
	
	bIsAutomaticInstantInteract = false;
	bIsAutomaticDurationInteract = true;
	bIsManualInstantInteract = false;
	bIsManualDurationInteract = false;
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
	UKismetSystemLibrary::PrintString(this, "Instant Interact", true, true, FLinearColor::Yellow);
	Destroy();
}



void AItem::OnDurationInteractBegin(APawn* InteractingPawn)
{
	//bCanCurrentlyBeInteractedWith = false;
	//UKismetSystemLibrary::PrintString(this, "OnDurationInteractBegin", true, true, FLinearColor::Gray);
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
		//UKismetSystemLibrary::PrintString(this, "OnDurationInteractEnd", true, true, FLinearColor::Gray);
	}
	
}







void AItem::OnInteractSweepInitialHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Start", true, true, FLinearColor::Green);
}
void AItem::OnInteractSweepConsecutiveHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Tick", true, true, FLinearColor::Blue);
}
void AItem::OnInteractSweepEndHitting(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "End", true, true, FLinearColor::Red);
}
