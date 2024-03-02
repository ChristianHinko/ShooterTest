// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/STGameplayAbility_ADS.h"

#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"



USTGameplayAbility_ADS::USTGameplayAbility_ADS(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AbilityTags.AddTag(STNativeGameplayTags::InputAction_SecondaryFire);
    AbilityTags.AddTag(STNativeGameplayTags::Ability_ADS);
}


bool USTGameplayAbility_ADS::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
    {
        return false;
    }




    return true;
}

void USTGameplayAbility_ADS::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


    ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
    if (!Character)
    {
        UE_LOG(LogSTGameplayAbility, Warning, TEXT("%s() Character was NULL when trying to activate ADS ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    UAbilityTask_WaitInputRelease* InputReleasedTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this);
    if (!InputReleasedTask)
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() InputReleasedTask was NULL when trying to activate ADS ability. Called EndAbility()"), ANSI_TO_TCHAR(__FUNCTION__));
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }
    ///////////////////////////////////// we are safe to proceed /////////

    if (ADSEffectTSub)
    {
        ADSEffectActiveHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, ADSEffectTSub.GetDefaultObject(), GetAbilityLevel());
    }
    else
    {
        UE_LOG(LogSTGameplayAbility, Warning, TEXT("ADSEffectTSub TSubclassOf empty in %s"), ANSI_TO_TCHAR(__FUNCTION__));
    }


    //Character->ADS();

    InputReleasedTask->OnRelease.AddDynamic(this, &USTGameplayAbility_ADS::OnRelease);
    InputReleasedTask->ReadyForActivation();
}

void USTGameplayAbility_ADS::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
    }
}

void USTGameplayAbility_ADS::OnRelease(float TimeHeld)
{
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);    // no need to replicate, server runs this too
}

void USTGameplayAbility_ADS::ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (ActorInfo)
    {
        ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
        if (Character && ActorInfo->AbilitySystemComponent.Get())
        {
            //Character->StopADSing();
            ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(ADSEffectActiveHandle);
        }
        else
        {
            UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() Couldn't call Character->StopADSing() or remove ADSEffectActiveHandle because Character* was NULL"), ANSI_TO_TCHAR(__FUNCTION__));
        }
    }
    else
    {
        UE_LOG(LogSTGameplayAbility, Error, TEXT("%s() ActorInfo was NULL when trying to remove ADSEffectActiveHande and when trying to call StopADSing on the character"), ANSI_TO_TCHAR(__FUNCTION__));
    }


    Super::ASSEndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
