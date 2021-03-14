// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/AS_Stamina.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/KismetSystemLibrary.h"
//#include "Engine/NetDriver.h"
//#include "Net/RepLayout.h"



void UAS_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Stamina, MaxStamina, COND_None, REPNOTIFY_Always);

	//DOREPLIFETIME_CONDITION_NOTIFY(UAS_Stamina, Stamina, COND_Custom, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Stamina, StaminaDrain, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Stamina, StaminaGain, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Stamina, StaminaRegenPause, COND_None, REPNOTIFY_Always);
}
//void UAS_Stamina::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) // this is only for AActors and UActorComponents, we will have to do something tricky instead of this
//{
//	Super::PreReplication(ChangedPropertyTracker);
//
//
//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Stamina, Stamina, true);
//}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Stamina::UAS_Stamina()
	: MaxStamina(5),
	StaminaDrain(1),
	StaminaGain(1),
	StaminaRegenPause(2)
{
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

		if (GetStamina() > 0)
		{
			// We are draining
			SetStamina(GetStamina() - (GetStaminaDrain() * DeltaTime));

			if (GetStamina() < 0)
			{
				// We are fully drained
				SetStamina(0);
				OnStaminaFullyDrained.Broadcast();
				bStaminaDraining = false; // break out of draining mode so we can start to regen
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
			if (GetStamina() < GetMaxStamina())
			{
				// We are regening
				SetStamina(GetStamina() + (GetStaminaGain() * DeltaTime));

				if (GetStamina() > GetMaxStamina())
				{
					// We are fully regened
					SetStamina(GetMaxStamina());
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


		//UNetDriver* NetDriver = GetWorld()->GetNetDriver();
		//IRepChangedPropertyTracker& ChangedPropertyTracker = *(NetDriver->FindOrCreateRepChangedPropertyTracker(this).Get());

		//if (bShouldTick == true)
		//{
		//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Stamina, Stamina, false);
		//}
		//else
		//{
		//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Stamina, Stamina, true);
		//}
	}

	// Actually semi-replicating stamina (or replicating it at all) is a really bad idea because of how transient it is

	//if (GetOwningActor()->GetLocalRole() == ROLE_Authority)
	//{
	//	ClientReplicateStaminaState(GetStamina(), bStaminaDraining);
	//}
}

bool UAS_Stamina::ShouldTick() const
{
	return bShouldTick;
}

void UAS_Stamina::ClientReplicateStaminaState_Implementation(float serverStamina, bool serverStaminaDraining)
{
	SetStamina(serverStamina);
	SetStaminaDraining(serverStaminaDraining);

	UE_LOG(LogTemp, Log, TEXT("client recieved server stamina state"));
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

//void UAS_Stamina::OnRep_Stamina(const FGameplayAttributeData& ServerBaseValue)
//{
//	UKismetSystemLibrary::PrintString(this, "OnRep_Stamina", true, false);
//	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Stamina, Stamina, ServerBaseValue);
//}

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
