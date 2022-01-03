// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSAbilitySystemGlobals.h"

#include "AbilitySystem/SSGameplayAbilityTypes.h"
#include "AbilitySystem/SSGameplayEffectTypes.h"



USSAbilitySystemGlobals::USSAbilitySystemGlobals()
{

}


FGameplayAbilityActorInfo* USSAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return new FGAAI_Shooter();
}
FGameplayEffectContext* USSAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FGEC_Shooter();
}
