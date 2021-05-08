// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayEffectTypes.h"



FSSGameplayEffectContext::FSSGameplayEffectContext()
{

}


bool FSSGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return Super::NetSerialize(Ar, Map, bOutSuccess);
}
