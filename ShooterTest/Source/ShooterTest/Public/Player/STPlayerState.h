// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ASSEPlayerState_AbilitySystemPlayerState.h"

#include "STPlayerState.generated.h"

class UGSActorComponent_PlayerStateExtension;
class USTAttributeSet_PlayerState;

/**
 * Game's base player state class.
 */
UCLASS()
class SHOOTERTEST_API ASTPlayerState : public AASSEPlayerState_AbilitySystemPlayerState
{
    GENERATED_BODY()

public:

    ASTPlayerState(const FObjectInitializer& inObjectInitializer);

public:

    FORCEINLINE USTAttributeSet_PlayerState& GetAttributeSetChecked() const
    {
        check(PlayerAttributeSet);
        return *PlayerAttributeSet;
    }

protected:

    UPROPERTY()
    TObjectPtr<UGSActorComponent_PlayerStateExtension> GSPlayerStateExtensionComponent = nullptr;

    UPROPERTY()
    TObjectPtr<USTAttributeSet_PlayerState> PlayerAttributeSet = nullptr;
};
