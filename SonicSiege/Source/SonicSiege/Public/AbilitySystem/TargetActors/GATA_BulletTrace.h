// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActors/GATA_Trace.h"
#include "GATA_BulletTrace.generated.h"

//struct FGATDF_MultiFilter;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API AGATA_BulletTrace : public AGATA_Trace
{
	GENERATED_BODY()

public:
	AGATA_BulletTrace(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Scatter)
		uint8 numberOfLines;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Scatter)
		float scatterRadius;

protected:
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor);
};
