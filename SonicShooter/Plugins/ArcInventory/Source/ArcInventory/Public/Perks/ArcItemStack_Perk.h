// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"
#include "ArcItemStack_Perk.generated.h"

/**
 * 
 */
UCLASS()
class ARCINVENTORY_API UArcItemStack_Perk : public UArcItemStack
{
	GENERATED_BODY()
public:
	UArcItemStack_Perk(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perk Settings", Replicated)
	TArray<FArcPerkModifierData> Modifiers;
	   
	virtual bool CanAttachTo_Implementation(UArcItemStack* OtherStack) override;
};
