// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SSActor.generated.h"


/**
 *  Pooling:
	If pooling is used, the CDO stores the pooled actors in TArray<TWeakObjectPtr<ASSActor>> Pooled
	 Another few things to note :
		1) Deactivate means it takes it out of the worldand puts it in the pool
			-Also EndPlay() gets called when this happens
		2) Recycle means it reactivates(brings it back into the world)
			-BeginPlay() will be called every time this happens
 */
UCLASS()
class SONICSHOOTER_API ASSActor : public AActor
{
	GENERATED_BODY()


public:
	ASSActor();

};
