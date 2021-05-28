// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AS_Stamina.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, MaxStamina, Params);

	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, Stamina, Params);
	Params.RepNotifyCondition = REPNOTIFY_Always;

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaDrain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaGain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaRegenPause, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Stamina::UAS_Stamina()
	: MaxStamina(5),
	StaminaDrain(1),
	StaminaGain(1),
	StaminaRegenPause(2)
{
	Stamina = FFloatPropertyWrapper(this, FName(TEXT("Stamina")));
	SetSoftAttributeDefaults();


}

void UAS_Stamina::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();


	Stamina = GetMaxStamina(); // TODO: this event is server only (after constructer call at least) but Stamina isn't replicated so the client won't this updated
}

void UAS_Stamina::Tick(float DeltaTime)
{
	if (bStaminaDraining)
	{
		timeSinceStaminaDrain = 0; // we are in draining mode, reset our time since drainage

		if (Stamina > 0)
		{
			// We are draining
			Stamina = Stamina - (GetStaminaDrain() * DeltaTime);

			if (Stamina < 0)
			{
				// We are fully drained
				Stamina = 0;
				OnStaminaFullyDrained.Broadcast();
				bStaminaDraining = false; // break out of draining mode so we can start to regen


				if (GetStaminaRegenPause() >= 0.5f) // if the pause is at least .5 seconds, we are safe to replicate (because the packet should probably take no longer than 500ms when replcating) TODO: check the player ping instead of hardcoded number
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

		if (timeSinceStaminaDrain >= GetStaminaRegenPause())
		{
			if (Stamina < GetMaxStamina())
			{
				// We are regening
				Stamina = Stamina + (GetStaminaGain() * DeltaTime);

				if (Stamina > GetMaxStamina())
				{
					// We are fully regened
					Stamina = GetMaxStamina();
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
void UAS_Stamina::SetShouldTick(bool newShouldTick)
{
	if (bShouldTick != newShouldTick)
	{
		bShouldTick = newShouldTick;
	}
}

bool UAS_Stamina::ShouldTick() const
{
	return bShouldTick;
}

void UAS_Stamina::SetStaminaDraining(bool newStaminaDraining)
{
	if (bStaminaDraining != newStaminaDraining)
	{
		bStaminaDraining = newStaminaDraining;

		SetShouldTick(true);
		GetOwningAbilitySystemComponent()->UpdateShouldTick();
	}
}



// OnReps:


void UAS_Stamina::OnRep_MaxStamina(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Stamina, MaxStamina, ServerBaseValue);
}

void UAS_Stamina::OnRep_StaminaDrain(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Stamina, StaminaDrain, ServerBaseValue);
}

void UAS_Stamina::OnRep_StaminaGain(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Stamina, StaminaGain, ServerBaseValue);
}

void UAS_Stamina::OnRep_StaminaRegenPause(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Stamina, StaminaRegenPause, ServerBaseValue);
}
