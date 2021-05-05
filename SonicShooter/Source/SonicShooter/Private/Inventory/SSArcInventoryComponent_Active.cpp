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
#include "Item/SSArcItemDefinition.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Item/UW_Crosshair.h"
#include "UI/UMG/Widgets/UW_Ammo.h"
#include "Utilities/LogCategories.h"

#include "AbilitySystem/SSAttributeSet.h"


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

	OnItemInactive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemInactiveEvent);
	OnItemActive.AddDynamic(this, &USSArcInventoryComponent_Active::OnItemActiveEvent);
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
				if (USSAttributeSet* SSNewAttributeSet = Cast<USSAttributeSet>(NewAttributeSet))
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


void USSArcInventoryComponent_Active::OnItemActiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{

	// Add UIData widgets
	if (ItemStack)	// If it's not valid, we don't have to warning because it he might just not have an item here
	{
		if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
		{
			if (OwningPawn->IsLocallyControlled())
			{
				if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
				{
					if (USSUArcUIData_ItemDefinition* ItemUIData = Cast<USSUArcUIData_ItemDefinition>(ItemStack->GetUIData()))
					{
						if (AHUD_Shooter* ShooterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
						{
							// Create our widgets and add them to viewport
							ShooterHUD->ActiveItemWidget = UWidgetBlueprintLibrary::Create(this, ItemUIData->ActiveItemWidgetTSub, OwningPC);
							if (ShooterHUD->ActiveItemWidget)
							{
								ShooterHUD->ActiveItemWidget->AddToViewport();
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

void USSArcInventoryComponent_Active::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{




	// Remove UIData widgets
	if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
	{
		if (OwningPawn->IsLocallyControlled())
		{
			if (APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController()))
			{
				if (AHUD_Shooter* ShooterCharacterHUD = Cast<AHUD_Shooter>(OwningPC->GetHUD()))
				{
					if (ShooterCharacterHUD->ActiveItemWidget)
					{
						ShooterCharacterHUD->ActiveItemWidget->RemoveFromViewport();
						ShooterCharacterHUD->ActiveItemWidget = nullptr;
					}
				}
			}
		}
	}
}

