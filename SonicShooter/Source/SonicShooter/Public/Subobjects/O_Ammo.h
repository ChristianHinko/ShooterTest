// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"

#include "O_Ammo.generated.h"



/**
 * Has ammo float
 */
UCLASS()
class SONICSHOOTER_API UO_Ammo : public UObject
{
	GENERATED_BODY()
	
public:
	UO_Ammo(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Ammo")
		FFloatPropertyWrapper ClipAmmo;
	TSharedRef<FFloatValueChange> OnClipAmmoChange;

protected:

};
