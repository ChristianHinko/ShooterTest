// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_Character.h"

#include "Net/UnrealNetwork.h"



void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, MyCharacterAttribute, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
}

UAS_Character::UAS_Character()
	: MyCharacterAttribute(125)
{

}


void UAS_Character::OnRep_MyCharacterAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, MyCharacterAttribute, ServerBaseValue);
}
