// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PS_AbilitySystemPlayerState.h"

#include "SSPlayerState.generated.h"


class UAS_PlayerState;



/**
 * Base Player State
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState : public APS_AbilitySystemPlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		UAS_PlayerState* PlayerAttributeSet;

public:
	ASSPlayerState(const FObjectInitializer& ObjectInitializer);


	UAS_PlayerState* GetAttributeSet() const { return PlayerAttributeSet; }

};
