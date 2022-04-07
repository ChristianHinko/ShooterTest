// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSPlayerState.h"

#include "PS_Shooter.generated.h"


class UASC_Shooter;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API APS_Shooter : public ASSPlayerState
{
	GENERATED_BODY()
	
public:
	APS_Shooter(const FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY()
		TWeakObjectPtr<UASC_Shooter> ShooterAbilitySystemComponent;

};
