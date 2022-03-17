// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_ActiveItem.h"

#include "UI/UMG/Widgets/UW_Crosshair.h"
#include "Components/TextBlock.h"



UUW_ActiveItem::UUW_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UUW_ActiveItem::NativeOnInitialized()
{
	if (CrosshairWidget)
	{
		// Inject crosshair brush TODO: this is bad but i just want this to work
		CrosshairWidget->CrosshairBrush = CrosshairBrush;
	}


	Super::NativeOnInitialized();
}

void UUW_ActiveItem::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	// Hacky way of allowing injection of ActiveItemName. Until this point, ItemTextBlock's text was
	// empty - so we update it right before adding to player screen
	if (ItemTextBlock)
	{
		ItemTextBlock->SetText(ActiveItemName);
	}


	Super::AddToScreen(LocalPlayer, ZOrder);
}
