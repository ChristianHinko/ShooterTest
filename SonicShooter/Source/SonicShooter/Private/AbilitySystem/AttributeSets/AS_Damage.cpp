// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AS_Damage.h"

#include "Net/UnrealNetwork.h"

void UAS_Damage::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Damage, OutgoingDamage, COND_None, REPNOTIFY_Always);
}

UAS_Damage::UAS_Damage()
	: OutgoingDamage(100)
{


}

// OnReps
void UAS_Damage::OnRep_OutgoingDamage(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Damage, OutgoingDamage, ServerBaseValue);
}
