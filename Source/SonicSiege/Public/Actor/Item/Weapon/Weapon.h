// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/Item.h"
#include "Weapon.generated.h"

class UAS_Weapon;

/**
 * 
 */
UCLASS()
class SONICSIEGE_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:
	AWeapon();

	UPROPERTY()
		UAS_Weapon* WeaponAttributeSet;

	void Fire();

protected:
	virtual void CreateAttributeSets() override;
	virtual void RegisterAttributeSets() override;
};
