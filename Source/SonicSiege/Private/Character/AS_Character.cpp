// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_Character.h"

#include "Net/UnrealNetwork.h"



void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkSpeed, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkAcceleration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunAccelaration, COND_None, REPNOTIFY_Always);
}

UAS_Character::UAS_Character()
	: WalkSpeed(600.0f),
	WalkAcceleration(4000.0f),
	RunSpeed(1600.0f),
	RunAccelaration(16000.0f)
{

}


void UAS_Character::OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkAcceleration, ServerBaseValue);
}

void UAS_Character::OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunAccelaration, ServerBaseValue);
}
