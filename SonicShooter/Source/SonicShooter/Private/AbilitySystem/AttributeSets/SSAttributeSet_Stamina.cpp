// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void USSAttributeSet_Stamina::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Stamina, MaxStamina, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Stamina, StaminaDrain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Stamina, StaminaGain, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(USSAttributeSet_Stamina, StaminaRegenPause, Params);
}

//	These are default values BEFORE the default attribute values effect gets applied
USSAttributeSet_Stamina::USSAttributeSet_Stamina(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MaxStamina(5)
	, StaminaDrain(1)
	, StaminaGain(1)
	, StaminaRegenPause(2)
{
}




// OnReps

void USSAttributeSet_Stamina::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Stamina, MaxStamina, OldValue);
}

void USSAttributeSet_Stamina::OnRep_StaminaDrain(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Stamina, StaminaDrain, OldValue);
}

void USSAttributeSet_Stamina::OnRep_StaminaGain(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Stamina, StaminaGain, OldValue);
}

void USSAttributeSet_Stamina::OnRep_StaminaRegenPause(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USSAttributeSet_Stamina, StaminaRegenPause, OldValue);
}
