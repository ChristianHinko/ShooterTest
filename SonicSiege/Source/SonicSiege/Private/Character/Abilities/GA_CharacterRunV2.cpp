// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterRunV2.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Kismet/KismetSystemLibrary.h"

UGA_CharacterRunV2::UGA_CharacterRunV2()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.RunV2")));

	ActivationBlockedTags.AddTagFast(TagOutOfStamina);
}

void UGA_CharacterRunV2::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	//	Good place to cache references so we don't have to cast every time.
	if (!ActorInfo)
	{
		return;
	}

	CMC = Cast<USSCharacterMovementComponent>(ActorInfo->MovementComponent);
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL"), *FString(__FUNCTION__));
	}
	GASCharacter = Cast<AAbilitySystemCharacter>(ActorInfo->AvatarActor);
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL"), *FString(__FUNCTION__));
	}
	CharacterAttributeSet = GASCharacter->GetCharacterAttributeSet();
	if (!CharacterAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterAttributeSet was NULL"), *FString(__FUNCTION__));
	}
	
	
}

bool UGA_CharacterRunV2::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	//	Returning false in here for checks is better than doing checks in ActivateAbility() since returning false triggers a rollback on the client if Server returns false. In our previous method we called CancelAbility() inside ActivateAbility() if a check didn't pass, which doesn't even cancel it on the remote machine if client since bRespectsRemoteAbilityToCancel most of the time will be false.
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!DrainStaminaFromRunEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Effect TSubclassOf NULL so returned false - please fill out Character Run ability blueprint"), *FString(__FUNCTION__));
		return false;
	}
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!GASCharacter)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() GASCharacter was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (!CharacterAttributeSet)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() CharacterAttributeSet was NULL. Returned false"), *FString(__FUNCTION__));
		return false;
	}
	if (GASCharacter->GetCharacterAttributeSet()->GetStamina() <= 0)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() Stamina was <= 0 so can't run. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_CharacterRunV2::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}




	// Lets do the logic we want to happen when the ability starts.
	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterRunV2::OnRelease);
	InputReleasedTask->ReadyForActivation();

	//	Set to running speed
	CMC->SetWantsToRun(true);
}

void UGA_CharacterRunV2::OnRelease(float TimeHeld)
{
	//	Set back to normal speed
	CMC->SetWantsToRun(false);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);	// no need to replicate, server runs this too
}
























void UGA_CharacterRunV2::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterRunV2::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	// Lets do the logic we want to happen when the ability ends. If you want you can do an async task,
	// but just make sure you don't call Super::EndAbility until after the task ends (call Super::EndAbility in the task's callback)









	//Now call the Super to finish ending the ability.
	/*
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
















void UGA_CharacterRunV2::BeginDestroy()
{
	Super::BeginDestroy();



}
