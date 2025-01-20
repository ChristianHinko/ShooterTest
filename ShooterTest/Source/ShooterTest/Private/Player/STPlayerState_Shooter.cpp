// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/STPlayerState_Shooter.h"

#include "AbilitySystem/STAbilitySystemComponent_Shooter.h"

ASTPlayerState_Shooter::ASTPlayerState_Shooter(const FObjectInitializer& inObjectInitializer)
    : Super(inObjectInitializer.SetDefaultSubobjectClass<USTAbilitySystemComponent_Shooter>(GetAbilitySystemComponentName()))
{
}
