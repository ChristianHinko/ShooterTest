// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/SSEngineSubsystem.h"

#include "AbilitySystemGlobals.h"



void USSEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


	UAbilitySystemGlobals::Get().InitGlobalData();
}
