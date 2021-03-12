// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Public/TickableAttributeSetInterface.h"

#include "AS_Character.generated.h"



DECLARE_MULTICAST_DELEGATE(FStaminaDelegate)


/**
 * This attribute set will be on every character that uses the ability system (using AbilitySystemCharacter)
 * add universal character attributes here.
 */
UCLASS()
class SONICSHOOTER_API UAS_Character : public USSAttributeSet, public ITickableAttributeSetInterface
{
	GENERATED_BODY()
	
public:
	// Constructor and default values
	UAS_Character();

#pragma region Gameplay Tags
	
#pragma endregion

	
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

#pragma region Stamina Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAS_Character, MaxStamina)

	UPROPERTY(BlueprintReadOnly/*, ReplicatedUsing = OnRep_Stamina*/, Category = "Attributes")
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAS_Character, Stamina)

	UFUNCTION(Unreliable, Client)
		void ClientReplicateStaminaState(float serverStamina, bool serverStaminaDraining);
	void ClientReplicateStaminaState_Implementation(float serverStamina, bool serverStaminaDraining);

	/** How fast your stamina drains while running */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaDrain, Category = "Attributes")
		FGameplayAttributeData StaminaDrain;
	ATTRIBUTE_ACCESSORS(UAS_Character, StaminaDrain)

	void SetStaminaDraining(bool newStaminaDraining);

	FStaminaDelegate OnStaminaFullyDrained;
	FStaminaDelegate OnStaminaFullyGained;

	/** How fast your stamina regenerates durring stamina regeneration */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaGain, Category = "Attributes")
		FGameplayAttributeData StaminaGain;
	ATTRIBUTE_ACCESSORS(UAS_Character, StaminaGain)

	/** The time it takes for your stamina to start regening again (the pause) */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenPause, Category = "Attributes")
		FGameplayAttributeData StaminaRegenPause;
	ATTRIBUTE_ACCESSORS(UAS_Character, StaminaRegenPause)
#pragma endregion
	

protected:
	//	Server only. Handle applying any modifications to incomming effects (ie. subtracting incomming damage using a shield attribute)
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	//	Server only. Handle using 'meta' attributes for modifying 'persistant' attributes. Such as Damage modifying Health
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTick() const override;
	virtual void SetShouldTick(bool newShouldTick);

	virtual void SetSoftAttributeDefaults() override;

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
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& ServerBaseValue);

	//UFUNCTION()
	//	virtual void OnRep_Stamina(const FGameplayAttributeData& ServerBaseValue);

	UFUNCTION()
		virtual void OnRep_StaminaDrain(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_StaminaGain(const FGameplayAttributeData& ServerBaseValue);
	UFUNCTION()
		virtual void OnRep_StaminaRegenPause(const FGameplayAttributeData& ServerBaseValue);

private:
	bool bShouldTick;

	bool bStaminaDraining;
	float timeSinceStaminaDrain;
};
