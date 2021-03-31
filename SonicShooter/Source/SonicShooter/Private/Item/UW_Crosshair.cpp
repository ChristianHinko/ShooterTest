// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UW_Crosshair.h"

#include "Player/SSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Item/AS_Gun.h"



UUW_Crosshair::UUW_Crosshair()
{
	SpreadAttribute = UAS_Gun::GetCurrentBulletSpreadAttribute();
}


void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();


	if (GetOwningPlayer() && GetOwningPlayer()->PlayerState)
	{
		if (ASSPlayerState* SSPlayerState = Cast<ASSPlayerState>(GetOwningPlayer()->PlayerState))
		{
			PlayerASC = SSPlayerState->GetAbilitySystemComponent();
		}
	}

	if (PlayerASC && SpreadAttribute.IsValid())
	{
		PlayerASC->GetGameplayAttributeValueChangeDelegate(SpreadAttribute).AddUObject(this, &UUW_Crosshair::SpreadAttributeChanged);

		const float initialSpread = PlayerASC->GetNumericAttribute(SpreadAttribute);
		SetCurrentSpread(initialSpread);
	}
}

void UUW_Crosshair::SpreadAttributeChanged(const FOnAttributeChangeData& Data)
{
	const float NewValue = Data.NewValue;


	SetCurrentSpread(NewValue);
}

void UUW_Crosshair::SetCurrentSpread(float NewSpread)
{
	CurrentSpread = NewSpread;
	UpdateCrosshair();
}

void UUW_Crosshair::NativeDestruct()
{
	Super::NativeDestruct();


	if (PlayerASC)
	{
		PlayerASC->GetGameplayAttributeValueChangeDelegate(SpreadAttribute).RemoveAll(this);
	}
}
