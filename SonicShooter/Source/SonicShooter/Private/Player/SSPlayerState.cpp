// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState.h"

#include "Subobjects/ActorComponents/GSActorComponent_PlayerStateExtension.h"
#include "Player/SSAttributeSet_PlayerState.h"



ASSPlayerState::ASSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GSPlayerStateExtensionComponent = CreateDefaultSubobject<UGSActorComponent_PlayerStateExtension>(TEXT("GSPlayerStateExtensionComponent"));

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically adds the AttributeSet with the AbilitySystemComponent
	PlayerAttributeSet = CreateDefaultSubobject<USSAttributeSet_PlayerState>(TEXT("PlayerStateAttributeSet"));
}
