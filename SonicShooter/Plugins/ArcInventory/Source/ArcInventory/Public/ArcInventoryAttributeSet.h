// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ArcInventoryAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcInventoryAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UArcInventoryAttributeSet(const class FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_InventorySize)
	FGameplayAttributeData InventorySize;

	UFUNCTION()
	void OnRep_InventorySize(FGameplayAttributeData OldInventorySize);
	
	

	static FGameplayAttribute InventorySizeAttribute();
};
