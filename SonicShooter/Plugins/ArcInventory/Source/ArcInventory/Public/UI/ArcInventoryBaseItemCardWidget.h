// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArcInventoryBaseItemCardWidget.generated.h"

class UArcItemStack;

/**
 * 
 */
UCLASS(Abstract)
class ARCINVENTORY_API UArcInventoryBaseItemCardWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UArcInventoryBaseItemCardWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "ArcInventory|UI")
	virtual UArcItemStack* GetItemStack() const;

	UFUNCTION(BlueprintCallable, Category="ArcInventory|UI")
	virtual void SetItemStack(UArcItemStack* InItemStack);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnItemStackSet(UArcItemStack* NewItemStack);


protected:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="", BlueprintSetter=SetItemStack, BlueprintGetter=GetItemStack, Meta=(ExposeOnSpawn = true))
	UArcItemStack* ItemStack;
	
};
