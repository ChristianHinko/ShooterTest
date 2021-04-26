// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ArcInvInputBinder.h"

UArcInvInputBinder::UArcInvInputBinder()
	: Super()
{

}

int32 UArcInvInputBinder::GetInputBinding_Implementation(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityToGrant)
{
	return INDEX_NONE;
}
