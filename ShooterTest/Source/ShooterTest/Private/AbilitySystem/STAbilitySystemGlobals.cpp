// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/STAbilitySystemGlobals.h"

#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "AbilitySystem/Types/STGameplayEffectTypes.h"



USTAbilitySystemGlobals::USTAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


FGameplayAbilityActorInfo* USTAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return new FSTGameplayAbilityActorInfo_Shooter();
}
FGameplayEffectContext* USTAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FSTGameplayEffectContext_Shooter();
}
