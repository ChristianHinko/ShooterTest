// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/STInventoryProcessor_Shooter.h"

#include "Modular/ArcItemStackModular.h"
#include "Inventory/AIEBlueprintFunctionLibrary_Inventory.h"
#include "UI/STHUD_Shooter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Modular/ArcItemStackModular.h"
#include "Inventory/Item/Fragments/STItemFragment_BulletSpread.h"
#include "Subobjects/ASSActorComponent_AvatarActorExtension.h"
#include "GCUtils_ObjectTraversal.h"
#include "Inventory/Item/Fragments/AIEItemFragment_UIData.h"
#include "Inventory/Item/Fragments/STItemFragment_ClipAmmo.h"
#include "Inventory/AIEBlueprintFunctionLibrary_Inventory.h"
#include "Blueprint/UserWidget.h"



USTInventoryProcessor_Shooter::USTInventoryProcessor_Shooter()
{

}

void USTInventoryProcessor_Shooter::OnInventoryInit_Implementation()
{
    Super::OnInventoryInit_Implementation();


    UASSActorComponent_AvatarActorExtension* AvatarActorExtensionComponent = GetOwningActor()->FindComponentByClass<UASSActorComponent_AvatarActorExtension>();
    if (IsValid(AvatarActorExtensionComponent))
    {
        AvatarActorExtensionComponent->OnInitializeAbilitySystemComponentDelegate.AddUObject(this, &USTInventoryProcessor_Shooter::OnInitializeAbilitySystemComponent);
    }
}


void USTInventoryProcessor_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent& ASC)
{
    // Re-inject the new Ability System Component into our active gun
    UArcItemStackModular* ItemStack = Cast<UArcItemStackModular>(GetActiveItemStack());
    if (IsValid(ItemStack))
    {
        USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();
        if (IsValid(BulletSpreadItemFragment))
        {
            BulletSpreadItemFragment->SetAbilitySystemComponent(GetOwningAbilitySystemComponent());
        }
    }
}

void USTInventoryProcessor_Shooter::OnItemSlotChange_Implementation(const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStackModular* ItemStack, UArcItemStackModular* PreviousItemStack, FGameplayTag Context)
{
    Super::OnItemSlotChange_Implementation(ItemSlotRef, ItemStack, PreviousItemStack, Context);

    if (IsValid(ItemStack) && ItemStack != PreviousItemStack) // if we are Equiping
    {
        // Item fragment initialization
        {
            UAIEBlueprintFunctionLibrary_Inventory::CreateInstancedVersionOfItemFragmentIfNeeded<
                USTItemFragment_ClipAmmo,
                USTItemFragment_ClipAmmoInstanced>(ItemStack);

            UAIEBlueprintFunctionLibrary_Inventory::CreateInstancedVersionOfItemFragmentIfNeeded<
                USTItemFragment_BulletSpread,
                USTItemFragment_BulletSpreadInstanced>(ItemStack);
        }

        // Inject the Ability System Component into our bullet spread fragment
        USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();
        if (IsValid(BulletSpreadItemFragment))
        {
            BulletSpreadItemFragment->SetAbilitySystemComponent(GetOwningAbilitySystemComponent());
            BulletSpreadItemFragment->ResetBulletSpread();
        }
    }
}


void USTInventoryProcessor_Shooter::MakeItemActive(int32 NewActiveItemSlot)
{
    Super::MakeItemActive(NewActiveItemSlot);

    UArcItemStackModular* ActiveItemStack = GetActiveItemStack();
    if (!IsValid(ActiveItemStack))
    {
        return;
    }



    // Reset our gun's CurrentBulletSpread
    {
        UArcItemStackModular* ItemStack = Cast<UArcItemStackModular>(ActiveItemStack);
        if (IsValid(ItemStack))
        {
            USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();
            if (IsValid(BulletSpreadItemFragment))
            {
                // NOTE: The BulletSpread subobject looks for numeric Attribute values from the ASC. These Attribute values should be the ones
                // from this newly active item - HOWEVER, on the Client, it has to wait for the Server to replicate the UAbilitySystemComponent::SpawnedAttributes array. So it
                // ends up taking a bit to have the correct Bullet Spread values.
                // This is the result of having a predictive Gameplay Ability without having predictive Attribute Set adding and removing (because addition and removal of Attribute Sets is not meant to be predictive of course).
                // The predictive STGameplayAbility_SwapActiveItem Ability effectively adds and removes Attribute Sets (by changing the active item) non-predictively which is the root of the problem.
                // I guess this is just a limitation of dynamically adding and removing Attribute Sets during runtime.
                // You can notice this problem by looking at the crosshair. When swapping active weapons, the gun is using the old weapon's bullet spread for a split second.
                BulletSpreadItemFragment->SetAbilitySystemComponent(GetOwningAbilitySystemComponent()); // ensure it has the ASC
                BulletSpreadItemFragment->ResetBulletSpread();
            }
        }
    }


    // Set the HUD's widget pointer
    APlayerController* owningPlayerController = GCUtils::ObjectTraversal::GetTypedSelfOrOwnerActor<APlayerController>(GetOwningActor());
    if (IsValid(owningPlayerController))
    {
        if (owningPlayerController->IsLocalController())
        {
            ASTHUD_Shooter* shooterHUD = Cast<ASTHUD_Shooter>(owningPlayerController->GetHUD());
            if (IsValid(shooterHUD))
            {
                UAIEItemFragment_UIDataInstanced* uIDataItemFragment = ActiveItemStack->FindFirstFragment<UAIEItemFragment_UIDataInstanced>();
                if (IsValid(uIDataItemFragment))
                {
                    if (IsValid(uIDataItemFragment->ItemWidget))
                    {
                        shooterHUD->CurrentActiveItemWidget = uIDataItemFragment->ItemWidget;
                    }
                }
            }
        }
    }
}

void USTInventoryProcessor_Shooter::MakeItemInactive()
{
    const FArcInventoryItemSlotReference& SlotToBeMadeActive = GetActiveItemSlot();
    UArcItemStackModular* ItemStack = GetItemInSlot(SlotToBeMadeActive); // the item stack that ArcInventory will soon make inactive

    // Reset our gun's CurrentBulletSpread
    if (IsValid(ItemStack))
    {
        USTItemFragment_BulletSpreadInstanced* BulletSpreadItemFragment = ItemStack->FindFirstFragment<USTItemFragment_BulletSpreadInstanced>();
        if (IsValid(BulletSpreadItemFragment))
        {
            BulletSpreadItemFragment->ResetBulletSpread();
        }
    }


    // Clear the HUD's widget pointer
    APlayerController* OwningPlayerController = GCUtils::ObjectTraversal::GetTypedSelfOrOwnerActor<APlayerController>(GetOwningActor());
    if (IsValid(OwningPlayerController))
    {
        if (OwningPlayerController->IsLocalController())
        {
            ASTHUD_Shooter* ShooterHUD = Cast<ASTHUD_Shooter>(OwningPlayerController->GetHUD());
            if (IsValid(ShooterHUD))
            {
                ShooterHUD->CurrentActiveItemWidget = nullptr;
            }
        }
    }


    Super::MakeItemInactive(); // makes the active item stack inactive
}
