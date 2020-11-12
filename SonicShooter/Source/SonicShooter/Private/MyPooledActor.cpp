// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPooledActor.h"

// Sets default values
AMyPooledActor::AMyPooledActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bDebugPooling = true;
}

// Called when the game starts or when spawned
void AMyPooledActor::BeginPlay()
{
	Super::BeginPlay();
	
}

ASSActor* AMyPooledActor::GetSSActor()
{
	return this;
}

// Called every frame
void AMyPooledActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

