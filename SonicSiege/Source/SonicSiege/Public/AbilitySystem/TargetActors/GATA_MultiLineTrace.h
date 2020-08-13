// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TargetActors/GATA_MultiTrace.h"

#include "GATA_MultiLineTrace.generated.h"



/**
 * This target actor will collect all desired actors (specified by ActorClassToCollect) by using multiple line traces (maximum value
 * specified by maxTraces) and end when it hits a non-ActorClassToCollect
 * 
 * This doesn't take into account collision profiles yet
 */
UCLASS()
class SONICSIEGE_API AGATA_MultiLineTrace : public AGATA_MultiTrace
{
	GENERATED_BODY()

public:
	AGATA_MultiLineTrace();


	uint8 maxTraces;

	TSubclassOf<AActor> ActorClassToCollect;

protected:
	//BEGIN AGameplayAbilityTargetActor_Trace Interface
	virtual void ConfirmTargetingAndContinue() override;
	//virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	//END AGameplayAbilityTargetActor_Trace Interface

	TArray<FHitResult> PerformMultiTraces(AActor* InSourceActor);
};
