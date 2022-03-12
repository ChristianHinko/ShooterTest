// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "Net/UnrealNetwork.h"
#include "ArcItemStack.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "ArcInventory.h" // for Roy's Native Gameplay Tags

#include "UI/HUD_Shooter.h"
#include "Item/SSArcItemDefinition_Active.h"
#include "UI/UMG/Widgets/UW_ActiveItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Utilities/LogCategories.h"
#include "Item/SSArcItemStack.h"
#include "Item/Gun/ArcItemStack_Gun.h"
#include "Subobjects/O_Gun.h"



void USSArcInventoryComponent_Active::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.Condition = COND_OwnerOnly;
	Params.bIsPushBased = true;
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


	OnAttributeSetCreated.AddDynamic(this, &USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent);

	OnItemSlotChange.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemSlotChangeEvent);

	OnItemInactive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemInactiveEvent);
}

void USSArcInventoryComponent_Active::BeginPlay()
{
	// Make sure we have nothing stored when we begin play. We want to have a clean start to this active slot if we reset
	const int32 OldActiveItem = ActiveItemSlot;
	MakeItemInactive();
	ActiveItemSlot = OldActiveItem;

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {
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


void USSArcInventoryComponent_Active::OnAttributeSetCreatedEvent(UArcInventoryComponent_Equippable* Inventory, UAttributeSet* AttributeSet, UArcItemStack* AttributeSource)
{
	// Tells us to apply the default stats Effect
	bCreatedAttributeSets = true;
}

void USSArcInventoryComponent_Active::MakeItemActive(int32 NewActiveItemSlot)
{
	Super::MakeItemActive(NewActiveItemSlot);
	// Earliest point for the validity of UArcInventoryComponent_Active::ActiveItemSlot and hence GetActiveItemStack() can be used
	// NOTE: This is not the case for Roy's UArcInventoryComponent_Active::OnItemActive delegate (this delegate is not safe)


	UArcItemStack* ActiveItemStack = GetActiveItemStack();
	if (!IsValid(ActiveItemStack))
	{
		return;
	}


	// Check if we created any Attribute Sets
	if (bCreatedAttributeSets)
	{
		// Attribute Sets have been created! - so apply default stats Effect
		UAbilitySystemComponent* ASC = GetOwnerAbilitySystem();
		if (IsValid(ASC))
		{
			USSArcItemDefinition_Active* SSItemDefinition = Cast<USSArcItemDefinition_Active>(ActiveItemStack->GetItemDefinition().GetDefaultObject());
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






	// Reset our Gun's CurrentBulletSpread
	{
		UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
		if (IsValid(GunStack))
		{
			GunStack->GetGunSubobject()->ResetBulletSpread();
		}
	}


	// Add UIData widget
	const APawn* OwningPawn = GetTypedOuter<APawn>();
	if (IsValid(OwningPawn))
	{
		if (OwningPawn->IsLocallyControlled())
		{
			bool bSuccessfullyAdded = true;

			APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController());
			if (IsValid(OwningPC))
			{
				const USSArcUIData_ItemDefinition* UIData = Cast<USSArcUIData_ItemDefinition>(ActiveItemStack->GetUIData());
				if (IsValid(UIData))
				{
					AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD());
					if (IsValid(ShooterHUD))
					{
						USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ActiveItemStack);
						if (IsValid(SSArcItemStack))
						{
							UUW_ActiveItem* WidgetToAdd = SSArcItemStack->ActiveItemWidget;

							if (!IsValid(WidgetToAdd))
							{
								// No valid Widget! - For some reason the Widget wasn't created successfully in OnItemSlotChangeEvent()!
								UE_LOG(UISetup, Warning, TEXT("%s() New active Item Stack did not point to a valid item Widget when trying to add it to Viewport. Equipping the item maybe didn't successfully create the Widget so we have nothing. We will create the Widget now but something seams to have messed up at some point"), ANSI_TO_TCHAR(__FUNCTION__));
								
								// Create the Widget
								WidgetToAdd = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC));
								if (WidgetToAdd)
								{
									WidgetToAdd->ActiveItemName = ActiveItemStack->ItemName; // inject ItemName

									SSArcItemStack->ActiveItemWidget = WidgetToAdd;
								}
							}

							// Add the Widget to Viewport
							if (IsValid(WidgetToAdd))
							{
								WidgetToAdd->AddToPlayerScreen();
								ShooterHUD->CurrentActiveItemWidget = WidgetToAdd;
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
	int32 SizeChange = 0;

	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)
	{
		--SizeChange; // we don't want duplicates.... remove the item from the history buffer so we can make it a new recent
	}

	// Make item new recent
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);
	++SizeChange;

	if (ActiveItemHistory.Num() > MaxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1); // remove oldest stored item if we are passed the max buffer size
	}

}


void USSArcInventoryComponent_Active::OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (IsValid(ItemStack)) // if we are Equiping
	{
		const APawn* OwningPawn = GetTypedOuter<APawn>();
		if (IsValid(OwningPawn))
		{
			if (OwningPawn->IsLocallyControlled())
			{
				// We will create the item's Widget so we can add it when it later becomes "Active"
				USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack);
				if (IsValid(SSArcItemStack))
				{
					if (!IsValid(SSArcItemStack->ActiveItemWidget)) // only create a new Widget if it doesn't already exist
					{
						const USSArcUIData_ItemDefinition* UIData = Cast<USSArcUIData_ItemDefinition>(ItemStack->GetUIData());
						if (IsValid(UIData))
						{
							APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController());
							if (IsValid(OwningPC))
							{
								UUW_ActiveItem* Widget = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC));
								if (IsValid(Widget))
								{
									Widget->ActiveItemName = ItemStack->ItemName; // inject ItemName

									SSArcItemStack->ActiveItemWidget = Widget;
								}
							}
						}
					}
				}

			}
		}
	}
	else // if we are UnEquiping
	{
		USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(PreviousItemStack);
		if (IsValid(SSArcItemStack))
		{
			UUW_ActiveItem* WidgetToRemove = SSArcItemStack->ActiveItemWidget;
			if (IsValid(WidgetToRemove))
			{
				// We completely get rid of the widget since the inventory now longer has the item
				WidgetToRemove->RemoveFromParent();
				SSArcItemStack->ActiveItemWidget = nullptr;
			}
		}
	}

}

void USSArcInventoryComponent_Active::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Reset our Gun's CurrentBulletSpread
	{
		UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ItemStack);
		if (IsValid(GunStack))
		{
			GunStack->GetGunSubobject()->ResetBulletSpread();
		}
	}


	// Remove UIData widgets
	const APawn* OwningPawn = GetTypedOuter<APawn>();
	if (IsValid(OwningPawn))
	{
		if (OwningPawn->IsLocallyControlled())
		{
			const APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController());
			if (IsValid(OwningPC))
			{
				const USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack);
				if (IsValid(SSArcItemStack))
				{
					UUW_ActiveItem* WidgetToRemove = SSArcItemStack->ActiveItemWidget;
					if (IsValid(WidgetToRemove))
					{
						// Remove ActiveItemWidget from Viewport and clear the pointer from ShooterHUD
						WidgetToRemove->RemoveFromViewport();

						// And clear the pointer from the HUD
						AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD());
						if (IsValid(ShooterHUD))
						{
							ShooterHUD->CurrentActiveItemWidget = nullptr;
						}
					}
				}
			}

		}
	}

}
