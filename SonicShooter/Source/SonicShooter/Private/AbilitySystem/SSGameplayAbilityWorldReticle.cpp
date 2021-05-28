// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSGameplayAbilityWorldReticle.h"



ASSGameplayAbilityWorldReticle::ASSGameplayAbilityWorldReticle()
{

}


void ASSGameplayAbilityWorldReticle::SSInitializeReticle(AActor* InTargetingActor, APlayerController* PlayerController, FSSWorldReticleParameters InSSParameters)
{
	check(InTargetingActor);

	SSParameters = InSSParameters;

	InitializeReticle(InTargetingActor, PlayerController, InSSParameters); // call at the end instead of beginning because of their call to OnParametersInitialized()
}
