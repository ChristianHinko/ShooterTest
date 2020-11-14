// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/SSActor.h"
#include "Interfaces/Poolable.h"

#include "MyPooledActor.generated.h"

UCLASS()
class SONICSHOOTER_API AMyPooledActor : public ASSActor, public IPoolable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPooledActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
