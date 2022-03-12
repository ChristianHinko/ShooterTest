// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"

#include "O_ClipAmmo.generated.h"



/**
 * Has ammo float
 */
UCLASS()
class SONICSHOOTER_API UO_ClipAmmo : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);
	
public:
	UO_ClipAmmo(const FObjectInitializer& ObjectInitializer);


	TSharedRef<FFloatValueChange> OnClipAmmoChange;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Ammo")
		FFloatPropertyWrapper ClipAmmo;


protected:

};
