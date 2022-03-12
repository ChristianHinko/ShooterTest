// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/SSArcItemDefinition_Active.h"

#include "ArcItemDefinition_Gun.generated.h"


class AGATA_BulletTrace;



/**
 * 
 */
UCLASS(Abstract)
class SONICSHOOTER_API UArcItemDefinition_Gun : public USSArcItemDefinition_Active
{
	GENERATED_BODY()

public:
	UArcItemDefinition_Gun();


	/**
	 * This gun's Target Actor (what it will shoot)
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun Firing")
		TSubclassOf<AGATA_BulletTrace> DefaultBulletTraceTargetActorTSub;

	/**
	 * The Effect that will be applied to the target that this bullet hits
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun Firing")
		TSubclassOf<UGameplayEffect> DefaultBulletHitEffectTSub;

};
