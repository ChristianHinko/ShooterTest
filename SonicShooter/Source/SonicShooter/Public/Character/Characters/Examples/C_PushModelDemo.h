// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SSCharacter.h"

#include "C_PushModelDemo.generated.h"



/**
 * Push model demo character.
 *
 * Primary fire to increment MyPushModelFloat.
 * Secondary fire to increment it without marking it dirty.
 */
UCLASS()
class SONICSHOOTER_API AC_PushModelDemo : public ASSCharacter
{
	GENERATED_BODY()

public:
	AC_PushModelDemo(const FObjectInitializer& ObjectInitializer);


	void SetMyPushModelFloat(const float NewPushModelFloat);

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPressedPrimaryFire() override;
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerOnPressedPrimaryFire();

	virtual void OnPressedSecondaryFire() override;
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerOnPressedSecondaryFire();

private:
	UPROPERTY(Replicated)
		float MyPushModelFloat;
};
