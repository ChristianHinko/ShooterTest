// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "Wrappers/PropertyWrappers.h"

#include "ASC_Shooter.generated.h"



/**
 * Shooter specific ASC
 */
UCLASS()
class SONICSHOOTER_API UASC_Shooter : public UASSAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UASC_Shooter(const FObjectInitializer& ObjectInitializer);


protected:

};
