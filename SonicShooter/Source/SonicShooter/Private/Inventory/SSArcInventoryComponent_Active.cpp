// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSArcInventoryComponent_Active.h"

#include "Net/UnrealNetwork.h"
#include "ArcItemStack.h"
#include "Item/Definitions/ArcItemDefinition_Active.h"
#include "AbilitySystem/SSAbilitySystemComponent.h"
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
	maxItemHistoryBufferSize = 30;
	bUseOnEquipItemSwappingThingRoyMade = false;

	// The work below can be done in the constructor since we are dealing with CustomInventorySlots which is filled out in the editor 
	// Figures out what active item to start on (first CustomInventorySlot with the tag "Inventory.Slot.Active"). We know there should be a valid item in this slot even though it may not be replicated yet so this convieniently sets the startingActiveItemSlot to the first active item slot regardless of wheather we have a valid item yet or not, however, this may limit certain gameplay mechanics related to runtime inventory startup editing or something since CustomInventorySlots are desined to be edited in editor. But who knows there may be a way to fix that
	FGameplayTag ActiveSlotTag = GetDefault<UArcInventoryDeveloperSettings>()->ActiveItemSlotTag;
	for (int32 i = 0; i < CustomInventorySlots.Num(); i++)
	{
		if (CustomInventorySlots[i].Tags.HasTag(ActiveSlotTag))
		{
			startingActiveItemSlot = i;
		}
	}
}

void USSArcInventoryComponent_Active::InitializeComponent()
{
	Super::InitializeComponent();

	OnItemSlotChange.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemSlotChangeEvent);

	OnItemActive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemActiveEvent);
	OnItemInactive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemInactiveEvent);
}

void USSArcInventoryComponent_Active::BeginPlay()
{
	//Make sure we have nothing stored when we begin play.  We want to have a clean start to this active slot if we reset
	int32 OldActiveItem = ActiveItemSlot;
	MakeItemInactive();
	ActiveItemSlot = OldActiveItem;

	GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			SwapActiveItems(startingActiveItemSlot);


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
	if (bUseOnEquipItemSwappingThingRoyMade)
	{
		//If we are an active item slot, make it active if we don't already have an active item		
		if (ActiveItemSlot == INDEX_NONE && IsActiveItemSlot(ItemSlotRef) && IsValid(ItemStack))
		{

			int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
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
			int32 ItemSlotIndex = GetActiveItemIndexBySlotRef(ItemSlotRef);
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

	if (ActiveItemHistory.RemoveSingle(NewActiveItemSlotReference) == 1)		// We don't want duplicates.... remove the item from the history buffer so we can make it a new recent
	{
		sizeChange--;
	}
	ActiveItemHistory.Insert(NewActiveItemSlotReference, 0);						// Make item new recent
	++sizeChange;



	if (ActiveItemHistory.Num() > maxItemHistoryBufferSize)
	{
		ActiveItemHistory.RemoveAt(ActiveItemHistory.Num() - 1);						// Remove oldest stored item if we are passed the max buffer size
	}



}

bool USSArcInventoryComponent_Active::ApplyAbilityInfo_Internal(const FArcItemDefinition_AbilityInfo& AbilityInfo, FArcEquippedItemInfo& StoreInto, UArcItemStack* AbilitySource)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		//Setup the Item Info, duplicating attribute sets if we have to
		for (auto AttributeSetClass : AbilityInfo.AttributeSetsToAdd)
		{
			//Find an attribute set with the same key
			UAttributeSet** ContainedAttributeSet = StoreInto.InstancedAttributeSets.FindByPredicate([=](UAttributeSet* Key) {
				return Key->GetClass() == AttributeSetClass.Get();
				});
			if (ContainedAttributeSet != nullptr)	 //If it exists, we've got it!
			{
				continue;
			}



			//Otherwise, create a new one
			UAttributeSet* NewAttributeSet = NewObject<UAttributeSet>(GetOwner(), AttributeSetClass);

			//and init the attributes
			for (auto KV : AbilityInfo.AttributeInitalizers)
			{
				FGameplayAttribute Attribute = KV.Key;
				float val = KV.Value;

				if (Attribute.GetAttributeSetClass() == NewAttributeSet->GetClass())
				{
					if (FNumericProperty* NumericProperty = CastField<FNumericProperty>(Attribute.GetUProperty()))
					{
						void* ValuePtr = NumericProperty->ContainerPtrToValuePtr<void>(NewAttributeSet);
						NumericProperty->SetFloatingPointPropertyValue(ValuePtr, val);
					}
					else if (FStructProperty* StructProperty = CastField<FStructProperty>(Attribute.GetUProperty()))
					{
						FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(NewAttributeSet);
						if (DataPtr)
						{
							DataPtr->SetBaseValue(val);
							DataPtr->SetCurrentValue(val);
						}
					}
				}
				
				//BEGIN =@OVERRIDED CODE MARKER@= Make it run soft attribute defaults after setting hard default values
				if (UASSAttributeSet* SSNewAttributeSet = Cast<UASSAttributeSet>(NewAttributeSet))
				{
					SSNewAttributeSet->SetSoftAttributeDefaults();
				}
				//END =@OVERRIDED CODE MARKER@=
			}

			//and then tell watchers that a new attribute set has been created
			OnAttributeSetCreated.Broadcast(this, NewAttributeSet, AbilitySource);

			StoreInto.InstancedAttributeSets.Add(NewAttributeSet);
		}
	}


	if (UAbilitySystemComponent* ASC = GetOwnerAbilitySystem())
	{
		//Add any loose tags first, that way any abilities or effects we add later behave properly with the tags  
		ASC->AddLooseGameplayTags(AbilityInfo.GrantedTags, 1);

		if (GetOwnerRole() == ROLE_Authority)
		{
			//Add any attribute sets we have
			for (UAttributeSet* AttributeSet : StoreInto.InstancedAttributeSets)
			{
				if (!UArcItemBPFunctionLibrary::ASCHasAttributeSet(ASC, AttributeSet->GetClass()))
				{
					AttributeSet->Rename(nullptr, GetOwner());
					UArcItemBPFunctionLibrary::ASCAddInstancedAttributeSet(ASC, AttributeSet);

				}
			}


			//Add all the active abilities for the ability slots we have
			for (auto AbilityInfoStruct : AbilityInfo.ActiveAbilityEntries)
			{
				TSubclassOf<UGameplayAbility> AbilityClass = AbilityInfoStruct.ActiveAbilityClass;
				UArcInvInputBinder* InputBinder = AbilityInfoStruct.InputBinder;
				if (!IsValid(AbilityClass) || !IsValid(InputBinder))
				{
					continue;
				}

				int32 InputIndex = InputBinder->GetInputBinding(ASC, AbilityClass);
				FGameplayAbilitySpec Spec(AbilityClass.GetDefaultObject(), 1, InputIndex, AbilitySource);


				FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
				StoreInto.AddedAbilities.Add(Handle);
			}
			//and add any extras we have
			for (auto ExtraAbility : AbilityInfo.ExtraAbilities)
			{
				//If an ability exists already, then don't bother adding it
				//if (ASC->FindAbilitySpecFromClass(ExtraAbility))
				//{
				//	continue;
				//}

				//=@MODIFIED MARKER@= also this class doesnt even override these functions
				if (FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(ExtraAbility))
				{
					if (Spec->SourceObject == AbilitySource)
					{
						continue;
					}
				}
				//=@OVERRIDED CODE MARKER@= what we modified in this override we use our grant ability instead of give ability
				FGameplayAbilitySpecHandle Handle = Cast<USSAbilitySystemComponent>(ASC)->GrantAbility(ExtraAbility, AbilitySource);
				//FGameplayAbilitySpec Spec(ExtraAbility.GetDefaultObject(), 1, INDEX_NONE, AbilitySource);

				//FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(Spec);
				StoreInto.AddedAbilities.Add(Handle);
			}



			//Add any GameplayEffects we have
			for (auto EffectClass : AbilityInfo.AddedGameplayEffects)
			{
				for (auto& Handle : StoreInto.AddedGameplayEffects)
				{
					if (ASC->GetGameplayEffectDefForHandle(Handle) == EffectClass->GetDefaultObject<UGameplayEffect>())
					{
						continue;
					}
				}

				FGameplayEffectContextHandle ECH(UAbilitySystemGlobals::Get().AllocGameplayEffectContext());
				ECH.AddInstigator(GetOwner(), GetOwner());
				FGameplayEffectSpec Spec(EffectClass->GetDefaultObject<UGameplayEffect>(), ECH, 1);


				FActiveGameplayEffectHandle Handle = ASC->ApplyGameplayEffectSpecToSelf(Spec);
				//Store any non-instant handles we get.  Instant Gameplay Effects will fall off right away so we don't need to remove them later
				//Really, items shouldn't use instant GEs.
				if (Spec.Def->DurationPolicy != EGameplayEffectDurationType::Instant)
				{
					StoreInto.AddedGameplayEffects.Add(Handle);
				}
			}

			ASC->bIsNetDirty = true;
		}


	}

	return true;
}


void USSArcInventoryComponent_Active::OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	// Problem 1: Not sure if this is a UI problem or if it's maybe just some problem with attribute initializers or something like that, but for some reason the ui starts you off with 0 backup ammo and you nmeed to reload in order for the backup ammo to update (happened on listening server but using that as a reference since client version doesn't exactly work rn because of problem 2)
	// Problem 2: This event on the client gets nullptr passed into the PreviousItemStack unfortunately. This means we can't destroy the previous item's widget when it's unequiped
	// Problem 3: Right now only the server runs this when the game fills the players inventory with startup weapons, so we need this to somehow be called on client too on startup
	// Looks like Roy is working on fixing both problems 2 and 3... Well just wait on the next ArcInventory update to finish this stuff (problem 1 might be easier to solve after 2 and 3 are fixed)
	/*
		If we are getting egar to have problem 2 fixed before Roy gets out the new update, we can just paste this check in ArcInventoryItemTypes.cpp line 143:
		if (IsValid(ItemStack))
		{
			Owner->OnItemSlotChange.Broadcast(Owner, FArcInventoryItemSlotReference(*this, Owner), ItemStack, nullptr);
		}
	*/


	// Untested since we are waiting on these problems to be resolved for the next ArcInventory update
	if (IsValid(ItemStack))		// If we are equiping
	{
		// We will create the item's widget so we can show it when it later becomes "Active"
		if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
		{
			if (!IsValid(SSArcItemStack->ActiveItemWidget))		// Only create a new widget if it doesn't already exist
			{
				if (USSUArcUIData_ActiveItemDefinition* ItemUIData = Cast<USSUArcUIData_ActiveItemDefinition>(ItemStack->GetUIData()))
				{
					if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
					{
						if (OwningPawn->IsLocallyControlled())
						{
							if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
							{
								if (UUW_ActiveItem* WidgetToCreate = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, ItemUIData->ActiveItemWidgetTSub, OwningPC)))
								{
									WidgetToCreate->AddToViewport();
									WidgetToCreate->SetVisibility(ESlateVisibility::Collapsed);
									SSArcItemStack->ActiveItemWidget = WidgetToCreate;
								}
							}
						}
					}
				}
			}
		}
	}
	else						// If we are UNequiping
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
		if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
		{
			if (OwningPawn->IsLocallyControlled())
			{
				if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
				{
					if (USSUArcUIData_ActiveItemDefinition* ItemUIData = Cast<USSUArcUIData_ActiveItemDefinition>(ItemStack->GetUIData()))
					{
						if (AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
						{
							if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
							{
								UUW_ActiveItem* WidgetToDisplay = nullptr;			// This ptr represents the widget that will show up on screen (whether it's already created or not)
								if (SSArcItemStack->ActiveItemWidget == nullptr)	// If for some reason the widget wasn't created successfully on item equip
								{
									UE_LOG(UISetup, Warning, TEXT("%s() New active item stack did not point to a valid item widget when trying to make it visible. Equipping the item maybe didn't successfully create the widget so we have nothing. We will create the widget now but something seams to have messed up at some point"), *FString(__FUNCTION__));
									// Create the widget and add to viewport
									WidgetToDisplay = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, ItemUIData->ActiveItemWidgetTSub, OwningPC));
									if (WidgetToDisplay)
									{
										SSArcItemStack->ActiveItemWidget = WidgetToDisplay;
										ShooterHUD->CurrentActiveItemWidget = WidgetToDisplay;
										WidgetToDisplay->AddToViewport();
									}
								}
								else												// The widget from USSArcItemStack was valid as expected (it was created on item equip), so we will make it visible
								{
									WidgetToDisplay = SSArcItemStack->ActiveItemWidget;
									if (WidgetToDisplay)
									{
										WidgetToDisplay->SetVisibility(ESlateVisibility::Visible);
										ShooterHUD->CurrentActiveItemWidget = WidgetToDisplay;
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
									UE_LOG(LogUI, Fatal, TEXT("%s(): When trying to inject the new active item name into UUW_Ammo on create, we couldn't, because the cast from UUserWidget to UUW_Ammo failed"), *FString(__FUNCTION__));
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
		UE_LOG(UISetup, Warning, TEXT("%s() Item's widget was not successfully displayed on item active (a cast must have failed in the process)"), *FString(__FUNCTION__));
	}
}

void USSArcInventoryComponent_Active::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Remove UIData widgets
	if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
	{
		if (OwningPawn->IsLocallyControlled())
		{
			if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
			{
				if (AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
				{
					if (USSArcItemStack* SSArcItemStack = Cast<USSArcItemStack>(ItemStack))
					{
						// We only to make item's widget not visible
						UUW_ActiveItem* WidgetToHide = SSArcItemStack->ActiveItemWidget;
						if (WidgetToHide)
						{
							WidgetToHide->SetVisibility(ESlateVisibility::Collapsed);
							ShooterHUD->CurrentActiveItemWidget = nullptr;		// We set this pointer to null since at this point it's not visible to the player (indicating the item is no longer active)
						}
					}
				}
			}
		}
	}
}

