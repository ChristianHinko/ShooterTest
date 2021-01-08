// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcInvInputBinder.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;

/**
 * 
 */
UCLASS(EditInlineNew, Abstract, Blueprintable)
class ARCINVENTORY_API UArcInvInputBinder : public UObject
{
	GENERATED_BODY()
public:

	UArcInvInputBinder();

	UFUNCTION(BlueprintNativeEvent)
	int32 GetInputBinding(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityToGrant);
	virtual int32 GetInputBinding_Implementation(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayAbility> AbilityToGrant);

};
