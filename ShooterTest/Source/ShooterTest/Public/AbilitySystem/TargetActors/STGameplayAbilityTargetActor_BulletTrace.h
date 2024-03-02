// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActor/ASSGameplayAbilityTargetActor.h"

#include "STGameplayAbilityTargetActor_BulletTrace.generated.h"



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API ASTGameplayAbilityTargetActor_BulletTrace : public AASSGameplayAbilityTargetActor
{
    GENERATED_BODY()

public:
    ASTGameplayAbilityTargetActor_BulletTrace(const FObjectInitializer& ObjectInitializer);

    bool bDebugHitTargetDataDmg; // An extra debug of dmg done on target hits

    /** Max distance to travel */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        float MaxRange;
    /** Number of bullets to shoot (a shotgun-like feature) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        int32 NumOfBullets;
    /** Max times to penetrate through blocking hits (assign a value of -1 for an unbound number of penetrations) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        int32 MaxPenetrations;
    /** Max times to ricochet (assign a value of -1 for an unbound number of ricochets) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        int32 MaxRicochets;
    /** Bullet speed that is slowed down by ricochets and penetrations. Bullet stops when we run out of bullet speed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        float InitialBulletSpeed;
    /** The falloff of range for this bullet per cm    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        float RangeFalloffNerf;
    /** The spread of the bullet direction */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        float CurrentBulletSpread;

    /** Trace channel for collision queries */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet")
        TEnumAsByte<ECollisionChannel> TraceChannel;

    /** This is injected in every fire */
    UPROPERTY(/*BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "Bullet"*/)
        int16 FireSpecificNetSafeRandomSeed;


    virtual void ConfirmTargetingAndContinue() override;

};
