// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void USTAttributeSet_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Stamina, MaxStamina, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Stamina, StaminaDrain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Stamina, StaminaGain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USTAttributeSet_Stamina, StaminaRegenPause, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
USTAttributeSet_Stamina::USTAttributeSet_Stamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MaxStamina(5)
	, StaminaDrain(1)
	, StaminaGain(1)
	, StaminaRegenPause(2)
{
}




// OnReps

void USTAttributeSet_Stamina::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Stamina, MaxStamina, OldValue);
}

void USTAttributeSet_Stamina::OnRep_StaminaDrain(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Stamina, StaminaDrain, OldValue);
}

void USTAttributeSet_Stamina::OnRep_StaminaGain(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Stamina, StaminaGain, OldValue);
}

void USTAttributeSet_Stamina::OnRep_StaminaRegenPause(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USTAttributeSet_Stamina, StaminaRegenPause, OldValue);
}
