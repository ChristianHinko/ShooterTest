// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"


/**
 * Pooling:
 * Another few things to note:
 *	1) Deactivate means it takes it out of the world and puts it in the pool
 *		- Also EndPlay() gets called when this happens
 *	2) Recycle means it reactivates (brings it back into the world)
 *		- BeginPlay() will be called every time this happens
 * 
 */
UCLASS()
class SONICSHOOTER_API APooledActor : public AActor
{
	GENERATED_BODY()
	

public:
	APooledActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		bool EnablePooling = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
		bool DebugPooling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		int MaxPoolSize = 50;

	//pooling
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Pooling")
		void Deactivate();
	UFUNCTION(NetMulticast, Reliable)
		void ReactivationBroadcast(FVector_NetQuantize NewLocation, FVector NewVelocity, AActor* BulletOwner, APawn* BulletInstigator);
	UFUNCTION(NetMulticast, Reliable)
		void DeactivationBroadcast();
	virtual void LifeSpanExpired() override;
private:
	UPROPERTY()
		TArray<TWeakObjectPtr<APooledActor>> Pooled;

	static APooledActor* GetFromPool(UWorld* World, UClass* BulletClass);
	static APooledActor* SpawnOrReactivate(UWorld* World, TSubclassOf<class APooledActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator);
	void DeativateToPool();
};

//*Pooling:
//*If pooling is used, the CDO stores the pooled actors in TArray<TWeakObjectPtr<APooledActor>> Pooled
//* Another few things to note :
//*1) Deactivate means it takes it out of the worldand puts it in the pool
//* -Also EndPlay() gets called when this happens
//* 2) Recycle means it reactivates(brings it back into the world)
//* -BeginPlay() will be called every time this happens