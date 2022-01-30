// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wrappers/PropertyWrappers.h"

#include "O_Gun.generated.h"



/**
 * Has CurrentBulletSpread float
 */
UCLASS()
class SONICSHOOTER_API UO_Gun : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
		UO_Gun(const FObjectInitializer& ObjectInitializer);


		TSharedRef<FFloatValueChange> OnCurrentBulletSpreadChange;

		/** Current bullet spread. Non-replicated because set every frame */
		UPROPERTY(BlueprintReadOnly/*, Replicated*/, Category = "Gun")
			FFloatPropertyWrapper CurrentBulletSpread;

protected:
		//BEGIN FTickableObjectBase interface
		virtual bool IsTickable() const override;
		virtual void Tick(float DeltaTime) override;
		virtual TStatId GetStatId() const override { return TStatId(); }
		//END FTickableObjectBase interface

		//BEGIN FTickableGameObject interface
		virtual bool IsTickableWhenPaused() const override { return false; };
		//END FTickableGameObject interface

};
