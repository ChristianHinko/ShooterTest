// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Generators/ArcItemGenerator_Unique.h"

#include "SSItemGenerator_Gun.generated.h"



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSItemGenerator_Gun : public UArcItemGenerator_Unique
{
	GENERATED_BODY()
	
public:
	USSItemGenerator_Gun(const FObjectInitializer& ObjectInitializer);


protected:
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;

};
