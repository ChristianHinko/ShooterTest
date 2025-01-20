// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/STGameplayAbility.h"

USTGameplayAbility::USTGameplayAbility(const FObjectInitializer& inObjectInitializer)
    : Super(inObjectInitializer)
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    bServerRespectsRemoteAbilityCancellation = false;
    NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ServerOnlyTermination;
}
