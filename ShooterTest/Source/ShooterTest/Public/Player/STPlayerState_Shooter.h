// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/STPlayerState.h"

#include "STPlayerState_Shooter.generated.h"


class USTAbilitySystemComponent_Shooter;



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API ASTPlayerState_Shooter : public ASTPlayerState
{
	GENERATED_BODY()
	
public:
	ASTPlayerState_Shooter(const FObjectInitializer& ObjectInitializer);


protected:
	UPROPERTY()
		TWeakObjectPtr<USTAbilitySystemComponent_Shooter> ShooterAbilitySystemComponent;

};
