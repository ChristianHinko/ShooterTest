// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h"

#include "Net/UnrealNetwork.h"



void UAS_ExampleAbilitySystemCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_ExampleAbilitySystemCharacter, ExampleAttribute, COND_None, REPNOTIFY_Always);
}

UAS_ExampleAbilitySystemCharacter::UAS_ExampleAbilitySystemCharacter()
	: ExampleAttribute(0)
{

}


void UAS_ExampleAbilitySystemCharacter::OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_ExampleAbilitySystemCharacter, ExampleAttribute, ServerBaseValue);
}
