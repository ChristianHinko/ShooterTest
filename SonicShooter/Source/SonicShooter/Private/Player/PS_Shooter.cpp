// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PS_Shooter.h"

#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"



APS_Shooter::APS_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UASC_Shooter>(AbilitySystemComponentName))
{
	ShooterAbilitySystemComponent = Cast<UASC_Shooter>(ASSAbilitySystemComponent);


}
