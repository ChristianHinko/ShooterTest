// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UW_Crosshair.h"

#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Item/AS_Gun.h"
#include "Utilities/LogCategories.h"
#include "Player/SSPlayerController.h"



UUW_Crosshair::UUW_Crosshair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpreadAttribute = UAS_Gun::GetCurrentBulletSpreadAttribute();
}


void UUW_Crosshair::NativeConstruct()
{
	Super::NativeConstruct();


	if (APlayerController* OwningPlayer = GetOwningPlayer())
	{
		if (OwningPlayer->PlayerState)
		{
			if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(OwningPlayer->PlayerState))
			{
				PlayerASC = AbilitySystem->GetAbilitySystemComponent();


				if (SpreadAttribute.IsValid())
				{
					PlayerASC->GetGameplayAttributeValueChangeDelegate(SpreadAttribute).AddUObject(this, &UUW_Crosshair::OnSpreadAttributeChanged);

					const float InitialSpread = PlayerASC->GetNumericAttribute(SpreadAttribute);
					SetCurrentSpread(InitialSpread);
				}
			}
			else
			{
				UE_LOG(LogUI, Error, TEXT("%s(): Cast from player state to ability system FAILED"), *FString(__FUNCTION__));
			}
		}
		else // PS not valid
		{
			//UE_LOG(LogUI, Error, TEXT("%s(): PlayerState was NULL"), *FString(__FUNCTION__));


			// Player state was null, try waiting for it to be valid
			SSOwningPlayerController = Cast<ASSPlayerController>(OwningPlayer);
			if (SSOwningPlayerController)
			{
				SSOwningPlayerController->OnPlayerStateValid.AddUObject(this, &UUW_Crosshair::OnPlayerStateValid);
			}
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): OwningPlayer was NULL"), *FString(__FUNCTION__));
	}
}

void UUW_Crosshair::OnPlayerStateValid()
{
	SSOwningPlayerController->OnPlayerStateValid.RemoveAll(this);

	if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(SSOwningPlayerController->PlayerState))
	{
		PlayerASC = AbilitySystem->GetAbilitySystemComponent();


		if (SpreadAttribute.IsValid())
		{
			PlayerASC->GetGameplayAttributeValueChangeDelegate(SpreadAttribute).AddUObject(this, &UUW_Crosshair::OnSpreadAttributeChanged);

			const float InitialSpread = PlayerASC->GetNumericAttribute(SpreadAttribute);
			SetCurrentSpread(InitialSpread);
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): Cast from player state to ability system FAILED"), *FString(__FUNCTION__));
	}
}

void UUW_Crosshair::OnSpreadAttributeChanged(const FOnAttributeChangeData& Data)
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

	if (SSOwningPlayerController)
	{
		SSOwningPlayerController->OnPlayerStateValid.RemoveAll(this);
	}
}
