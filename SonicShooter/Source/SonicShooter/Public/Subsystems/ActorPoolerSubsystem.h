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
		int MaxPoolSize = 50;

private:
	UPROPERTY()
		TArray<TWeakObjectPtr<ASSActor>> Pooled;

	ASSActor* GetFromPool(UClass* BulletClass);

	UFUNCTION(BlueprintCallable)
		ASSActor* SpawnOrReactivate(TSubclassOf<ASSActor> ActorClass, AActor* ActorOwner, APawn* ActorInstigator, const FTransform& Transform);
	UFUNCTION(BlueprintCallable)
		void DeativateToPool(ASSActor* ActorToDeactivate);
};
