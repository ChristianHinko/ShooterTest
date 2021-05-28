// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"

#include "SSPlayerState.generated.h"


class UAS_PlayerState;


/**
 * Base player state class (GAS implemented)
 */
UCLASS()
class SONICSHOOTER_API ASSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()


public:
	ASSPlayerState(const FObjectInitializer& ObjectInitializer);


	USSAbilitySystemComponent* GetAbilitySystemComponent() const override { return SSAbilitySystemComponent; }
	UAS_PlayerState* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY()
		USSAbilitySystemComponent* SSAbilitySystemComponent;
	static FName AbilitySystemComponentName;

	UPROPERTY()
		UAS_PlayerState* AttributeSet;


};
