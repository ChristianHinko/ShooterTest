// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcItemStack.h"

#include "SSArcItemStack.generated.h"


class UUW_ActiveItem;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API USSArcItemStack : public UArcItemStack
{
	GENERATED_BODY()
	
public:
	USSArcItemStack(const FObjectInitializer& ObjectInitializer);


	/**
	 * Our created Active Item Widget. Only valid while Item is equipped - Widget is destroyed on UnEquip.
	 * NOTE: Only valid on the Client and Listening Server.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "UI")
		UUW_ActiveItem* ActiveItemWidget;

};
