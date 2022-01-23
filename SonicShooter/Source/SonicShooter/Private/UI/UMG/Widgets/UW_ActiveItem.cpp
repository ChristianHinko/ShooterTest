// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UMG/Widgets/UW_ActiveItem.h"

#include "UI/UMG/Widgets/UW_Ammo.h"



UUW_ActiveItem::UUW_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UUW_ActiveItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (AmmoWidget)
	{
		AmmoWidget->ActiveItemName = ActiveItemName;
	}
}
