// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayEffectTypes.h"



bool FSSGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	// TODO: look at Kaos' method for this

	return Super::NetSerialize(Ar, Map, bOutSuccess) && TargetData.NetSerialize(Ar, Map, bOutSuccess);
}
