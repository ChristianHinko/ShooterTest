// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types\PropertyWrappers\GCPropertyWrappers.h"
#include "Modular/ArcItemFragment.h"

#include "STItemFragment_ClipAmmo.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_ClipAmmo : public UArcItemFragment
{
	GENERATED_BODY()

public:
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

public:
	USTItemFragment_ClipAmmo();


	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Ammo")
		FGCInt32PropertyWrapper ClipAmmo;
};
