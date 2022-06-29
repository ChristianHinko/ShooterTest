// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SSInventoryComponent_Shooter.h"

#include "UI/SSHUD_Shooter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "Subobjects/ASSActorComponent_AbilitySystemSetup.h"
#include "BlueprintFunctionLibraries/GCBlueprintFunctionLibrary_ActorHelpers.h"



USSInventoryComponent_Shooter::USSInventoryComponent_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USSInventoryComponent_Shooter::InitializeComponent()
{
	Super::InitializeComponent();


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
	Super::OnItemSlotChangeEvent(Inventory, ItemSlotRef, ItemStack, PreviousItemStack);

	if (IsValid(ItemStack) && ItemStack != PreviousItemStack) // if we are Equiping
	{
		// Inject the Ability System Component into our gun
		USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ItemStack);
		if (IsValid(GunStack))
		{
			GunStack->GetBulletSpreadSubobject()->SetAbilitySystemComponent(GetOwnerAbilitySystem());
			GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
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


	// Set the HUD's widget pointer
	APlayerController* OwningPlayerController = UGCBlueprintFunctionLibrary_ActorHelpers::GetTypedOwnerOfComponentCasted<APlayerController>(this);
	if (IsValid(OwningPlayerController))
	{
		if (OwningPlayerController->IsLocalController())
		{
			ASSHUD_Shooter* ShooterHUD = Cast<ASSHUD_Shooter>(OwningPlayerController->GetHUD());
			if (IsValid(ShooterHUD))
			{
				UAIEItemStack* AIEItemStack = Cast<UAIEItemStack>(ActiveItemStack);
				if (IsValid(AIEItemStack))
				{
					UUserWidget* ActiveWidget = AIEItemStack->ActiveItemWidget;
					if (IsValid(ActiveWidget))
					{
						ShooterHUD->CurrentActiveItemWidget = ActiveWidget;
					}
				}
			}
		}
	}
}

void USSInventoryComponent_Shooter::OnItemInactiveEvent(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	Super::OnItemInactiveEvent(InventoryComponent, ItemStack);

	// Reset our gun's CurrentBulletSpread
	{
		USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(ItemStack);
		if (IsValid(GunStack))
		{
			GunStack->GetBulletSpreadSubobject()->ResetBulletSpread();
		}
	}


	// Clear the HUD's widget pointer
	APlayerController* OwningPlayerController = UGCBlueprintFunctionLibrary_ActorHelpers::GetTypedOwnerOfComponentCasted<APlayerController>(this);
	if (IsValid(OwningPlayerController))
	{
		if (OwningPlayerController->IsLocalController())
		{
			ASSHUD_Shooter* ShooterHUD = Cast<ASSHUD_Shooter>(OwningPlayerController->GetHUD());
			if (IsValid(ShooterHUD))
			{
				ShooterHUD->CurrentActiveItemWidget = nullptr;
			}
		}
	}
}
