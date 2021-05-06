// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UW_Crosshair.h"

#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "Item/Weapons/AS_Gun.h"



UUW_Crosshair::UUW_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UUW_Crosshair::OnPlayerASCValid()
{
	Super::OnPlayerASCValid();


	ShooterASC = Cast<UASC_Shooter>(PlayerASC);
	if (ShooterASC)
	{
		ShooterASC->OnCurrentBulletSpreadChange->AddDynamic(this, &UUW_Crosshair::OnCurrentBulletSpreadChange);


		// Search for a Gun AttributeSet
		for (UAttributeSet* AttributeSet : PlayerASC->GetSpawnedAttributes_Mutable())
		{
			if (UAS_Gun* GunAttributeSet = Cast<UAS_Gun>(AttributeSet))
			{
				// Call manually for initial value
				float currentBulletSpread = GunAttributeSet->CurrentBulletSpread;
				OnCurrentBulletSpreadChange(currentBulletSpread, currentBulletSpread);
			}
		}
	}

}

void UUW_Crosshair::OnCurrentBulletSpreadChange(const float& OldValue, const float& NewValue)
{
	SetCurrentSpread(NewValue);
}

void UUW_Crosshair::SetCurrentSpread(float NewSpread)
{
	CurrentSpread = NewSpread;
	UpdateCrosshair();
}


void UUW_Crosshair::NativeDestruct()
{
	if (ShooterASC)
	{
		ShooterASC->OnCurrentBulletSpreadChange->RemoveAll(this);
	}


	Super::NativeDestruct();
}
