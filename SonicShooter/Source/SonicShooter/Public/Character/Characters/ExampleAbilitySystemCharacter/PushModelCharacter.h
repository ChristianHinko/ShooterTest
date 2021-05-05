// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AbilitySystemCharacter.h"

#include "PushModelCharacter.generated.h"



/**
 * Push model demo character.
 * 
 * Primary fire to increment MyPushModelFloat.
 * Secondary fire to increment it without marking it dirty.
 */
UCLASS()
class SONICSHOOTER_API APushModelCharacter : public AAbilitySystemCharacter
{
	GENERATED_BODY()
	
public:
	APushModelCharacter(const FObjectInitializer& ObjectInitializer);


	void SetMyPushModelFloat(const float NewPushModelFloat);

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPrimaryFirePressed() override;
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerPrimaryFirePressed();

	virtual void OnSecondaryFirePressed() override;
	UFUNCTION(Server, WithValidation, Reliable)
		void ServerSecondaryFirePressed();

private:
	UPROPERTY(Replicated)
		float MyPushModelFloat;
};
