// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ShooterCharacter.h"
#include "Sonic.generated.h"

class AWeapon;///////// remove this

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API ASonic : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	ASonic(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	// testing, delete these
	AWeapon* TestWeapon;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AWeapon> MyTestWeapon;

	FTimerHandle MyTimerHandle;
	void MyTimerCallback();

};