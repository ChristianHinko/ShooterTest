// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/STPlayerState_Shooter.h"

#include "AbilitySystem/AbilitySystemComponents/STAbilitySystemComponent_Shooter.h"



ASTPlayerState_Shooter::ASTPlayerState_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USTAbilitySystemComponent_Shooter>(AbilitySystemComponentName))
{
	ShooterAbilitySystemComponent = Cast<USTAbilitySystemComponent_Shooter>(ASSAbilitySystemComponent);


}
