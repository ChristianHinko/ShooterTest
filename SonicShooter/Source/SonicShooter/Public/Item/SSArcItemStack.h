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

	// The pointer to the item's widget that is currently created for the player and added to the player's viewport. Would put this in the player's HUD class but that would be a mess (would need a TArray of widgets and a way of finding a specific one). This works better
	UPROPERTY()
		UUW_ActiveItem* ActiveItemWidget;
};
