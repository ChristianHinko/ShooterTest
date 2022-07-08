// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ASSEPlayerState_AbilitySystemPlayerState.h"

#include "STPlayerState.generated.h"


class UGSActorComponent_PlayerStateExtension;
class USTAttributeSet_PlayerState;



/**
 * Game's base PlayerState class
 */
UCLASS()
class SHOOTERTEST_API ASTPlayerState : public AASSEPlayerState_AbilitySystemPlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TObjectPtr<UGSActorComponent_PlayerStateExtension> GSPlayerStateExtensionComponent;
	UPROPERTY()
		TObjectPtr<USTAttributeSet_PlayerState> PlayerAttributeSet;

public:
	ASTPlayerState(const FObjectInitializer& ObjectInitializer);


	USTAttributeSet_PlayerState* GetAttributeSet() const { return PlayerAttributeSet; }

};
