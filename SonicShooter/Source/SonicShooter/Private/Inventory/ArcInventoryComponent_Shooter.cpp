// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ArcInventoryComponent_Shooter.h"

#include "Inventory/Item/SSArcItemDefinition_Active.h"
#include "UI/HUD_Shooter.h"
#include "UI/UMG/Widgets/UW_ActiveItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Subobjects/O_BulletSpread.h"
#include "BlueprintFunctionLibraries/HLBlueprintFunctionLibrary_InterfaceHelpers.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"



UArcInventoryComponent_Shooter::UArcInventoryComponent_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UArcInventoryComponent_Shooter::InitializeComponent()
{
	Super::InitializeComponent();


	OnItemSlotChange.AddDynamic(this, &UArcInventoryComponent_Shooter::OnItemSlotChangeEvent);

	OnItemInactive.AddDynamic(this, &UArcInventoryComponent_Shooter::OnItemInactiveEvent);

	UASSActorComponent_AbilitySystemSetup* AbilitySystemSetupComponent = GetOwner()->FindComponentByClass<UASSActorComponent_AbilitySystemSetup>();
	if (IsValid(AbilitySystemSetupComponent))
	{
		AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &UArcInventoryComponent_Shooter::OnInitializeAbilitySystemComponent);
	}
}


void UArcInventoryComponent_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	// Re-inject the new Ability System Component into our active gun
	UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(GetActiveItemStack());
	if (IsValid(GunStack))
	{
		GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(GetOwnerAbilitySystem());
	}
}

void UArcInventoryComponent_Shooter::OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (IsValid(ItemStack) && ItemStack != PreviousItemStack) // if we are Equiping
	{
		// Inject the Ability System Component into our gun
		{
			UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ItemStack);
			if (IsValid(GunStack))
			{
				GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(GetOwnerAbilitySystem());
				GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
			}
		}

		// Create UI Data
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
								SSArcItemStack->ActiveItemWidget = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC));
								SSArcItemStack->ActiveItemWidget->ActiveItemName = ItemStack->ItemName; // inject ItemName
							}
						}
					}
				}

			}
		}
	}
	else if (IsValid(PreviousItemStack) && PreviousItemStack != ItemStack) // if we are UnEquiping
	{
		// Clear the gun's Ability System Component
		{
			UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(PreviousItemStack);
			if (IsValid(GunStack))
			{
				GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(nullptr);
				GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
			}
		}

		// Remove UI Data
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


void UArcInventoryComponent_Shooter::MakeItemActive(int32 NewActiveItemSlot)
{
	Super::MakeItemActive(NewActiveItemSlot);

	UArcItemStack* ActiveItemStack = GetActiveItemStack();
	if (!IsValid(ActiveItemStack))
	{
		return;
	}



	// Reset our gun's CurrentBulletSpread
	{
		UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
		if (IsValid(GunStack))
		{
			// NOTE: The BulletSpread subobject looks for numeric Attribute values from the ASC. These Attribute values should be the ones
			// from this newly active item - HOWEVER, on the Client, it has to wait for the Server to replicate the UAbilitySystemComponent::SpawnedAttributes array. So it
			// ends up taking a bit to have the correct Bullet Spread values.
			// This is the result of having a predictive Gameplay Ability without having predictive Attribute Set adding and removing (because addition and removal of Attribute Sets is not meant to be predictive of course).
			// The predictive GA_SwapActiveItem Ability effectively adds and removes Attribute Sets (by changing the active item) non-predictively which is the root of the problem.
			// I guess this is just a limitation of dynamically adding and removing Attribute Sets during runtime.
			// You can notice this problem by looking at the crosshair. When swapping active weapons, the gun is using the old weapon's bullet spread for a split second.
			GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(GetOwnerAbilitySystem()); // ensure it has the ASC
			GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
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
							if (!IsValid(SSArcItemStack->ActiveItemWidget))
							{
								// No valid Widget! - For some reason the Widget wasn't created successfully in OnItemSlotChangeEvent()!
								UE_LOG(UISetup, Warning, TEXT("%s() New active Item Stack did not point to a valid item Widget when trying to add it to Viewport. Equipping the item maybe didn't successfully create the Widget so we have nothing. We will create the Widget now but something seams to have messed up at some point"), ANSI_TO_TCHAR(__FUNCTION__));
								
								// Create the Widget
								SSArcItemStack->ActiveItemWidget = Cast<UUW_ActiveItem>(UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC));
								SSArcItemStack->ActiveItemWidget->ActiveItemName = ActiveItemStack->ItemName; // inject ItemName
							}
							
							// Add the Widget to Viewport
							UUW_ActiveItem* WidgetToAdd = SSArcItemStack->ActiveItemWidget;
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

void UArcInventoryComponent_Shooter::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Reset our gun's CurrentBulletSpread
	{
		UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ItemStack);
		if (IsValid(GunStack))
		{
			GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
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
