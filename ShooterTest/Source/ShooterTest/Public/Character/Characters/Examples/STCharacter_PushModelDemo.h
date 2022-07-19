// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/STCharacter.h"

#include "STCharacter_PushModelDemo.generated.h"



/**
 * Push model demo character.
 *
 * Primary fire to increment MyPushModelFloat.
 * Secondary fire to increment it without marking it dirty.
 */
UCLASS()
class SHOOTERTEST_API ASTCharacter_PushModelDemo : public ASTCharacter
{
	GENERATED_BODY()

public:
	ASTCharacter_PushModelDemo(const FObjectInitializer& ObjectInitializer);


	void SetMyPushModelFloat(const float NewPushModelFloat);

protected:
	//  BEGIN AActor Interface
	virtual void Tick(float DeltaSeconds) override;
	//  END AActor Interface

	//  BEGIN APawn Interface
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//  END APawn Interface

	virtual void OnPressedPrimaryFire();
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerOnPressedPrimaryFire();

	virtual void OnPressedSecondaryFire();
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerOnPressedSecondaryFire();

private:
	UPROPERTY(Replicated)
		float MyPushModelFloat;
};
