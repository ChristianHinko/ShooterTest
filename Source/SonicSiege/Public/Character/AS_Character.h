// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AS_Character.generated.h"



/**
 * This attribute set will be on every character that uses the ability system (using AbilitySystemCharacter)
 * add universal character attributes here.
 */
UCLASS()
class SONICSIEGE_API UAS_Character : public USSAttributeSet
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_Character();

	// Attributes
#pragma region Movement Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkSpeed, Category = "Attributes|Movement")
		FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Character, WalkSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WalkAcceleration, Category = "Attributes|Movement")
		FGameplayAttributeData WalkAcceleration;
	ATTRIBUTE_ACCESSORS(UAS_Character, WalkAcceleration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunSpeed, Category = "Attributes|Movement")
		FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UAS_Character, RunSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RunAccelaration, Category = "Attributes|Movement")
		FGameplayAttributeData RunAccelaration;
	ATTRIBUTE_ACCESSORS(UAS_Character, RunAccelaration)
#pragma endregion

#pragma region Health Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAS_Character, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes", meta = (HideFromModifiers))	// HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAS_Character, Health)


	//	'meta' attributes: ie. "What do we do with this incomming Damage or Healing?" Good solution in place of an ExecutionCalculation
	/** This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category = "Attributes", meta = (HideFromLevelInfos))	// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UAS_Character, Damage)

	/** This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Healing, Category = "Attributes", meta = (HideFromLevelInfos))	// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient
		FGameplayAttributeData Healing;
	ATTRIBUTE_ACCESSORS(UAS_Character, Healing)
#pragma endregion
	

protected:
	//	Handle applying any modifications to incomming effects (ie. subtracting incomming damage using a shield attribute)
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	//	Handle using 'meta' attributes for modifying 'persistant' attributes. Such as Damage modifying Health
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_WalkSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_WalkAcceleration(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunSpeed(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_RunAccelaration(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_Damage(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_Healing(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& ServerBaseValue);
};
