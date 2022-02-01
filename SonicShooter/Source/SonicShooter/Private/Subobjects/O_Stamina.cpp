// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Stamina.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "BlueprintFunctionLibraries/BFL_InterfaceHelpers.h"


void UO_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_Stamina, Stamina, Params);
}

UO_Stamina::UO_Stamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnStaminaChange(MakeShared<FFloatValueChange>())
	, Stamina(0.f, this, FName("Stamina"), OnStaminaChange)
{

}

void UO_Stamina::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld() == nullptr || GetWorld()->IsGameWorld() == false)
	{
		return;
	}
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}

	// Safe "BeginPlay" logic here
	if (IAbilitySystemInterface* AbilitySystemInterface = UBFL_InterfaceHelpers::GetInterfaceTypedOuter<IAbilitySystemInterface, UAbilitySystemInterface>(this))
	{
		OwnerASC = AbilitySystemInterface->GetAbilitySystemComponent();
		if (IsValid(OwnerASC))
		{
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetMaxStaminaAttribute()).AddUObject(this, &UO_Stamina::OnMaxStaminaAttributeChange);
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaDrainAttribute()).AddUObject(this, &UO_Stamina::OnStaminaDrainAttributeChange);;
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaGainAttribute()).AddUObject(this, &UO_Stamina::OnStaminaGainAttributeChange);;
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaRegenPauseAttribute()).AddUObject(this, &UO_Stamina::OnStaminaRegenPauseAttributeChange);;
		}
	}
}

bool UO_Stamina::IsTickable() const
{
	return bShouldTick;
}
void UO_Stamina::Tick(float DeltaTime)
{
	if (bStaminaDraining)
	{
		timeSinceStaminaDrain = 0; // we are in draining mode, reset our time since drainage

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
		timeSinceStaminaDrain += DeltaTime; // only accurate while ticking, because this won't be updated if not ticking

		if (timeSinceStaminaDrain >= StaminaRegenPause)
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


void UO_Stamina::SetStaminaDraining(bool newStaminaDraining)
{
	if (bStaminaDraining != newStaminaDraining)
	{
		bStaminaDraining = newStaminaDraining;

		SetShouldTick(true);
		OwnerASC->UpdateShouldTick();
	}
}

void UO_Stamina::SetShouldTick(bool newShouldTick)
{
	if (bShouldTick != newShouldTick)
	{
		bShouldTick = newShouldTick;
	}
}


