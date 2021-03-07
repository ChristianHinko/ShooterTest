// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"
#include "WeaponStack.generated.h"

class AGATA_BulletTrace;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UWeaponStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Target Actor")
		TSubclassOf<AGATA_BulletTrace> BulletTraceTargetActorTSub;
};
