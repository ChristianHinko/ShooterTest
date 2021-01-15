// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ArcItemPerkTypes.generated.h"

class UArcItemPerkDefinition;

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcPerkModifierData
{
	GENERATED_USTRUCT_BODY()
public:
	FArcPerkModifierData()
	{
		Value = 0.0f;
		ModifierOp = EGameplayModOp::Additive;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameplayModifier)
		FGameplayAttribute Attribute;

	/** The numeric operation of this modifier: Override, Add, Multiply, etc  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameplayModifier)
		TEnumAsByte<EGameplayModOp::Type> ModifierOp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameplayModifier)
		float Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GameplayModifier)
	FGameplayTagQuery SlotApplicationRequirement;
};

FArchive& operator<<(FArchive& Ar, FArcPerkModifierData& PerkData);
