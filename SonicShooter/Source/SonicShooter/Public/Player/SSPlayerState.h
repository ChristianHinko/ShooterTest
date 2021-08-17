// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/AbilitySystemPlayerState.h"

#include "SSPlayerState.generated.h"


class UAS_PlayerState;



/**
 * Base Player State
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState : public AAbilitySystemPlayerState
{
	GENERATED_BODY()


public:
	ASSPlayerState(const FObjectInitializer& ObjectInitializer);


	UAS_PlayerState* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY()
		UAS_PlayerState* AttributeSet;

};
