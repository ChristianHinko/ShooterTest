// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SystemAbilities/GA_StartupEffects.h"

#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character\AbilitySystemCharacter.h"
#include "Pawn\AbilitySystemPawn.h"

#include "Kismet/KismetSystemLibrary.h"

UGA_StartupEffects::UGA_StartupEffects()
{
	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.StartupEffects")));
}

void UGA_StartupEffects::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!AvatarActor)
	{
		return;
	}
	
	GASCharacter = Cast<AAbilitySystemCharacter>(AvatarActor);
	if (!GASCharacter)
	{
		GASPawn = Cast<AAbilitySystemPawn>(AvatarActor);
		if (!GASPawn)
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() failed to cast avatar actor to AAbilitySystemCharacter or AAbilitySystemPawn."), *FString(__FUNCTION__));
			return;
		}
	}
}


bool UGA_StartupEffects::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (!GASCharacter && !GASPawn)
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() No Character or pawn was found when trying to apply startup effects for the player's new possession. Returned false"), *FString(__FUNCTION__));
		return false;
	}

	return true;
}

void UGA_StartupEffects::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
		return;
	}

	for (TSubclassOf<UGameplayEffect> EffectTSub : GASCharacter->EffectsToApplyOnStartup)
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(EffectTSub, GetAbilityLevel());

		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, EffectSpecHandle);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}




void UGA_StartupEffects::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_StartupEffects::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}




	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
