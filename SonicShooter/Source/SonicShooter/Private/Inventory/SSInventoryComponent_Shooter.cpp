// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSInventoryComponent_Shooter.h"

#include "Inventory/Item/SSItemDefinition_Active.h"
#include "UI/SSHUD_Shooter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "BlueprintFunctionLibraries/HLBlueprintFunctionLibrary_InterfaceHelpers.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"



USSInventoryComponent_Shooter::USSInventoryComponent_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USSInventoryComponent_Shooter::InitializeComponent()
{
	Super::InitializeComponent();


	OnItemSlotChange.AddDynamic(this, &USSInventoryComponent_Shooter::OnItemSlotChangeEvent);

	OnItemInactive.AddDynamic(this, &USSInventoryComponent_Shooter::OnItemInactiveEvent);

	UASSActorComponent_AbilitySystemSetup* AbilitySystemSetupComponent = GetOwner()->FindComponentByClass<UASSActorComponent_AbilitySystemSetup>();
	if (IsValid(AbilitySystemSetupComponent))
	{
		AbilitySystemSetupComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &USSInventoryComponent_Shooter::OnInitializeAbilitySystemComponent);
	}
}


void USSInventoryComponent_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	// Re-inject the new Ability System Component into our active gun
	USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(GetActiveItemStack());
	if (IsValid(GunStack))
	{
		GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(GetOwnerAbilitySystem());
	}
}

void USSInventoryComponent_Shooter::OnItemSlotChangeEvent(UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStack* ItemStack, UArcItemStack* PreviousItemStack)
{
	if (IsValid(ItemStack) && ItemStack != PreviousItemStack) // if we are Equiping
	{
		// Inject the Ability System Component into our gun
		{
			USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ItemStack);
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
				USSItemStack* SSItemStack = Cast<USSItemStack>(ItemStack);
				if (IsValid(SSItemStack))
				{
					if (!IsValid(SSItemStack->ActiveItemWidget)) // only create a new Widget if it doesn't already exist
					{
						const USSUIData_ItemDefinition* UIData = Cast<USSUIData_ItemDefinition>(ItemStack->GetUIData());
						if (IsValid(UIData))
						{
							APlayerController* OwningPC = Cast<APlayerController>(OwningPawn->GetController());
							if (IsValid(OwningPC))
							{
								SSItemStack->ActiveItemWidget = UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC);
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
			USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(PreviousItemStack);
			if (IsValid(GunStack))
			{
				GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(nullptr);
				GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
			}
		}

		// Remove UI Data
		USSItemStack* SSItemStack = Cast<USSItemStack>(PreviousItemStack);
		if (IsValid(SSItemStack))
		{
			UUserWidget* WidgetToRemove = SSItemStack->ActiveItemWidget;
			if (IsValid(WidgetToRemove))
			{
				// We completely get rid of the widget since the inventory now longer has the item
				WidgetToRemove->RemoveFromParent();
				SSItemStack->ActiveItemWidget = nullptr;
			}
		}
	}

}


void USSInventoryComponent_Shooter::MakeItemActive(int32 NewActiveItemSlot)
{
	Super::MakeItemActive(NewActiveItemSlot);

	UArcItemStack* ActiveItemStack = GetActiveItemStack();
	if (!IsValid(ActiveItemStack))
	{
		return;
	}



	// Reset our gun's CurrentBulletSpread
	{
		USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ActiveItemStack);
		if (IsValid(GunStack))
		{
			// NOTE: The BulletSpread subobject looks for numeric Attribute values from the ASC. These Attribute values should be the ones
			// from this newly active item - HOWEVER, on the Client, it has to wait for the Server to replicate the UAbilitySystemComponent::SpawnedAttributes array. So it
			// ends up taking a bit to have the correct Bullet Spread values.
			// This is the result of having a predictive Gameplay Ability without having predictive Attribute Set adding and removing (because addition and removal of Attribute Sets is not meant to be predictive of course).
			// The predictive SSGameplayAbility_SwapActiveItem Ability effectively adds and removes Attribute Sets (by changing the active item) non-predictively which is the root of the problem.
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
				const USSUIData_ItemDefinition* UIData = Cast<USSUIData_ItemDefinition>(ActiveItemStack->GetUIData());
				if (IsValid(UIData))
				{
					ASSHUD_Shooter* ShooterHUD = Cast<ASSHUD_Shooter>(OwningPC->GetHUD());
					if (IsValid(ShooterHUD))
					{
						USSItemStack* SSItemStack = Cast<USSItemStack>(ActiveItemStack);
						if (IsValid(SSItemStack))
						{
							if (!IsValid(SSItemStack->ActiveItemWidget))
							{
								// No valid Widget! - For some reason the Widget wasn't created successfully in OnItemSlotChangeEvent()!
								UE_LOG(UISetup, Warning, TEXT("%s() New active Item Stack did not point to a valid item Widget when trying to add it to Viewport. Equipping the item maybe didn't successfully create the Widget so we have nothing. We will create the Widget now but something seams to have messed up at some point"), ANSI_TO_TCHAR(__FUNCTION__));
								
								// Create the Widget
								SSItemStack->ActiveItemWidget = UWidgetBlueprintLibrary::Create(this, UIData->ActiveItemWidgetTSub, OwningPC);
							}
							
							// Add the Widget to Viewport
							UUserWidget* WidgetToAdd = SSItemStack->ActiveItemWidget;
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

void USSInventoryComponent_Shooter::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	// Reset our gun's CurrentBulletSpread
	{
		USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ItemStack);
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
				const USSItemStack* SSItemStack = Cast<USSItemStack>(ItemStack);
				if (IsValid(SSItemStack))
				{
					UUserWidget* WidgetToRemove = SSItemStack->ActiveItemWidget;
					if (IsValid(WidgetToRemove))
					{
						// Remove ActiveItemWidget from Viewport and clear the pointer from ShooterHUD
						WidgetToRemove->RemoveFromViewport();

						// And clear the pointer from the HUD
						ASSHUD_Shooter* ShooterHUD = Cast<ASSHUD_Shooter>(OwningPC->GetHUD());
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
