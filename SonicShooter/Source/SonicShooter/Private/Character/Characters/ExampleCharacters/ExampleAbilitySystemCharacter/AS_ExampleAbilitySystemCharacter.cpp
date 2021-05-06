// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/ExampleCharacters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h"

#include "Net/UnrealNetwork.h"



void UAS_ExampleAbilitySystemCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_ExampleAbilitySystemCharacter, ExampleAttribute, Params);
}

UAS_ExampleAbilitySystemCharacter::UAS_ExampleAbilitySystemCharacter()
	: ExampleAttribute(0)
{

}


void UAS_ExampleAbilitySystemCharacter::OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_ExampleAbilitySystemCharacter, ExampleAttribute, ServerBaseValue);
}
