// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generators/ArcItemGenerator_Unique.h"

#include "GunGenerator.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGunGenerator : public UArcItemGenerator_Unique
{
	GENERATED_BODY()
	
public:
	UGunGenerator(const FObjectInitializer& ObjectInitializer);


protected:
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;

};
