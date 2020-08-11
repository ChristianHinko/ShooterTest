// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayAbility.h"

#include "SonicSiege/Private/Utilities/LogCategories.h"

#include "Character/AbilitySystemCharacter.h"


USSGameplayAbility::USSGameplayAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bServerRespectsRemoteAbilityCancellation = false;
}


void USSGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGrant && ActorInfo)
	{
		if (ActorInfo->AbilitySystemComponent.Get())
		{
			bool ActivatedAbilitySucessfully = ActorInfo->AbilitySystemComponent.Get()->TryActivateAbility(Spec.Handle);

		}
	}
}

void USSGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalPredicted)
	{
		if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))	// If we are a client without a valid prediction key
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Ability activated but the client has no valid prediction key"), *FString(__FUNCTION__));
		}
	}
	


#pragma region Copied from Super (Blueprint Support)
	if (bHasBlueprintActivate)
	{
		// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
		K2_ActivateAbility();
		return;
	}
	else if (bHasBlueprintActivateFromEvent)
	{
		if (TriggerEventData)
		{
			// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
			K2_ActivateAbilityFromEvent(*TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
		return;
	}
#pragma endregion
}
