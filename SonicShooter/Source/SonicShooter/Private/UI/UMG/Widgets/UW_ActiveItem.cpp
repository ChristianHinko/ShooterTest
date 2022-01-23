// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UMG/Widgets/UW_ActiveItem.h"

#include "Item/UW_Crosshair.h"
#include "Components/TextBlock.h"



UUW_ActiveItem::UUW_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UUW_ActiveItem::NativeConstruct()
{
	Super::NativeConstruct();


	if (ItemTextBlock)
	{
		ItemTextBlock->Text = ActiveItemName;
	}

	if (CrosshairWidget)
	{
		// Inject crosshair brush TODO: this is bad but i just want this to work
		CrosshairWidget->CrosshairBrush = CrosshairBrush;
	}
}
