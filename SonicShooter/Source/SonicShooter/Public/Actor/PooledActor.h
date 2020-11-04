// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledActor.generated.h"

UCLASS()
class SONICSHOOTER_API APooledActor : public AActor
{
	GENERATED_BODY()
	

public:
	APooledActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		bool EnablePooling = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch")
		bool SafeLaunch = true;
	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool OwnerSafe = false;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "State")
		FVector Velocity;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "State")
		FRandomStream RandomStream;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
		TArray<AActor*> IgnoredActors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Safe launch", Meta = (EditCondition = "SafeLaunch"))
		float SafeDelay = 1.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
		bool DebugPooling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		int MaxPoolSize = 50;

	//pooling
	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "EBBullet|Pooling")
		void Deactivate();
	UFUNCTION(NetMulticast, Reliable)
		void ReactivationBroadcast(FVector_NetQuantize NewLocation, FVector NewVelocity, AActor* BulletOwner, APawn* BulletInstigator);
	UFUNCTION(NetMulticast, Reliable)
		void DeactivationBroadcast();
	virtual void LifeSpanExpired() override;
private:
	UPROPERTY()
		TArray<TWeakObjectPtr<APooledActor>> Pooled;

	bool CanRetrace = false;
	static APooledActor* GetFromPool(UWorld* World, UClass* BulletClass);
	static APooledActor* SpawnOrReactivate(UWorld* World, TSubclassOf<class APooledActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator);
	void DeativateToPool();
};
