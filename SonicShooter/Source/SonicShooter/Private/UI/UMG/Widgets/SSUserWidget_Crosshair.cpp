// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/SSUserWidget_Crosshair.h"

#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Subobjects/SSObject_BulletSpread.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSInventoryComponent_Active.h"
#include "Inventory/Item/Gun/SSItemStack_Gun.h"



USSUserWidget_Crosshair::USSUserWidget_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void USSUserWidget_Crosshair::NativePreConstruct()
{
	Super::NativePreConstruct();


	//ImageTop->SetRenderTransformAngle(0.f);
	//ImageBottom->SetRenderTransformAngle(180.f);
	//ImageLeft->SetRenderTransformAngle(-90.f);
	//ImageRight->SetRenderTransformAngle(90.f);
}

void USSUserWidget_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();

	ImageTop->SetBrush(CrosshairBrush);
	ImageBottom->SetBrush(CrosshairBrush);
	ImageLeft->SetBrush(CrosshairBrush);
	ImageRight->SetBrush(CrosshairBrush);
}

void USSUserWidget_Crosshair::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get BulletSpread subobject
	if (const FSSGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSSGameplayAbilityActorInfo_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		USSInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const USSItemStack_Gun* GunStack = Cast<USSItemStack_Gun>(InventoryComponent->GetActiveItemStack());
			if (IsValid(GunStack))
			{
				BulletSpreadSubobject = GunStack->GetBulletSpreadSubobject();
			}
		}
	}

	if (BulletSpreadSubobject.IsValid())
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.AddDynamic(this, &USSUserWidget_Crosshair::OnCurrentBulletSpreadChange);

		const float& CurrentBulletSpread = BulletSpreadSubobject->CurrentBulletSpread;
		OnCurrentBulletSpreadChange(CurrentBulletSpread, CurrentBulletSpread);
	}

}

void USSUserWidget_Crosshair::OnCurrentBulletSpreadChange(const float& OldValue, const float& NewValue)
{
	CurrentSpread = NewValue;
	UpdateCrosshair();
}


void USSUserWidget_Crosshair::UpdateCrosshair()
{
	if (CurrentSpread <= 0)
	{
		SizeBoxTop->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxBottom->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxLeft->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxRight->SetRenderTranslation(FVector2D::ZeroVector);
		return;
	}

	const float Number = 5.f; // arbitrary multiplier

	SizeBoxTop->SetRenderTranslation(CurrentSpread * Number * FVector2D(0, -1));
	SizeBoxBottom->SetRenderTranslation(CurrentSpread * Number * FVector2D(0, 1));
	SizeBoxLeft->SetRenderTranslation(CurrentSpread * Number * FVector2D(-1, 0));
	SizeBoxRight->SetRenderTranslation(CurrentSpread * Number * FVector2D(1, 0));
}


void USSUserWidget_Crosshair::NativeDestruct()
{
	if (BulletSpreadSubobject.IsValid())
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.RemoveAll(this);
	}


	Super::NativeDestruct();
}
