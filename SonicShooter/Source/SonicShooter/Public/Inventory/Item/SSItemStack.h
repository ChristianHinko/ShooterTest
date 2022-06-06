// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"

#include "SSItemStack.generated.h"


class USSUserWidget_ActiveItem;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSItemStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	USSItemStack(const FObjectInitializer& ObjectInitializer);


	/**
	 * Our created Active Item Widget. Only valid while Item is equipped - Widget is destroyed on UnEquip.
	 * NOTE: Only valid on the Client and Listening Server.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UI")
		TObjectPtr<USSUserWidget_ActiveItem> ActiveItemWidget;

};
