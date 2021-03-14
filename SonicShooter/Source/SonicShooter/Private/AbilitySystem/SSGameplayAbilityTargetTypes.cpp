// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilitySystem\SSGameplayAbilityTargetTypes.h"

bool FGameplayAbilityTargetData_RicochetTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	HitResult.NetSerialize(Ar, Map, bOutSuccess);

	return true;
}