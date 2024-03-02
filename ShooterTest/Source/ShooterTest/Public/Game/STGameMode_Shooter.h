// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/STGameMode.h"

#include "STGameMode_Shooter.generated.h"



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API ASTGameMode_Shooter : public ASTGameMode
{
    GENERATED_BODY()

public:
    ASTGameMode_Shooter(const FObjectInitializer& ObjectInitializer);


    virtual void SetPlayerDefaults(APawn* PlayerPawn) override;
};
