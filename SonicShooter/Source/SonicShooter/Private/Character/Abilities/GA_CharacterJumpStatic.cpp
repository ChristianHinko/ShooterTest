// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/GA_CharacterJumpStatic.h"

#include "Character/AbilitySystemCharacter.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"



UGA_CharacterJumpStatic::UGA_CharacterJumpStatic()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	bReplicateInputDirectly = true;		// bReplicateEndAbility in EndAbility() when replicating to the server doesn't always work because client's ability most likely isn't confirmed yet. So we do this bool instead to tell the server to run EndAbility(). (the better alternative to this bool is to use the input tasks but we can't because this is a non-instanced ability)
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.JumpStatic")));
}


bool UGA_CharacterJumpStatic::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const AAbilitySystemCharacter* Character = Cast<AAbilitySystemCharacter>(ActorInfo->AvatarActor.Get());
	return Character && Character->CanJump();
}

void UGA_CharacterJumpStatic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	if (!Character)
	{
		UE_LOG(LogGameplayAbility, Warning, TEXT("%s() Character was NULL when trying to activate static jump ability. Called EndAbility()"), *FString(__FUNCTION__));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	///////////////////////////////////// we are safe to proceed /////////


	Character->Jump();
}

void UGA_CharacterJumpStatic::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	}
}

// Epic's comment
/**
 *	Canceling a non instanced ability is tricky. Right now this works for Jump since there is nothing that can go wrong by calling
 *	StopJumping() if you aren't already jumping. If we had a montage playing non instanced ability, it would need to make sure the
 *	Montage that *it* played was still playing, and if so, to cancel it. If this is something we need to support, we may need some
 *	light weight data structure to represent 'non intanced abilities in action' with a way to cancel/end them.

 Translation:
	Anything outside of ActivateAbility() for Non-Instanced abilities will NOT have a valid prediction key, meaning you only get roll back inside ActivateAbility().
	This is because you can't bind to tasks during the execution of the ability, which means no WaitNetSyncs or InputEvent tasks that give a new prediction key for the callbacks.
	This leaves us a problem now since we don't have roll back capability outside ActivateAbility() but theres still a chance you can use Non-Instanced.
	If not having rollback on operations outside ActivateAbility() makes no difference, then go right ahead. This is why we can have jumping as Non-Instanced. Because in the event
	that the ability does get rolled back (only operations inside AcctivateAbility), calling Character->StopJumping() doen't mess anything up since your already not jumping.

	The montage thing they were talking about, I don't completely know what they are talking about since it's kind of vague. But seams like they mean if you were going to play
	a montage that has callbacks (meaning it's an async task) then make sure your ok with always stopping the montage every time when the ability ends, because I guess rolling
	back the montage won't work? And also weird that they are talking about doing an async task inside a Non-Instanced ability. Maybe it's not async. Idk
 */
void UGA_CharacterJumpStatic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (!IsEndAbilityValid(Handle, ActorInfo))
	{
		return;
	}
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterJumpStatic::EndAbility, Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled));
		return;
	}

	if (ActorInfo)
	{
		if (ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get()))
		{
			Character->StopJumping();
		}
		else
		{
			UE_LOG(LogGameplayAbility, Error, TEXT("%s() Couldn't call Character->StopJumping() because Character* was NULL"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove when trying to call StopJumping on the character"), *FString(__FUNCTION__));
	}


	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
