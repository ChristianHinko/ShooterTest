// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/ASSGameplayAbility.h"

#include "STGameplayAbility_CharacterJumpStatic.generated.h"

// THIS ABILITY IS WAYYYYYY OUTDATED!!!!!!!!!!!!!!!!
// WE HAVE NOT IMPLEMENTED THE NEW WAY OF DOING MOVEMENT ABILITIES FOR THIS STATIC VERISON OF JUMP!!!!
// IF YOU WANT TO USE THIS FOLLOW THE WAY THE STANDARD STGameplayAbility_CharacterJump DOES IT!!!!!!!!!
// WE JUST HAVENT FIXED THIS STATIC VERSION BECAUSE WE AREN'T USING IT!!!!!!!

/**
 * This serves as a good demonstration as to how you should go about making Non-Instanced abilities
 *
 * Non-Instanced Abilities must not change member variables or bind to Delegates during its execution of the Ability.
 * The Ability also cannot replicate variables or handle RPCs. Non-Instanced should be used only for Abilities that require no internal variable storage.
 *
 * Stuff were still not sure of yet:
 *		- We sorta made this from Epic's and Dan's Non-Instanced jump ability and added our own spin to it. Something to be aware of is in Dan's project the jumping got corrections for some reason when
 *			shooting the machine gun or the shot gun but not with the rocket launcher. Pretty sure it's just something weird with his project but be on the lookout to make sure nothing weird happens.
 *		- It seams like EndAbility doesn't need to be called in order to fire it again and again. Thats weird. Just call it on client and server anyways as always because thats what your supposed to do.
 *		- Another thing thats weird it that for Non-Instanced abilities, EGameplayAbilityActivationMode inside ActivationInfo is set to Confirmed on both the client and server, even thought Confirmed means your on the client.
 */
UCLASS()
class SHOOTERTEST_API USTGameplayAbility_CharacterJumpStatic : public UASSGameplayAbility
{
	GENERATED_BODY()

public:
	USTGameplayAbility_CharacterJumpStatic(const FObjectInitializer& ObjectInitializer);

protected:
	//  BEGIN UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void ASSEndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//  END UGameplayAbility Interface
};

