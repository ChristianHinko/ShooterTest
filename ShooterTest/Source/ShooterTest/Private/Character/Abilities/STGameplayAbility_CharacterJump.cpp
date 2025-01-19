// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Abilities/STGameplayAbility_CharacterJump.h"

#include "Character/STCharacter.h"
#include "Character/STCharacterMovementComponent.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "ASSNativeGameplayTags.h"
#include "AbilitySystemComponent.h"

USTGameplayAbility_CharacterJump::USTGameplayAbility_CharacterJump(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AbilityTags.AddTag(STNativeGameplayTags::Ability_Movement_Jump);
    AbilityTags.AddTag(ASSNativeGameplayTags::Ability_Type_DisableAutoActivationFromInput);
    AbilityTags.AddTag(STNativeGameplayTags::InputAction_Jump);


    CancelAbilitiesWithTag.AddTag(STNativeGameplayTags::Ability_Movement_Crouch);
    CancelAbilitiesWithTag.AddTag(STNativeGameplayTags::Ability_Movement_Run);
}

void USTGameplayAbility_CharacterJump::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);

    // Good place to cache references so we don't have to cast every time
}

bool USTGameplayAbility_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
    {
        return false;
    }

    ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!IsValid(Character))
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Character was NULL. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }

    if (Character->CanJump() == false)
    {
        UE_LOG(LogSTGameplayAbility, Verbose, TEXT("%s() Was not able to jump when trying to activate ability. Returned false"), ANSI_TO_TCHAR(__FUNCTION__));
        return false;
    }

    return true;
}

void USTGameplayAbility_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    UCharacterMovementComponent* CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
    if (!IsValid(CMC))
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to activate ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    ///////////////////////// we've passed the checks ///////////


    //    Make sure we apply effect in valid prediction key window so we make sure the tag also gets applied on the client too
    if (JumpEffectTSub)
    {
        JumpEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, JumpEffectTSub.GetDefaultObject(), GetAbilityLevel());
    }
    else
    {
        UE_LOG(LogSTGameplayAbility, Warning, TEXT("JumpEffectTSub empty in %s - please fill out Character Jump ability blueprint"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    CMC->DoJump(false);
}

void USTGameplayAbility_CharacterJump::ASSEndAbility(
    const FGameplayAbilitySpecHandle& inSpecHandle,
    const FGameplayAbilityActorInfo& inActorInfo,
    const FGameplayAbilityActivationInfo& inActivationInfo,
    const bool inShouldReplicateEndAbility,
    const bool inWasCanceled)
{
    const FSTGameplayAbilityActorInfo& STActorInfo = static_cast<const FSTGameplayAbilityActorInfo&>(inActorInfo);

    if (USTCharacterMovementComponent* CMC = STActorInfo.STCharacterMovementComponent.Get())
    {
        CMC->UnJump();
    }
    else
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() CMC was NULL when trying to UnJump"), ANSI_TO_TCHAR(__FUNCTION__));
    }

    inActorInfo.AbilitySystemComponent->RemoveActiveGameplayEffect(JumpEffectActiveHandle);


    Super::ASSEndAbility(inSpecHandle, inActorInfo, inActivationInfo, inShouldReplicateEndAbility, inWasCanceled);
}
