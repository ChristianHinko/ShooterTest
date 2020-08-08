// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterRun.h"

#include "Character/AbilitySystemCharacter.h"
#include "Character/SSCharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Character\AS_Character.h"
#include "Kismet/KismetSystemLibrary.h"

UGA_CharacterRun::UGA_CharacterRun()
{
	TagOutOfStamina = FGameplayTag::RequestGameplayTag(FName("State.Character.OutOfStamina"));
	TagRunning = FGameplayTag::RequestGameplayTag(FName("State.Character.Running"));
	
	
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Run")));
	
	ActivationBlockedTags.AddTagFast(TagOutOfStamina);

	ActivationOwnedTags.AddTagFast(TagRunning);

	

}


bool UGA_CharacterRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UGA_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	if (!StaminaDrainEffectTSub)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("Effect TSubclassOf empty in %s so this ability was canceled - please fill out Character Run ability blueprint"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	USSCharacterMovementComponent* CMC = Cast<USSCharacterMovementComponent>(ActorInfo->MovementComponent);
	if (!CMC)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() CharacterMovementComponent was NULL when trying to run. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}
	UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
	if (!InputReleasedTask)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate run ability. Called CancelAbility()"), *FString(__FUNCTION__));
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		return;
	}

	if (GASCharacter == nullptr)
	{
		GASCharacter = Cast<AAbilitySystemCharacter>(GetAvatarActorFromActorInfo());
	}

	// Lets do the logic we want to happen when the ability starts.
	//	Make sure we apply effect in valid prediction key window so we make sure the tag also gets applied on the client too
	//StaminaDrainActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, StaminaDrainEffectTSub.GetDefaultObject(), GetAbilityLevel());
	CMC->SetWantsToRun(true);

	InputReleasedTask->OnRelease.AddDynamic(this, &UGA_CharacterRun::OnRelease);
	InputReleasedTask->ReadyForActivation();




	FTimerDelegate TickTimerDel;

	//Binding the function with specific variables
	TickTimerDel.BindUFunction(this, TEXT("OnTimerTick"));

	GetWorld()->GetTimerManager().SetTimer(TickTimerHandle, TickTimerDel, 1.f, true, 0.f);
}

//	Somehow we have a valid prediction key here. I guess we don't need a WaitNetSync
void UGA_CharacterRun::OnTimerTick()
{
	if (GASCharacter)
	{
		if (GASCharacter->GetCharacterAttributeSet())
		{
			//	Check if we can't sprint anymore
			if (GASCharacter->GetCharacterAttributeSet()->GetStamina() <= 0)
			{
				

				EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);	// no need to replicate, server runs this too
				return;
			}
		}
	}


	
	ApplyGameplayEffectToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), StaminaDrainEffectTSub.GetDefaultObject(), GetAbilityLevel());
}

void UGA_CharacterRun::OnRelease(float TimeHeld)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);	// no need to replicate, server runs this too
}
























void UGA_CharacterRun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Super wraps the whole EndAbility() in IsEndAbilityValid()
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	// Make sure we bind our child class' version of EndAbility() instead of using the Super's version of this part
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterRun::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}



	// Lets do the logic we want to happen when the ability ends. If you want you can do an async task,
	// but just make sure you don't call Super::EndAbility until after the task ends (call Super::EndAbility in the task's callback)
	if (ActorInfo)
	{
		USSCharacterMovementComponent* CMC = CastChecked<USSCharacterMovementComponent>(ActorInfo->MovementComponent);
		if (CMC && ActorInfo->AbilitySystemComponent.Get())
		{
			//	We want to group all ending actions for this ability together instead of them having them inside their own NULL checks. We want all our logic running or none of it running
			CMC->SetWantsToRun(false);
			ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(StaminaDrainActiveHandle);
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Either CMC or ActorInfo->AbilitySystemComponent.Get() was NULL when trying to remove StaminaDrainActiveHandle and when trying to run CMC->SetWantsToRun(false);"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove StaminaDrainActiveHandle and when trying to run CMC->SetWantsToRun(false);"), *FString(__FUNCTION__));
	}



	
	//Now call the Super to finish ending the ability.
	/* 
		IMPORTANT: If part of your gameplay logic in EndAbility() uses an async task, make sure you wait until the task is completed before you call Super::EndAbility.
		Otherwise the task may not complete. Call Super::EndAbility inside the task's OnComplete delegate.
	*/
	// super end ability loops through all tasks and calls OnDestroy; however, this is a virtual function, some tasks may not be destroyed on end ability (this is probably a super rare case tho) (dan says WaitTargetData doesn't end)
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
















void UGA_CharacterRun::BeginDestroy()
{
	Super::BeginDestroy();

	// Alternatively you can clear ALL timers that belong to this (Actor) instance.
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
}


