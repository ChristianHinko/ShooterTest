// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState.h"

#include "Player/AS_PlayerState.h"



ASSPlayerState::ASSPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSAbilitySystemComponent>(AbilitySystemComponentName))
{
	SSAbilitySystemComponent = Cast<USSAbilitySystemComponent>(ASSAbilitySystemComponent);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSet = CreateDefaultSubobject<UAS_PlayerState>(TEXT("PlayerStateAttributeSet"));

	// Set PlayerState's NetUpdateFrequency to the same as the Pawn.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;
	// we're not sure if adaptive net update frequency is safe for PS or what a safe min update frequency would be for PS so we just set it to the max
	MinNetUpdateFrequency = NetUpdateFrequency;


}
