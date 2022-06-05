// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ASSEPlayerState_AbilitySystemPlayerState.h"

#include "SSPlayerState.generated.h"


class UAS_PlayerState;



/**
 * Base Player State
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState : public AASSEPlayerState_AbilitySystemPlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TObjectPtr<UAS_PlayerState> PlayerAttributeSet;

public:
	ASSPlayerState(const FObjectInitializer& ObjectInitializer);


	UAS_PlayerState* GetAttributeSet() const { return PlayerAttributeSet; }

};
