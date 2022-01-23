// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "Net/UnrealNetwork.h"
#include "ArcItemStack.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Input/ArcInvInputBinder.h"
#include "AbilitySystemGlobals.h"

#include "UI/HUD_Shooter.h"
#include "Item/SSArcItemDefinition_Active.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Item/UW_Crosshair.h"
#include "UI/UMG/Widgets/UW_Ammo.h"
#include "Utilities/LogCategories.h"
#include "Item/SSArcItemStack.h"
#include "ArcInventory.h" // for Roy's Native Gameplay Tags

#include "AbilitySystem/ASSAttributeSet.h"



void USSArcInventoryComponent_Active::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.bIsPushBased = true;
	Params.Condition = COND_OwnerOnly;
	DOREPLIFETIME_WITH_PARAMS_FAST(USSArcInventoryComponent_Active, ActiveItemHistory, Params);
}


USSArcInventoryComponent_Active::USSArcInventoryComponent_Active(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxItemHistoryBufferSize = 30;
	bUseOnEquipItemSwappingThingRoyMade = false;
	
	// The work below can be done in the constructor since we are dealing with CustomInventorySlots which is filled out in the editor 
	// Figures out what active item to start on (first CustomInventorySlot with the tag "Inventory.Slot.Active"). We know there should be a valid item in this slot even though it may not be replicated yet so this convieniently sets the StartingActiveItemSlot to the first active item slot regardless of wheather we have a valid item yet or not, however, this may limit certain gameplay mechanics related to runtime inventory startup editing or something since CustomInventorySlots are desined to be edited in editor. But who knows there may be a way to fix that
	const FGameplayTag& ActiveSlotTag = FArcInvActiveSlotTag;
	for (int32 i = 0; i < CustomInventorySlots.Num(); ++i)
	{
		if (CustomInventorySlots[i].Tags.HasTag(ActiveSlotTag))
		{
			StartingActiveItemSlot = i;
		}
	}

}

void USSArcInventoryComponent_Active::InitializeComponent()
{
	Super::InitializeComponent();


	OnItemSlotChange.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemSlotChangeEvent);

	OnItemActive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemActiveEvent);
	OnItemInactive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemInactiveEvent);

	OnAttributeSetCreated.AddDynamic(this, &USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent);
}

void USSArcInventoryComponent_Active::BeginPlay()
{
	// Make sure we have nothing stored when we begin play. We want to have a clean start to this active slot if we reset
	const int32 OldActiveItem = ActiveItemSlot;
	MakeItemInactive();
	ActiveItemSlot = OldActiveItem;

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			SwapActiveItems(StartingActiveItemSlot);


			//////////////////////// We aren't going to do this stuff from the super since it just makes things dufficult ////////////////////////
			////Check to see if we have an active item in our first slot and set it to that to start with  
			//if (PendingItemSlot != INDEX_NONE)
			//{
			//	this->SwitchToPendingItemSlot();
			//}
			////Sometimes, on the client, we get the initial ActiveItemSlot before we've begun play
			////In that case, PendingItemSlot would be none, and we have a valid ActiveItemSlot that hasn't been made active yet
			////So we'll do it here.
			//else if (ActiveItemSlot != INDEX_NONE && GetOwnerRole() != ROLE_Authority)
			//{
			//	this->MakeItemActive(ActiveItemSlot);
			//}
		});


	Super::Super::BeginPlay();
}

bool USSArcInventoryComponent_Active::IsActiveItemSlotIndexValid(int32 InActiveItemSlot)
{
	if (InActiveItemSlot < 0)
	{
		return false;
	}
	if (InActiveItemSlot >= CachedActiveItemSlots.Num())
	{
		return false;
	}

	return true;
}

void USSArcInventoryComponent_Active::OnItemEquipped(class UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	// NOTE: This Super call was not here for some reason TODO: review this and try to add this Super call in (but maybe this was intended idk)
	//Super::OnItemEquipped(Inventory, ItemSlotRef, ItemStack, PreviousItemStack);


	if (bUseOnEquipItemSwappingThingRoyMade)
	{
		//If we are an active item slot, make it active if we don't already have an active item		
		if (ActiveItemSlot == INDEX_NONE && IsActiveItemSlot(ItemSlotRef) && IsValid(ItemStack))
		{

			const int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
			PendingItemSlot = ItemSlotIndex;

			//If we've begun play, send the gameplay event now.  Otherwise we'll get it in BeginPlay
			if (HasBegunPlay())
			{
				SwitchToPendingItemSlot();
			}
		}

		//If we are unequipping an item and it's the currently active item, either go to the next available active item or go to neutral
		if (!IsValid(ItemStack))
		{
			const int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
			if (ItemSlotIndex == ActiveItemSlot)
			{
				PendingItemSlot = GetNextValidActiveItemSlot();
				MakeItemInactive_Internal(ItemSlotRef, PreviousItemStack);
				SwitchToPendingItemSlot();
			}
		}
	}

}

bool USSArcInventoryComponent_Active::MakeItemActive_Internal(const FArcInventoryItemSlotReference& ItemSlot, UArcItemStack* ItemStack)
{
	bool bSuccess = Super::MakeItemActive_Internal(ItemSlot, ItemStack);


	if (bSuccess)
	{
		AddToActiveItemHistory(ItemSlot);
	}


	return bSuccess;
}

void USSArcInventoryComponent_Active::AddToActiveItemHistory(const FArcInventoryItemSlotReference& NewActiveItemSlotReference)
{
	int32 sizeChange = 0;


	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)		// we don't want duplicates.... remove the item from the history buffer so we can make it a new recent
	{
		--sizeChange;
	}
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);						// make item new recent
	++sizeChange;

	if (ActiveItemHistory.Num() > MaxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1);						// remove oldest stored item if we are passed the max buffer size
	}


}

bool USSArcInventoryComponent_Active::ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource)
{
	Super::ApplyAbilityInfo_Internal(AbilityInfo, StoreInto, AbilitySource);


	// Check if we created any Attribute Sets
	if (bCreatedAttributeSets)
	{
		// Attribute Sets have been created! - so apply default stats Effect
		UAbilitySystemComponent* ASC = GetOwnerAbilitySystem();
		if (IsValid(ASC))
		{
			USSArcItemDefinition_Active* SSItemDefinition = Cast<USSArcItemDefinition_Active>(AbilitySource->GetItemDefinition().GetDefaultObject());
			if (IsValid(SSItemDefinition))
			{
				// Apply the default stats Effect
				FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
				EffectContextHandle.AddInstigator(GetOwner(), GetOwner());
				EffectContextHandle.AddSourceObject(GetOwner());

				FGameplayEffectSpecHandle NewEffectSpecHandle = ASC->MakeOutgoingSpec(SSItemDefinition->InitializationEffectTSub, 1/*GetLevel()*/, EffectContextHandle);
				if (NewEffectSpecHandle.IsValid())
				{
					ASC->ApplyGameplayEffectSpecToSelf(*NewEffectSpecHandle.Data.Get());
				}
				else
				{
					UE_LOG(LogArcInventorySetup, Warning, TEXT("%s() Tried to apply the InitializationEffectTSub but failed. Maybe check if you filled out your USSArcItemDefinition_Active::InitializationEffectTSub correctly in Blueprint"), ANSI_TO_TCHAR(__FUNCTION__));
				}
			}
		}

	}

	bCreatedAttributeSets = false;




	return true;
}


void USSArcInventoryComponent_Active::OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	// Untested since we are waiting on these problems to be resolved for the next ArcInventory update
	if (IsValid(ItemStack))		// if we are equiping
	{
		// We will create the item's widget so we can add it when it later becomes "Active"
		if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
		{
			if (!IsValid(SSArcItemStack->ActiveItemWidget))		// only create a new widget if it doesn't already exist
			{
				if (USSArcUIData_ItemDefinition* ItemUIData = Cast<USSArcUIData_ItemDefinition>(ItemStack->GetUIData()))
				{
					if (APawn* OwningPawn = GetTypedOuter<APawn>())
					{
						if (OwningPawn->IsLocallyControlled())
						{
							if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
							{
								if (UUW_ActiveItem* WidgetToCreate = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, ItemUIData->ActiveItemWidgetTSub, OwningPC)))
								{
									SSArcItemStack->ActiveItemWidget = WidgetToCreate;
								}
							}
						}
					}
				}
			}
		}
	}
	else						// if we are UnEquiping
	{
		// We completely get rid of the widget since the inventory now longer has the item
		if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(PreviousItemStack))
		{
			UUW_ActiveItem* WidgetToRemove = SSArcItemStack->ActiveItemWidget;
			if (WidgetToRemove)
			{
				WidgetToRemove->RemoveFromParent();
			}
		}
	}
}

void USSArcInventoryComponent_Active::OnItemActiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Add UIData widget
	bool bSuccessfullyAdded = true;
	if (ItemStack)
	{
		if (const APawn* OwningPawn = GetTypedOuter<APawn>())
		{
			if (OwningPawn->IsLocallyControlled())
			{
				if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
				{
					if (USSArcUIData_ItemDefinition* ItemUIData = Cast<USSArcUIData_ItemDefinition>(ItemStack->GetUIData()))
					{
						if (AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
						{
							if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
							{
								UUW_ActiveItem* WidgetToAdd = nullptr;			// This ptr represents the widget that will be added to the screen (whether it's already created or not)
								if (SSArcItemStack->ActiveItemWidget == nullptr)	// If for some reason the widget wasn't created successfully on item equip
								{
									UE_LOG(UISetup, Warning, TEXT("%s() New active item stack did not point to a valid item widget when trying to add it to viewport. Equipping the item maybe didn't successfully create the widget so we have nothing. We will create the widget now but something seams to have messed up at some point"), ANSI_TO_TCHAR(__FUNCTION__));
									// Create the widget and add to viewport
									WidgetToAdd = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, ItemUIData->ActiveItemWidgetTSub, OwningPC));
									if (WidgetToAdd)
									{
										SSArcItemStack->ActiveItemWidget = WidgetToAdd;
										ShooterHUD->CurrentActiveItemWidget = WidgetToAdd;
										WidgetToAdd->AddToViewport();
									}
								}
								else												// The widget from USSArcItemStack was valid as expected (it was created on item equip), so we will add it to viewport
								{
									WidgetToAdd = SSArcItemStack->ActiveItemWidget;
									if (WidgetToAdd)
									{
										WidgetToAdd->AddToViewport();
										ShooterHUD->CurrentActiveItemWidget = WidgetToAdd;

									}
								}
								


								// COMMENTED OUT CODE FOR NOW SINCE WE MAY USE A SIMILAR METHOD LATER FOR INJECTING IN DATA ABOUT THE ITEM FOR THE ACTIVE ITEM WIDGET
								//	With this widget we want to inject the new weapon's name into the widget since the widget has no way of getting the new item stack since this event is too early for that
								/*UUserWidget* NewAmmoWidget = UWidgetBlueprintLibrary::Create(this, ItemUIData->AmmoWidgetTSub, OwningPC);
								if (UUW_Ammo* NewAmmoWidgetCasted = Cast<UUW_Ammo>(NewAmmoWidget))
								{
									NewAmmoWidgetCasted->ActiveItemName = ItemStack->ItemName;
								}
								else
								{
									UE_LOG(LogUI, Fatal, TEXT("%s(): When trying to inject the new active item name into UUW_Ammo on create, we couldn't, because the cast from UUserWidget to UUW_Ammo failed"), ANSI_TO_TCHAR(__FUNCTION__));
								}
								ShooterHUD->AmmoWidget = NewAmmoWidget;
								if (ShooterHUD->AmmoWidget)
								{
									ShooterHUD->AmmoWidget->AddToViewport();
								}*/
							}
						}
					}
				}
			}
		}
	}

	if (bSuccessfullyAdded == false)
	{
		UE_LOG(UISetup, Warning, TEXT("%s() Item's widget was not successfully displayed on item active (a cast must have failed in the process)"), ANSI_TO_TCHAR(__FUNCTION__));
	}
}

void USSArcInventoryComponent_Active::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Remove UIData widgets
	if (const APawn* OwningPawn = GetTypedOuter<APawn>())
	{
		if (OwningPawn->IsLocallyControlled())
		{
			if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
			{
				if (AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
				{
					if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
					{
						UUW_ActiveItem* WidgetToRemove = SSArcItemStack->ActiveItemWidget;
						if (WidgetToRemove)
						{
							WidgetToRemove->RemoveFromViewport();
							ShooterHUD->CurrentActiveItemWidget = nullptr; // we set this pointer to null since at this point it's not visible to the Player (indicating the Item is no longer active)
						}
					}
				}
			}
		}
	}
}


void USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent(UArcInventoryComponent_Equippable* Inventory, UAttributeSet* AttributeSet, UArcItemStack* AttributeSource)
{
	bCreatedAttributeSets = true;
}
