// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AS_PlayerState.h"

#include "Net/UnrealNetwork.h"



void UAS_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_PlayerState, ExampleAttribute, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
}

UAS_PlayerState::UAS_PlayerState()
	: ExampleAttribute(100)
{

}


void UAS_PlayerState::OnRep_ExampleAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_PlayerState, ExampleAttribute, ServerBaseValue);
}
