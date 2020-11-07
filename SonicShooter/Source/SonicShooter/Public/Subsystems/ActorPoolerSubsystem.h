// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActorPoolerSubsystem.generated.h"

class ASSActor;
/**
	A few things to note:
		1) Deactivate means it takes it out of the world and puts it in the pool
			-Also EndPlay() gets called when this happens
		2) Recycle means it reactivates(brings it back into the world)
			-BeginPlay() will be called every time this happens
 */
UCLASS()
class SONICSHOOTER_API UActorPoolerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	UActorPoolerSubsystem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		bool EnablePooling = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Debug")
		bool DebugPooling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pooling")
		int MaxPoolSize = 50;

	virtual void LifeSpanExpired();
private:
	UPROPERTY()
		TArray<TWeakObjectPtr<ASSActor>> Pooled;

	ASSActor* GetFromPool(UClass* BulletClass);
	ASSActor* SpawnOrReactivate(TSubclassOf<class ASSActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator);
	void DeativateToPool(ASSActor* ActorToDeactivate);
};
