// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Abilities/GameplayAbilityTargetDataFilter.h"

#include "GATDF_MultiFilter.generated.h"



/** Actor target filter that can filter by an array of actor types */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGATDF_MultiFilter/* : public FGameplayTargetDataFilter*/
{
	GENERATED_USTRUCT_BODY()

	virtual ~FGATDF_MultiFilter()
	{
	}

	/** Returns true if the actor passes the filter and will be targeted */
	virtual bool FilterPassesForActor(const AActor* ActorToBeFiltered) const
	{
		//switch (SelfFilter.GetValue())
		//{
		//case ETargetDataFilterSelf::Type::TDFS_NoOthers:
		//	if (ActorToBeFiltered != SelfActor)
		//	{
		//		return (bReverseFilter ^ false);
		//	}
		//	break;
		//case ETargetDataFilterSelf::Type::TDFS_NoSelf:
		//	if (ActorToBeFiltered == SelfActor)
		//	{
		//		return (bReverseFilter ^ false);
		//	}
		//	break;
		//case ETargetDataFilterSelf::Type::TDFS_Any:
		//default:
		//	break;
		//}

		for (TSubclassOf<AActor> RequiredActorTSub : RequiredActorClasses)
		{
			if (RequiredActorTSub && ActorToBeFiltered->IsA(RequiredActorTSub))
			{
				return (bReverseFilter ^ false);
			}
		}

		return (bReverseFilter ^ true);
	}

	///** Initializes SelfActor */
	//void InitializeFilterContext(AActor* FilterActor);

	///** Actor we're comparing against. */
	//UPROPERTY()
	//	AActor* SelfActor;

	///** Filter based on whether or not this actor is "self." */
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)
	//	TEnumAsByte<ETargetDataFilterSelf::Type> SelfFilter;

	/** Subclass actors must be one of these to pass the filter. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)
	TArray<TSubclassOf<AActor>> RequiredActorClasses;

	/** Reverses the meaning of the filter, so it will exclude all actors that pass. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)
		bool bReverseFilter;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FGATDF_MultiFilterHandle/* : public FGameplayTargetDataFilterHandle*/
{
	GENERATED_USTRUCT_BODY()

	TSharedPtr<FGATDF_MultiFilter> MultiFilter;

	/** Returns true if the actor passes the filter and will be targeted */
	bool FilterPassesForActor(const AActor* ActorToBeFiltered) const
	{
		if (!ActorToBeFiltered)
		{
			// If no filter is set, then always return true even if there is no actor.
			// If there is no actor and there is a filter, then always fail.
			return (MultiFilter.IsValid() == false);
		}
		//Eventually, this might iterate through multiple filters. We'll need to decide how to designate OR versus AND functionality.
		if (MultiFilter.IsValid())
		{
			if (!MultiFilter.Get()->FilterPassesForActor(ActorToBeFiltered))
			{
				return false;
			}
		}
		return true;
	}

	bool FilterPassesForActor(const TWeakObjectPtr<AActor> ActorToBeFiltered) const
	{
		return FilterPassesForActor(ActorToBeFiltered.Get());
	}

	bool operator()(const TWeakObjectPtr<AActor> ActorToBeFiltered) const
	{
		return FilterPassesForActor(ActorToBeFiltered.Get());
	}

	bool operator()(const AActor* ActorToBeFiltered) const
	{
		return FilterPassesForActor(ActorToBeFiltered);
	}
};
