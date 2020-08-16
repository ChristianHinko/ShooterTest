// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActors/GATA_Trace.h"
#include "GATA_LineTrace.generated.h"

/**
 * 
 */
UCLASS()
class SONICSIEGE_API AGATA_LineTrace : public AGATA_Trace
{
	GENERATED_BODY()
	
protected:
	virtual void PerformTrace(TArray<FHitResult>& OutHitResults, AActor* InSourceActor);
};