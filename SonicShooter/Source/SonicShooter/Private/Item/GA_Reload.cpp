// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/GA_Reload.h"

#include "SonicShooter/Private/Utilities/LogCategories.h"

#include "Kismet/KismetSystemLibrary.h"



UGA_Reload::UGA_Reload()
{
	//AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Reload")));
}

void UGA_Reload::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (!ActorInfo)
	{
		return;
	}
	//AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	if (!ActorInfo->AvatarActor.Get()/*AvatarActor*/)
	{
		return;
	}





}

bool UGA_Reload::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}





	return true;
}

void UGA_Reload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}


	//MyEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, MyEffectTSub.GetDefaultObject(), GetAbilityLevel());


	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}




void UGA_Reload::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}

	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_Reload::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}




	//ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(MyEffectActiveHandle);




	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
