// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_ActiveItem.h"

#include "UI/UMG/Widgets/STUserWidget_Crosshair.h"
#include "Components/TextBlock.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Modular/ArcInventoryComponent_Modular.h"
#include "Modular/ArcItemStackModular.h"
#include "Modular/Processors/ArcInventoryProcessor_Active.h"
#include "Modular/Fragments/ArcItemFragment_Text.h"



USTUserWidget_ActiveItem::USTUserWidget_ActiveItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}


// NOTE: This is bad right now because it's currently very non-intuitive. We get item specific data through GetActiveItemStack() because we know that this widget gets created when the item becomes active. So this logic is dependent on the idea that we create the widget when the item becomes active.
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
            UArcInventoryComponent_Modular* InventoryComponentModular = Cast<UArcInventoryComponent_Modular>(UArcItemBPFunctionLibrary::GetInventoryComponent(PlayerController->GetPawn(), true));
            if (IsValid(InventoryComponentModular))
            {
                const UArcInventoryProcessor_Active* InventoryProcessorActive = InventoryComponentModular->FindFirstProcessor<UArcInventoryProcessor_Active>();
                UArcItemStackModular* ActiveItemStack = InventoryProcessorActive->GetActiveItemStack();
                if (IsValid(ActiveItemStack))
                {
                    const UArcItemFragment_Text* TextItemFragment = ActiveItemStack->FindFirstFragment<UArcItemFragment_Text>();
                    if (IsValid(TextItemFragment))
                    {
                        ItemTextBlock->SetText(TextItemFragment->Text);
                        //ItemTextBlock->SetText(ActiveItemStack->ItemName);
                    }
                }
            }
        }
    }

    Super::NativeOnInitialized();
}
