// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Shooter.h"

#include "C_Sonic.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AC_Sonic : public AC_Shooter
{
	GENERATED_BODY()
	
public:
	AC_Sonic(const FObjectInitializer& ObjectInitializer);

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
