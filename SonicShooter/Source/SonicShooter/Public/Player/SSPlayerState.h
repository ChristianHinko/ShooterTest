// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ASSEPlayerState_AbilitySystemPlayerState.h"

#include "SSPlayerState.generated.h"


class USSAttributeSet_PlayerState;



/**
 * Base Player State
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState : public AASSEPlayerState_AbilitySystemPlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TObjectPtr<USSAttributeSet_PlayerState> PlayerAttributeSet;

public:
	ASSPlayerState(const FObjectInitializer& ObjectInitializer);


	USSAttributeSet_PlayerState* GetAttributeSet() const { return PlayerAttributeSet; }

};
