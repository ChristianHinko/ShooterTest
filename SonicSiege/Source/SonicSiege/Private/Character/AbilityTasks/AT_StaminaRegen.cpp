// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AbilityTasks/AT_StaminaRegen.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Kismet/KismetSystemLibrary.h"


UAT_StaminaRegen::UAT_StaminaRegen()
{
	bTickingTask = true;
	
}

UAT_StaminaRegen* UAT_StaminaRegen::AT_StaminaRegen(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName)
{
	UAT_StaminaRegen* MyObj = NewAbilityTask<UAT_StaminaRegen>(OwningAbility, TaskInstanceName);


	return MyObj;
}

void UAT_StaminaRegen::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	/*if (AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s() called on invalid AbilitySystemComponent"), *FString(__FUNCTION__));
	}*/
}





void UAT_StaminaRegen::OnDestroy(bool AbilityEnded)
{
	// Clear ALL timers that belong to this (Actor) instance.
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	Super::OnDestroy(AbilityEnded);

}
