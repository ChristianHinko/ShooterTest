// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_Character.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"

#include "Kismet/KismetSystemLibrary.h"
//#include "Engine/NetDriver.h"
//#include "Net/RepLayout.h"



void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkSpeed, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkAcceleration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunAccelaration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, MaxStamina, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, Stamina, COND_Custom, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, StaminaDrain, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, StaminaGain, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, StaminaRegenPause, COND_None, REPNOTIFY_Always);
}
//void UAS_Character::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) // this is only for AActors and UActorComponents, we will have to do something tricky instead of this
//{
//	Super::PreReplication(ChangedPropertyTracker);
//
//
//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Character, Stamina, true);
//}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Character::UAS_Character()
	: WalkSpeed(300.f),
	WalkAcceleration(2048.f),
	RunSpeed(600.f),
	RunAccelaration(4096.f),
	MaxStamina(5),
	StaminaDrain(1),
	StaminaGain(1),
	StaminaRegenPause(2)
{
	SetSoftAttributeDefaults();
	

}

void UAS_Character::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();


	Stamina = GetMaxStamina(); // TODO: this event is server only (after constructer call at least) but Stamina isn't replicated so the client won't this updated
}

void UAS_Character::Tick(float DeltaTime)
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
void UAS_Character::SetShouldTick(bool newShouldTick)
{
	if (bShouldTick != newShouldTick)
	{
		bShouldTick = newShouldTick;


		//UNetDriver* NetDriver = GetWorld()->GetNetDriver();
		//IRepChangedPropertyTracker& ChangedPropertyTracker = *(NetDriver->FindOrCreateRepChangedPropertyTracker(this).Get());

		//if (bShouldTick == true)
		//{
		//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Character, Stamina, false);
		//}
		//else
		//{
		//	DOREPLIFETIME_ACTIVE_OVERRIDE(UAS_Character, Stamina, true);
		//}
	}

	// Actually semi-replicating stamina (or replicating it at all) is a really bad idea because of how transient it is
	
	//if (GetOwningActor()->GetLocalRole() == ROLE_Authority)
	//{
	//	ClientReplicateStaminaState(GetStamina(), bStaminaDraining);
	//}
}

bool UAS_Character::ShouldTick() const
{
	return bShouldTick;
}

void UAS_Character::ClientReplicateStaminaState_Implementation(float serverStamina, bool serverStaminaDraining)
{
	SetStamina(serverStamina);
	SetStaminaDraining(serverStaminaDraining);

	UE_LOG(LogTemp, Log, TEXT("client recieved server stamina state"));
}

void UAS_Character::SetStaminaDraining(bool newStaminaDraining)
{
	if (bStaminaDraining != newStaminaDraining)
	{
		bStaminaDraining = newStaminaDraining;

		SetShouldTick(true);
		GetOwningAbilitySystemComponent()->UpdateShouldTick();
	}
}

bool UAS_Character::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	const FGameplayAttribute AttributeToModify = Data.EvaluatedData.Attribute;
	

	return true;
}
void UAS_Character::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;



}



void UAS_Character::OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, WalkAcceleration, ServerBaseValue);
}

void UAS_Character::OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunSpeed, ServerBaseValue);
}

void UAS_Character::OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, RunAccelaration, ServerBaseValue);
}





void UAS_Character::OnRep_MaxStamina(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, MaxStamina, ServerBaseValue);
}

//void UAS_Character::OnRep_Stamina(const FGameplayAttributeData& ServerBaseValue)
//{
//	UKismetSystemLibrary::PrintString(this, "OnRep_Stamina", true, false);
//	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, Stamina, ServerBaseValue);
//}

void UAS_Character::OnRep_StaminaDrain(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, StaminaDrain, ServerBaseValue);
}

void UAS_Character::OnRep_StaminaGain(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, StaminaGain, ServerBaseValue);
}

void UAS_Character::OnRep_StaminaRegenPause(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, StaminaRegenPause, ServerBaseValue);
}



