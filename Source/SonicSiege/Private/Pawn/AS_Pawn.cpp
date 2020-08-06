// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/AS_Pawn.h"

#include "Net/UnrealNetwork.h"



void UAS_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Pawn, MyPawnAttribute, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
}

UAS_Pawn::UAS_Pawn()
	: MyPawnAttribute(75)
{

}


void UAS_Pawn::OnRep_MyPawnAttribute(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Pawn, MyPawnAttribute, ServerBaseValue);
}
