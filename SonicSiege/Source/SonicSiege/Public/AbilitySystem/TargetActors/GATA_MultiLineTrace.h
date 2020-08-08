// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"

#include "GATA_MultiLineTrace.generated.h"



/**
 * THIS IS CURRENTLY BROKEN!!
 * Maybe dont event inherit from target actor _Trace because I'm having to change so much of it
 * Maybe make a AGATA_Traces or something and make this inherit from that
 * If we ever want to use this again what you need to do is make the for loop in ConfirmTargetingAndContinue not run PerformTrace
 * every iteration. Instead implement the for loop inside of PerformTrace (but PerfromTrace only returns one FHitResult not a TArray) which is why
 * you should not use it and maybe not even inherit from _Trace
 * 
 * Right now its not working because the AimWithPlayerController function called in PerformTrace is not meant for multiple traces and each itteration of the
 * for loop in ConfirmTargetingAndContinue the line trace swill flip back and forth because of this
 */
UCLASS()
class SONICSIEGE_API AGATA_MultiLineTrace : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	AGATA_MultiLineTrace();


	uint8 maxTraces;
protected:
	//BEGIN AGameplayAbilityTargetActor_Trace Interface
	virtual void ConfirmTargetingAndContinue() override;
	//virtual FHitResult PerformTrace(AActor* InSourceActor) override;
	//END AGameplayAbilityTargetActor_Trace Interface

	virtual TArray<FHitResult> PerformMultiTraces(AActor* InSourceActor);
};
