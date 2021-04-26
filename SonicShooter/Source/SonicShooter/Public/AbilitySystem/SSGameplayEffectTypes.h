// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"

#include "Abilities/GameplayAbilityTargetTypes.h"

#include "SSGameplayEffectTypes.generated.h"


//struct FGameplayAbilityTargetDataHandle;



/**
 * Our custom FGameplayEffectContext
 * 
 * TODO: THIS IS NOT READY I JUST COPIED THIS FROM GAS-SHOOTER AND KAOS DOES HIS REALLY DIFFERENTLY! LOOK INTO THIS
 * 
 * 
 * Dan:
 * 
 * Data structure that stores an instigator and related data, such as positions and targets
 * Games can subclass this structure and add game-specific information
 * It is passed throughout effect execution so it is a great place to track transient information about an execution
 */
USTRUCT()
struct SONICSHOOTER_API FSSGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	virtual FGameplayAbilityTargetDataHandle GetTargetData() // Kaos' example doesnt have this
	{
		return TargetData;
	}

	virtual void AddTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle) // Kaos' example doesnt have this
	{
		TargetData.Append(TargetDataHandle);
	}


	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FSSGameplayEffectContext::StaticStruct();
	}

	virtual FSSGameplayEffectContext* Duplicate() const override
	{
		FSSGameplayEffectContext* NewContext = new FSSGameplayEffectContext();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		// Shallow copy of TargetData, is this okay?
		NewContext->TargetData.Append(TargetData);
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:
	FGameplayAbilityTargetDataHandle TargetData; // Kaos' example doesnt have this
};

template<>
struct TStructOpsTypeTraits<FSSGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FSSGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
