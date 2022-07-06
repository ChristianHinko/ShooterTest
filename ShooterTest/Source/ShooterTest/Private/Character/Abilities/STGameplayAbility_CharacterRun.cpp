// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\STGameplayAbility_CharacterRun.h"

#include "Character/STCharacter.h"
#include "Character/STCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



USTGameplayAbility_CharacterRun::USTGameplayAbility_CharacterRun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = static_cast<uint8>(ESTAbilityInputID::Run);
	AbilityTags.AddTag(STNativeGameplayTags::Ability_Movement_Run);


	ActivationBlockedTags.AddTag(STNativeGameplayTags::Character_RunDisabled);	// This isn't the singular thing stopping you from running. The CMC is what listens for the presence of the RunDisabledTag and blocks running. This check just saves an ability activation.

	CancelAbilitiesWithTag.AddTag(STNativeGameplayTags::Ability_Movement_Crouch);
}


void USTGameplayAbility_CharacterRun::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	STCharacter = Cast<ASTCharacter>(ActorInfo->AvatarActor);
	if (STCharacter.IsValid())
	{
		CMC = STCharacter->GetSTCharacterMovementComponent();
	}
}

bool USTGameplayAbility_CharacterRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!STCharacter.IsValid())
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() STCharacter was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (!CMC.IsValid())
	{
		UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (CMC->CanRunInCurrentState() == false)
	{
		UE_LOG(LogSTGameplayAbility, Warning, TEXT("%s() Was not able to run in current state when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void USTGameplayAbility_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	/////////////////////////////////////////////    we've passed the checks //////


	RunningEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, RunningEffectTSub.GetDefaultObject(), GetAbilityLevel());

	CMC->Run();
}



void USTGameplayAbility_CharacterRun::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CMC->UnRun();
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(RunningEffectActiveHandle);

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
