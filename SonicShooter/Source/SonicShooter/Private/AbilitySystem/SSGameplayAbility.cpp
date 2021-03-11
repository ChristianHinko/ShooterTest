// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayAbility.h"

#include "SonicShooter/Private/Utilities/LogCategories.h"

#include "Character/AbilitySystemCharacter.h"


USSGameplayAbility::USSGameplayAbility()
{
	AbilityInputID = EAbilityInputID::Unset;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	bServerRespectsRemoteAbilityCancellation = false;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnlyTermination;
}


void USSGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	if (AbilityInputID == EAbilityInputID::Unset)
	{
		UE_LOG(LogGameplayAbility, Fatal, TEXT("%s()  Ability implementor forgot to set an AbilityInputID in the ability's constructor. Go back and set it so our grant ability calls know what input id to give it"), *FString(__FUNCTION__));
	}

	TryCallOnAvatarSetOnPrimaryInstance
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGrant && ActorInfo)
	{
		if (ActorInfo->AbilitySystemComponent.Get())
		{
			bool ActivatedAbilitySucessfully = ActorInfo->AbilitySystemComponent.Get()->TryActivateAbility(Spec.Handle);
		}
	}
}

bool USSGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void USSGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (NetExecutionPolicy == EGameplayAbilityNetExecutionPolicy::LocalPredicted)
	{
		// Const cast is a red flag. 
		FPredictionKey* Key = const_cast<FPredictionKey*>(&ActivationInfo.GetActivationPredictionKey());
		Key->NewRejectedDelegate().BindUObject(this, &USSGameplayAbility::OnActivationPredictionKeyRejected);

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

void USSGameplayAbility::ExternalEndAbility()
{
	check(CurrentActorInfo);

	const bool bReplicateEndAbility = true;
	const bool bWasCancelled = false;
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), bReplicateEndAbility, bWasCancelled);
}

//void USSGameplayAbility::OnCurrentAbilityPredictionKeyRejected()
//{
//	/*UKismetSystemLibrary::PrintString(this, "Prediction Key rejected ", true, false, FLinearColor::Red);
//
//	if (PKey == CurrentActivationInfo.GetActivationPredictionKey())
//	{
//		OnActivationPredictionKeyRejected();
//	}*/
//}

void USSGameplayAbility::OnActivationPredictionKeyRejected()
{

}
