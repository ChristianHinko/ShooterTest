// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "O_Stamina.generated.h"

/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UO_Stamina : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
		UO_Stamina();

		// Begin FTickableObjectBase interface
		virtual bool IsTickable() const;
		virtual void Tick(float DeltaTime) override;
		virtual TStatId GetStatId() const override { return TStatId(); }
		// End FTickableObjectBase interface

		// Begin FTickableGameObject interface
		virtual bool IsTickableWhenPaused() const { return false; };
		// end FTickableGameObject interface
};
