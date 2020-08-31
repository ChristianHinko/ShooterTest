// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Health.generated.h"



//struct FGameplayEffectModCallbackData


/**
 * 
 */
UCLASS()
class SONICSIEGE_API UAS_Health : public USSAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor and default values
	UAS_Health();

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAS_Health, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes", meta = (HideFromModifiers))	// HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAS_Health, Health)


	//	'meta' attributes: ie. "What do we do with this incomming Damage or Healing?" Good solution in place of an ExecutionCalculation
	
	/** This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))	// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAS_Health, Damage)

	/** This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (HideFromLevelInfos))	// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient
		FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UAS_Health, Healing)

protected:
	//	Server only. Handle applying any modifications to incomming effects (ie. subtracting incomming damage using a shield attribute)
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	//	Server only. Handle using 'meta' attributes for modifying 'persistant' attributes. Such as Damage modifying Health
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& ServerBaseValue);
};
