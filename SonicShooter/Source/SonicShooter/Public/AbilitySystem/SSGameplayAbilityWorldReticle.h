// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityWorldReticle.h"

#include "SSGameplayAbilityWorldReticle.generated.h"



/**
 * 
 */
USTRUCT(BlueprintType)
struct FSSWorldReticleParameters : public FWorldReticleParameters
{
	GENERATED_BODY()


};

/**
 * Our base World Reticle class
 */
UCLASS(Blueprintable, notplaceable)
class SONICSHOOTER_API ASSGameplayAbilityWorldReticle : public AGameplayAbilityWorldReticle
{
	GENERATED_BODY()
	
public:
	ASSGameplayAbilityWorldReticle();


	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Reticle")
		FSSWorldReticleParameters SSParameters;

	virtual void SSInitializeReticle(AActor* InTargetingActor, APlayerController* PlayerController, FSSWorldReticleParameters InSSParameters);

protected:

};
