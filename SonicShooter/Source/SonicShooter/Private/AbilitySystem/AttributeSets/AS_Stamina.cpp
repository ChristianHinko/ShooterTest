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
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaDrain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaGain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Stamina, StaminaRegenPause, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Stamina::UAS_Stamina()
	: MaxStamina(5)
	, StaminaDrain(1)
	, StaminaGain(1)
	, StaminaRegenPause(2)
{

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
