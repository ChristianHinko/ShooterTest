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

	// Only valid on the client/listening server. This keeps track of the item's widget in memory (only valid while item is equipped). Widget is destroyed on unequip.
	UPROPERTY()
		UUW_ActiveItem* ActiveItemWidget;
};
