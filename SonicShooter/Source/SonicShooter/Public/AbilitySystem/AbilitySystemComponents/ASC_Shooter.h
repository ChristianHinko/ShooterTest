// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
#include "Wrappers/PropertyWrappers.h"

#include "ASC_Shooter.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UASC_Shooter : public USSAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UASC_Shooter();


	// Change delegates:

	TSharedRef<FFloatValueChange> OnClipAmmoChange = MakeShared<FFloatValueChange>();
	TSharedRef<FFloatValueChange> OnCurrentBulletSpreadChange = MakeShared<FFloatValueChange>();


protected:

};
