// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AS_Actor.h"

#include "Net/UnrealNetwork.h"



void UAS_Actor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Actor, MyActorAttribute, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
}

UAS_Actor::UAS_Actor()
	: MyActorAttribute(75)
{

}


void UAS_Actor::OnRep_MyActorAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Actor, MyActorAttribute, ServerBaseValue);
}
