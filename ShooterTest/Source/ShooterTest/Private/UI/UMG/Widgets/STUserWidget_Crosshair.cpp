// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_Crosshair.h"

#include "Inventory/Item/Gun/STAttributeSet_Gun.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Subobjects/STObject_BulletSpread.h"
#include "AbilitySystem/Types/STGameplayAbilityTypes.h"
#include "Components/ArcInventoryComponent_Active.h"
#include "Inventory/Item/Gun/STItemStack_Gun.h"



USTUserWidget_Crosshair::USTUserWidget_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void USTUserWidget_Crosshair::NativePreConstruct()
{
	Super::NativePreConstruct();


	//ImageTop->SetRenderTransformAngle(0.f);
	//ImageBottom->SetRenderTransformAngle(180.f);
	//ImageLeft->SetRenderTransformAngle(-90.f);
	//ImageRight->SetRenderTransformAngle(90.f);
}

void USTUserWidget_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();

	ImageTop->SetBrush(CrosshairBrush);
	ImageBottom->SetBrush(CrosshairBrush);
	ImageLeft->SetBrush(CrosshairBrush);
	ImageRight->SetBrush(CrosshairBrush);
}

void USTUserWidget_Crosshair::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	// Get BulletSpread subobject
	if (const FSTGameplayAbilityActorInfo_Shooter* ShooterActorInfo = static_cast<const FSTGameplayAbilityActorInfo_Shooter*>(PlayerASC->AbilityActorInfo.Get()))
	{
		UArcInventoryComponent_Active* InventoryComponentActive = Cast<UArcInventoryComponent_Active>(ShooterActorInfo->InventoryComponent);
		if (IsValid(InventoryComponentActive))
		{
			const USTItemStack_Gun* GunStack = Cast<USTItemStack_Gun>(InventoryComponentActive->GetActiveItemStack());
			if (IsValid(GunStack))
			{
				BulletSpreadSubobject = GunStack->GetBulletSpreadSubobject();
			}
		}
	}

	if (BulletSpreadSubobject.IsValid())
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.AddUObject(this, &USTUserWidget_Crosshair::OnCurrentBulletSpreadChange);

		// Update for initial value
		const float& CurrentBulletSpread = BulletSpreadSubobject->CurrentBulletSpread;
		OnCurrentBulletSpreadChange(BulletSpreadSubobject->CurrentBulletSpread, CurrentBulletSpread, CurrentBulletSpread);
	}
}

void USTUserWidget_Crosshair::OnCurrentBulletSpreadChange(FGCFloatPropertyWrapper& PropertyWrapper, const float& InOldValue, const float& InNewValue)
{
	CurrentSpread = InNewValue;
	UpdateCrosshair();
}


void USTUserWidget_Crosshair::UpdateCrosshair()
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


void USTUserWidget_Crosshair::NativeDestruct()
{
	if (BulletSpreadSubobject.IsValid())
	{
		BulletSpreadSubobject->CurrentBulletSpread.ValueChangeDelegate.RemoveAll(this);
	}


	Super::NativeDestruct();
}
