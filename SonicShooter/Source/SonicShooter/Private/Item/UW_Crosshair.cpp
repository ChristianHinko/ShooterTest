// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UW_Crosshair.h"

#include "Item/Weapons/AS_Gun.h"



UUW_Crosshair::UUW_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Gun::GetCurrentBulletSpreadAttribute());
}


void UUW_Crosshair::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


	if (Attribute == UAS_Gun::GetCurrentBulletSpreadAttribute())
	{
		SetCurrentSpread(NewValue);
	}
}

void UUW_Crosshair::SetCurrentSpread(float NewSpread)
{
	CurrentSpread = NewSpread;
	UpdateCrosshair();
}
