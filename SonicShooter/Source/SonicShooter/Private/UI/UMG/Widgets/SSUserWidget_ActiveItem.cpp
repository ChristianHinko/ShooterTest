// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/SSUserWidget_ActiveItem.h"

#include "UI/UMG/Widgets/SSUserWidget_Crosshair.h"
#include "Components/TextBlock.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Components/ArcInventoryComponent_Active.h"



USSUserWidget_ActiveItem::USSUserWidget_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void USSUserWidget_ActiveItem::NativeOnInitialized()
{
	if (CrosshairWidget)
	{
		// Inject crosshair brush TODO: this is bad but i just want this to work
		CrosshairWidget->CrosshairBrush = CrosshairBrush;
	}


	Super::NativeOnInitialized();
}

void USSUserWidget_ActiveItem::AddToScreen(ULocalPlayer* LocalPlayer, int32 ZOrder)
{
	// ActiveItem widgets get added to player screen as soon as the item is made active, so search for the active item's name at this moment
	if (ItemTextBlock && ItemTextBlock->GetText().IsEmpty())
	{
		// Search for the active item and use its name
		const APlayerController* PlayerController = LocalPlayer->GetPlayerController(LocalPlayer->GetWorld());
		if (IsValid(PlayerController))
		{
			UArcInventoryComponent_Active* InventoryComponent = Cast<UArcInventoryComponent_Active>(UArcItemBPFunctionLibrary::GetInventoryComponent(PlayerController->GetPawn(), true));
			if (IsValid(InventoryComponent))
			{
				const UArcItemStack* ActiveItemStack = InventoryComponent->GetActiveItemStack();
				if (IsValid(ActiveItemStack))
				{
					ItemTextBlock->SetText(ActiveItemStack->ItemName);
				}
			}
		}
	}

	Super::AddToScreen(LocalPlayer, ZOrder);
}
