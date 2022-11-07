// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types\PropertyWrappers\GCPropertyWrappers.h"

#include "STObject_ClipAmmo.generated.h"



/**
 * Has ammo float
 */
UCLASS()
class SHOOTERTEST_API USTObject_ClipAmmo : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);
	
public:
	USTObject_ClipAmmo(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Ammo")
		FGCInt32PropertyWrapper ClipAmmo;

protected:

};
