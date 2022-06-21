// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SSPlayerController.generated.h"



/**
 * Base PlayerController class.
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASSPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	//BEGIN AController Interface
	virtual void InitPlayerState() override;
	virtual void OnRep_PlayerState() override;
	//END AController Interface

	virtual void EndPlayingState() override;
};
