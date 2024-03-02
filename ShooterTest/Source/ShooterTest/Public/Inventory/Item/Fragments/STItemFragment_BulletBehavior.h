// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modular/ArcItemFragment.h"

#include "STItemFragment_BulletBehavior.generated.h"

class AGameplayAbilityTargetActor;
class UGameplayEffect;
/**
 * Define how your bullet behaves!
 */
UCLASS()
class SHOOTERTEST_API USTItemFragment_BulletBehavior : public UArcItemFragment
{
    GENERATED_BODY()
public:
    /**
     * This gun's Target Actor (what it will shoot)
     */
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gun Firing")
        TSubclassOf<AGameplayAbilityTargetActor> BulletTargetActorTSub;

    /**
     * The Effect that will be applied to the target that this bullet hits
     */
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Gun Firing")
        TSubclassOf<UGameplayEffect> BulletInflictEffectTSub;
};
