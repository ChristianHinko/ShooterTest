// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacter_Shooter.h"

#include "SSCharacter_Sonic.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API ASSCharacter_Sonic : public ASSCharacter_Shooter
{
	GENERATED_BODY()
	
public:
	ASSCharacter_Sonic(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	//virtual void OnJumpPressed() override;
	//virtual void OnJumpReleased() override;

	//virtual void OnRunPressed() override;
	//virtual void OnRunReleased() override;

	//virtual void OnCrouchPressed() override;
	//virtual void OnCrouchReleased() override;
};
