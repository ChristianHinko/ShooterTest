// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Item.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Interactable.h"
#include "Character/AbilitySystemCharacter.h"

AItem::AItem()
{
	bWithoutAbilitySystemComponentSubobject = true;

	bShouldFireSweepEvents = true;
	InteractionMode = EInteractionMode::Duration;
}
void AItem::PostInitializeComponents()
{
	AAbilitySystemActor::Super::PostInitializeComponents();		// skip AAbilitySystemActor's call on SetupWithAbilitySystem()


}




bool AItem::CanActivateInteractAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}








void AItem::OnInstantInteract(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "Instant Interact", true, false, FLinearColor::Yellow);
}



void AItem::OnDurationInteractBegin(APawn* InteractingPawn)
{
	UKismetSystemLibrary::PrintString(this, "OnDurationInteractBegin", true, false, FLinearColor::Gray);
}
void AItem::InteractingTick(APawn* InteractingPawn, float DeltaTime, float CurrentInteractionTime)
{
	UKismetSystemLibrary::PrintString(this, "Interacting a " + FString::SanitizeFloat(interactDuration) + "duration interactable.....\nCurrentTime=" + FString::SanitizeFloat(CurrentInteractionTime), true, false, FLinearColor::Gray);
}
void AItem::OnDurationInteractEnd(APawn* InteractingPawn, EDurationInteractEndReason DurationInteractEndReason, float InteractionTime)
{
	if (DurationInteractEndReason == EDurationInteractEndReason::REASON_SuccessfulInteract)
	{
		Destroy();
		UKismetSystemLibrary::PrintString(this, "OnDurationInteractEnd", true, false, FLinearColor::Gray);
	}
	
}







void AItem::OnInteractSweepInitialHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Start", true, false, FLinearColor::Green);
}
void AItem::OnInteractSweepConsecutiveHit(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "Tick", true, false, FLinearColor::Blue);
}
void AItem::OnInteractSweepEndHitting(APawn* InteractingPawn)
{
	//UKismetSystemLibrary::PrintString(this, "End", true, false, FLinearColor::Red);
}
