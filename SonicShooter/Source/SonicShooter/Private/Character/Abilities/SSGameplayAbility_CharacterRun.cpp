// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Abilities\SSGameplayAbility_CharacterRun.h"

#include "Character/SSCharacter.h"
#include "Character/SSCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



USSGameplayAbility_CharacterRun::USSGameplayAbility_CharacterRun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityInputID = ESSAbilityInputID::Run;
	AbilityTags.AddTag(SSNativeGameplayTags::Ability_Movement_Run);


	ActivationBlockedTags.AddTag(SSNativeGameplayTags::Character_RunDisabled);	// This isn't the singular thing stopping you from running. The CMC is what listens for the presence of the RunDisabledTag and blocks running. This check just saves an ability activation.

	CancelAbilitiesWithTag.AddTag(SSNativeGameplayTags::Ability_Movement_Crouch);
}


void USSGameplayAbility_CharacterRun::ASSOnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::ASSOnAvatarSet(ActorInfo, Spec);

	// Good place to cache references so we don't have to cast every time
	if (!ActorInfo)
	{
		return;
	}

	SSCharacter = Cast<ASSCharacter>(ActorInfo->AvatarActor);
	if (SSCharacter.IsValid())
	{
		CMC = SSCharacter->GetSSCharacterMovementComponent();
	}
}

bool USSGameplayAbility_CharacterRun::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!SSCharacter.IsValid())
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() SSCharacter was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}
	if (!CMC.IsValid())
	{
		UE_LOG(LogSSGameplayAbility, Error, TEXT("%s() CharacterMovementComponent was NULL when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	if (CMC->CanRunInCurrentState() == false)
	{
		UE_LOG(LogSSGameplayAbility, Warning, TEXT("%s() Was not able to run in current state when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
		return false;
	}

	return true;
}

void USSGameplayAbility_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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



void USSGameplayAbility_CharacterRun::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CMC->UnRun();
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(RunningEffectActiveHandle);

	Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
