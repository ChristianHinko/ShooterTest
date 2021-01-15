// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/Definitions/ArcItemDefinition_Equipment.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemDefinition_Active.generated.h"

/**
 * 
 */
UCLASS(abstract)
class ARCINVENTORY_API UArcItemDefinition_Active : public UArcItemDefinition_Equipment
{
	GENERATED_BODY()
public:
	UArcItemDefinition_Active();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Display")
	USkeletalMesh* HeldItemMesh;

	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Active Item")
	//TMap<FGameplayTag, class UArcAnimationSet*> ActiveAnimationSets;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Active Item")
	FArcItemDefinition_AbilityInfo ActiveItemAbilityInfo;

	UFUNCTION(BlueprintNativeEvent)
	void SetHeldItemMesh(UArcItemStack* ItemStack, AActor* ActorToSetup);
	virtual void SetHeldItemMesh_Implementation(UArcItemStack* ItemStack, AActor* ActorToSetup);
	
};
