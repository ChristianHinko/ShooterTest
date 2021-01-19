// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"

#include "WeaponDefinition.generated.h"


class AGATA_BulletTrace;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UWeaponDefinition : public UArcItemDefinition_Active
{
	GENERATED_BODY()
	
public:
	UWeaponDefinition();

};
