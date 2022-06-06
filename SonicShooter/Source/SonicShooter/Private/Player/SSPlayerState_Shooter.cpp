// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState_Shooter.h"

#include "AbilitySystem/AbilitySystemComponents/SSAbilitySystemComponent_Shooter.h"



ASSPlayerState_Shooter::ASSPlayerState_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSAbilitySystemComponent_Shooter>(AbilitySystemComponentName))
{
	ShooterAbilitySystemComponent = Cast<USSAbilitySystemComponent_Shooter>(ASSAbilitySystemComponent);


}
