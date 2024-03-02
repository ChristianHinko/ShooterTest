// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modular/ArcItemFragment.h"
#include "Types/PropertyWrappers/GCPropertyWrappers.h"

#include "STItemFragment_ClipAmmo.generated.h"

/**
 * This fragment only exists so that item definitions can indicate that a
 * fragment should be created for item stacks. TODO @techdebt: This is unecessarily
 * heavy for an item definition fragment with no data on it.
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_ClipAmmo : public UArcItemFragment
{
    GENERATED_BODY()
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
