// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UW_Crosshair.h"

#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Item/AS_Gun.h"
#include "Utilities/LogCategories.h"



UUW_Crosshair::UUW_Crosshair()
{
	SpreadAttribute = UAS_Gun::GetCurrentBulletSpreadAttribute();
}


void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();


	if (GetOwningPlayer())
	{
		if (GetOwningPlayer()->PlayerState)
		{
			if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(GetOwningPlayer()->PlayerState))
			{
				PlayerASC = AbilitySystem->GetAbilitySystemComponent();
			}
			else
			{
				UE_LOG(LogUI, Error, TEXT("%s(): Cast from player state to ability system FAILED"), *FString(__FUNCTION__));
			}
		}
		else
		{
			UE_LOG(LogUI, Error, TEXT("%s(): PlayerState was NULL"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): OwningPlayer was NULL"), *FString(__FUNCTION__));
	}

	if (PlayerASC && SpreadAttribute.IsValid())
	{
		PlayerASC->GetGameplayAttributeValueChangeDelegate(SpreadAttribute).AddUObject(this, &UUW_Crosshair::SpreadAttributeChanged);

		const float InitialSpread = PlayerASC->GetNumericAttribute(SpreadAttribute);
		SetCurrentSpread(InitialSpread);
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
