// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState.h"

#include "Player/AS_PlayerState.h"



ASSPlayerState::ASSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSet = CreateDefaultSubobject<UAS_PlayerState>(TEXT("PlayerStateAttributeSet"));
}
