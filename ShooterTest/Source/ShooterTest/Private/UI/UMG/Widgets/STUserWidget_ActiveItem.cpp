// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_ActiveItem.h"

#include "UI/UMG/Widgets/STUserWidget_Crosshair.h"
#include "Components/TextBlock.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Components/ArcInventoryComponent_Active.h"



USTUserWidget_ActiveItem::USTUserWidget_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void USTUserWidget_ActiveItem::NativeOnInitialized()
{
	if (CrosshairWidget)
	{
		// Inject crosshair brush TODO: this is bad but i just want this to work
		CrosshairWidget->CrosshairBrush = CrosshairBrush;
	}


	// ActiveItem widgets get added to player screen as soon as the item is made active, so search for the active item's name at this moment
	if (ItemTextBlock && ItemTextBlock->GetText().IsEmpty())
	{
		// Search for the active item and use its name
		const APlayerController* PlayerController = GetOwningPlayer();
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

	Super::NativeOnInitialized();
}
