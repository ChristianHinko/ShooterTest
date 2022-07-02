// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/STObject_Stamina.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"
#include "BlueprintFunctionLibraries/GCBlueprintFunctionLibrary_InterfaceHelpers.h"



void USTObject_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USTObject_Stamina, Stamina, Params);
}
bool USTObject_Stamina::IsSupportedForNetworking() const
{
	return true;
}
bool USTObject_Stamina::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

USTObject_Stamina::USTObject_Stamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

	, Stamina(this, TEXT("Stamina"), 0.f)

	, MaxStamina(0.f)
	, StaminaDrain(0.f)
	, StaminaGain(0.f)
	, StaminaRegenPause(0.f)
{

}

void USTObject_Stamina::Tick(float DeltaTime)
{
	if (bStaminaDraining)
	{
		TimeSinceStaminaDrain = 0; // we are in draining mode, reset our time since drainage

		if (Stamina > 0)
		{
			// We are draining
			Stamina = Stamina - (StaminaDrain * DeltaTime);

			if (Stamina < 0)
			{
				// We are fully drained
				Stamina = 0;
				OnStaminaFullyDrained.Broadcast();
				bStaminaDraining = false; // break out of draining mode so we can start to regen


				if (StaminaRegenPause >= 0.5f) // if the pause is at least .5 seconds, we are safe to replicate (because the packet should probably take no longer than 500ms when replcating) TODO: check the player ping instead of hardcoded number
				{
					Stamina.MarkNetDirty();
				}
			}
		}
		else
		{
			// We tried to drain stamina with no stamina left, break out of draining mode to regen
			bStaminaDraining = false;
		}
	}
	else
	{
		TimeSinceStaminaDrain += DeltaTime; // only accurate while ticking, because this won't be updated if not ticking

		if (TimeSinceStaminaDrain >= StaminaRegenPause)
		{
			if (Stamina < MaxStamina)
			{
				// We are regening
				Stamina = Stamina + (StaminaGain * DeltaTime);

				if (Stamina > MaxStamina)
				{
					// We are fully regened
					Stamina = MaxStamina;
					OnStaminaFullyGained.Broadcast();

					SetShouldTick(false); // at this point no stamina logic needs to be performed (we are at full stamina) so we are safe to stop ticking
				}
			}
			else
			{
				// We tried gaining stamina with full stamina, stop ticking
				SetShouldTick(false);
			}
		}
	}
}


void USTObject_Stamina::SetStaminaDraining(bool newStaminaDraining)
{
	if (bStaminaDraining != newStaminaDraining)
	{
		SetShouldTick(true);	// this will get hit if we start draining or start regening
	}

	bStaminaDraining = newStaminaDraining;
}

void USTObject_Stamina::SetMaxStamina(float NewMaxStamina)
{
	float OldMaxStamina = MaxStamina;
	MaxStamina = NewMaxStamina;

	if (Stamina < NewMaxStamina)		// If this results in our stamina needing an increasing adjustment
	{
		if (bShouldTick == false)
		{
			if (Stamina < OldMaxStamina)
			{
				SetShouldTick(true);	// start ticking again, so we can regen to our new MaxStamina
			}
			else
			{
				Stamina = NewMaxStamina;	// we already had max stamina so give them the free stamina to get the the new max stamina
			}
		}
	}
	else if (Stamina > NewMaxStamina)	// If this results in our stamina needing a decreasing adjustment
	{
		Stamina = NewMaxStamina;
	}
}

void USTObject_Stamina::SetShouldTick(bool newShouldTick)
{
	if (bShouldTick != newShouldTick)
	{
		bShouldTick = newShouldTick;
	}
}