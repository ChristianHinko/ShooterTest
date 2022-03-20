// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UMG/Widgets/UW_Crosshair.h"

#include "Inventory/Item/Gun/AS_Gun.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Subobjects/O_BulletSpread.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"



UUW_Crosshair::UUW_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UUW_Crosshair::NativePreConstruct()
{
	Super::NativePreConstruct();


	//ImageTop->SetRenderTransformAngle(0.f);
	//ImageBottom->SetRenderTransformAngle(180.f);
	//ImageLeft->SetRenderTransformAngle(-90.f);
	//ImageRight->SetRenderTransformAngle(90.f);
}

void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();

	ImageTop->SetBrush(CrosshairBrush);
	ImageBottom->SetBrush(CrosshairBrush);
	ImageLeft->SetBrush(CrosshairBrush);
	ImageRight->SetBrush(CrosshairBrush);
}

void UUW_Crosshair::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get BulletSpread subobject
	if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
		if (IsValid(InventoryComponent))
		{
			const UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(InventoryComponent->GetActiveItemStack());
			if (IsValid(GunStack))
			{
				BulletSpreadSubobject = GunStack->GetBulletSpreadSubobject();
			}
		}
	}

	if (IsValid(BulletSpreadSubobject))
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.AddDynamic(this, &UUW_Crosshair::OnCurrentBulletSpreadChange);

		const float& CurrentBulletSpread = BulletSpreadSubobject->CurrentBulletSpread;
		OnCurrentBulletSpreadChange(CurrentBulletSpread, CurrentBulletSpread);
	}

}

void UUW_Crosshair::OnCurrentBulletSpreadChange(const float& OldValue, const float& NewValue)
{
	CurrentSpread = NewValue;
	UpdateCrosshair();
}


void UUW_Crosshair::UpdateCrosshair()
{
	if (CurrentSpread <= 0)
	{
		SizeBoxTop->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxBottom->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxLeft->SetRenderTranslation(FVector2D::ZeroVector);
		SizeBoxRight->SetRenderTranslation(FVector2D::ZeroVector);
		return;
	}

	const float number = 5.f; // arbitrary multiplier

	SizeBoxTop->SetRenderTranslation(CurrentSpread * number * FVector2D(0, -1));
	SizeBoxBottom->SetRenderTranslation(CurrentSpread * number * FVector2D(0, 1));
	SizeBoxLeft->SetRenderTranslation(CurrentSpread * number * FVector2D(-1, 0));
	SizeBoxRight->SetRenderTranslation(CurrentSpread * number * FVector2D(1, 0));
}


void UUW_Crosshair::NativeDestruct()
{
	if (BulletSpreadSubobject)
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.RemoveAll(this);
	}


	Super::NativeDestruct();
}
