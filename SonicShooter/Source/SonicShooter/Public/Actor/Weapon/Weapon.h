// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AbilitySystemActor.h"
#include "Weapon.generated.h"

class UAS_Weapon;
class AGATA_BulletTrace;

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API AWeapon : public AAbilitySystemActor
{
	GENERATED_BODY()
	
public:
	AWeapon();

	UAS_Weapon* GetWeaponAttributeSet() const { return WeaponAttributeSet; }
	AGATA_BulletTrace* GetBulletTraceTargetActor() const { return BulletTraceTargetActor; }
	FGameplayAbilitySpecHandle GetFireAbilitySpecHandle() const { return FireAbilitySpecHandle; }

protected:
#pragma region Abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<USSGameplayAbility> FireAbilityTSub;
	UPROPERTY(Replicated)
		FGameplayAbilitySpecHandle FireAbilitySpecHandle;
#pragma endregion
	UPROPERTY()
		UAS_Weapon* WeaponAttributeSet;


	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<AGATA_BulletTrace> BulletTraceTargetActorTSub;
	UPROPERTY()
		AGATA_BulletTrace* BulletTraceTargetActor;

	//BEGIN AActor Interface
	virtual void BeginPlay() override;
	//END AActor Interface

	//BEGIN AAbilitySystemActor Interface
	virtual void CreateAttributeSets() override;
	virtual void RegisterAttributeSets() override;
	virtual bool GrantStartingAbilities() override;
	//END AAbilitySystemActor Interface
};
