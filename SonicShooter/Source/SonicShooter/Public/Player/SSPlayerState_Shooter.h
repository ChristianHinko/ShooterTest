// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSPlayerState.h"

#include "SSPlayerState_Shooter.generated.h"


class USSAbilitySystemComponent_Shooter;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState_Shooter : public ASSPlayerState
{
	GENERATED_BODY()
	
public:
	ASSPlayerState_Shooter(const FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY()
		TWeakObjectPtr<USSAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

};
