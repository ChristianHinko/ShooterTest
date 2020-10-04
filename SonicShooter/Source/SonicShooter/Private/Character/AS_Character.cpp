// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AS_Character.h"

#include "Net/UnrealNetwork.h"
#include "GameplayAbilities\Public\GameplayEffectExtension.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplayTags\Classes\BlueprintGameplayTagLibrary.h"


void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME( UMyAttributeSet, MyAttribute);     <---Chances are this is how you would ordinarily do it,
	//however in the case of attributes this'll lead to confusing and annoying replication errors, usually involving client side ability prediction.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkSpeed, COND_None, REPNOTIFY_Always);	//    <-----This is how it is done properly for attributes.
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, WalkAcceleration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, RunAccelaration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, Health, COND_None, REPNOTIFY_Always);
	//	Damage and Healing not replicated since it's a 'meta' attribute

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, Stamina, COND_None, REPNOTIFY_Always);
	//	StaminaDrain and StaminaGain not replicated since it's a 'meta' attribute

}

//	These are default values BEFORE the default attribute values effect gets applied
UAS_Character::UAS_Character()
	: WalkSpeed(300.0f),
	WalkAcceleration(2000.0f),
	RunSpeed(800.0f),
	RunAccelaration(8000.0f),
	MaxHealth(100),
	Health(GetMaxHealth()),
	MaxStamina(5),
	Stamina(GetMaxStamina())
{
	TagOutOfStamina = FGameplayTag::RequestGameplayTag(FName("State.Character.OutOfStamina"));
	
	

}

bool UAS_Character::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);

	FGameplayAttribute AttributeToModify = Data.EvaluatedData.Attribute;
	




	if (AttributeToModify == GetDamageAttribute())
	{
		//Handle extra Attribute Modifications here (ie. armor buff, damage vulnerability)


	}

	if (AttributeToModify == GetHealingAttribute())
	{
		//Handle extra Attribute Modifications here (ie. less healing, extra healing)


	}

	if (AttributeToModify == GetStaminaDrainAttribute())
	{


	}

	if (AttributeToModify == GetStaminaGainAttribute())
	{


	}

	return true;
}
void UAS_Character::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayAttribute ModifiedAttribute = Data.EvaluatedData.Attribute;










	if (ModifiedAttribute == GetDamageAttribute())
	{
		const float damageToApply = Damage.GetCurrentValue();
		SetDamage(0.f);

		SetHealth(FMath::Clamp(GetHealth() - damageToApply, 0.f, GetMaxHealth()));

	}

	if (ModifiedAttribute == GetHealingAttribute())
	{
		const float healingToApply = Healing.GetCurrentValue();
		SetHealing(0.f);

		SetHealth(FMath::Clamp(GetHealth() + healingToApply, 0.f, GetMaxHealth()));

	}

	if (ModifiedAttribute == GetStaminaDrainAttribute())
	{
		const float staminaToDrain = StaminaDrain.GetCurrentValue();
		SetStaminaDrain(0.f);

		SetStamina(FMath::Clamp(GetStamina() - staminaToDrain, 0.f, GetMaxStamina()));

		UKismetSystemLibrary::PrintString(this, "Drained: " + FString::SanitizeFloat(staminaToDrain) + "Now at " + FString::SanitizeFloat(GetStamina()), true, false, FLinearColor::Red);
	}

	if (ModifiedAttribute == GetStaminaGainAttribute())
	{
		const float staminaToGain = StaminaGain.GetCurrentValue();
		SetStaminaGain(0.f);

		SetStamina(FMath::Clamp(GetStamina() + staminaToGain, 0.f, GetMaxStamina()));

		UKismetSystemLibrary::PrintString(this, "Gained: " + FString::SanitizeFloat(staminaToGain) + "Now at " + FString::SanitizeFloat(GetStamina()), true, false, FLinearColor::Green);
	}
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



void UAS_Character::OnRep_MaxHealth(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, MaxHealth, ServerBaseValue);
}
void UAS_Character::OnRep_Health(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, Health, ServerBaseValue);
}



void UAS_Character::OnRep_MaxStamina(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, MaxStamina, ServerBaseValue);
}
void UAS_Character::OnRep_Stamina(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, Stamina, ServerBaseValue);
}


