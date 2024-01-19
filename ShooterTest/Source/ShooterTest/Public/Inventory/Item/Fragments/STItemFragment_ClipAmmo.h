// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/PropertyWrappers/GCPropertyWrappers.h"
#include "Modular/ArcItemFragment.h"

#include "STItemFragment_ClipAmmo.generated.h"

class UArcItemStackModular;
class USTItemFragment_ClipAmmoInstanced;

/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_ClipAmmo : public UArcItemFragment
{
	GENERATED_BODY()

public:

	USTItemFragment_ClipAmmo();

public:

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGCInt32PropertyWrapper ClipAmmo;

	USTItemFragment_ClipAmmoInstanced& GetOrCreateInstancedClipAmmoFragment(UArcItemStackModular* itemStack) const;
};

/**
 *
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_ClipAmmoInstanced : public UArcItemFragment
{
	GENERATED_BODY()

public:

	USTItemFragment_ClipAmmoInstanced();

public:

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Ammo")
	FGCInt32PropertyWrapper ClipAmmo;
};
