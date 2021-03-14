// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActorPoolerSubsystem.generated.h"

class ASSActor;
/**
	A good example to reference if you ever need to pool a specific type.
	Every pool in your game should be on a different subsystem.
	This code could be used exactly how it is if you just need a pool of type ASSActor.
	If you need a pool of differnt type just swap out all ASSActor types to your desired type.
	I would suggest not using a naming convention like for example USSCharacterPoolerSubsystem
	because if you want another pool of the same type you will need to call the new subsystem
	something different. Like USSCharacterPoolerSubsystem1 or something. 
	But honestly do what you want.
 */
UCLASS() //UCLASS(Abstract)	// This class is abstract because this is only an example of how you would make a pooler subsystem. We don't want this instantiated at runtime
class SONICSHOOTER_API UActorPoolerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	UActorPoolerSubsystem();

	UPROPERTY(BlueprintReadWrite, Category = "Pooling|Variables")
		int32 maxPoolSize;
	UPROPERTY(BlueprintReadWrite, Category = "Pooling|Variables")
		uint8 bDebugPooling : 1;

private:
	TArray<TWeakObjectPtr<ASSActor>> Pooled;

	ASSActor* GetFromPool();

	UFUNCTION(BlueprintCallable, Category = "Pooling|Functions")
		ASSActor* SpawnOrReactivate(TSubclassOf<ASSActor> ActorClass, AActor* ActorOwner, APawn* ActorInstigator, const FTransform& Transform);
	UFUNCTION(BlueprintCallable, Category = "Pooling|Functions")
		void DeativateToPool(ASSActor* ActorToDeactivate);


	UFUNCTION(BlueprintPure, Category = "Pooling|Helpers")
		int32 GetCurrentPoolSize();
	UFUNCTION(BlueprintPure, Category = "Pooling|Helpers")
		bool IsPoolFull();
};
