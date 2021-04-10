// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_AttributeBacked.h"

#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Utilities/LogCategories.h"
#include "Player/SSPlayerController.h"



UUW_AttributeBacked::UUW_AttributeBacked()
{
#if 0
	AttributesToListenFor.Add(UAS_MyAttributeSet::GetMyAttributeAttribute());
#endif


}


void UUW_AttributeBacked::NativeConstruct()
{
	Super::NativeConstruct();


	if (APlayerController* OwningPlayer = GetOwningPlayer())
	{
		if (OwningPlayer->PlayerState)
		{
			if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(OwningPlayer->PlayerState))
			{
				PlayerASC = AbilitySystem->GetAbilitySystemComponent();


				SetUpAttributeListeningFor(PlayerASC);
			}
			else
			{
				UE_LOG(LogUI, Error, TEXT("%s(): Cast from player state to ability system FAILED"), *FString(__FUNCTION__));
			}
		}
		else // PS not valid
		{
			//UE_LOG(LogUI, Error, TEXT("%s(): PlayerState was NULL"), *FString(__FUNCTION__));


			SSOwningPlayerController = Cast<ASSPlayerController>(OwningPlayer);
			if (SSOwningPlayerController)
			{
				// Player state was null, so try waiting for it to be valid
				SSOwningPlayerController->OnPlayerStateValid.AddUObject(this, &UUW_AttributeBacked::OnPlayerStateValid);
			}
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): OwningPlayer was NULL"), *FString(__FUNCTION__));
	}
}

void UUW_AttributeBacked::SetUpAttributeListeningFor(UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		UE_LOG(LogUI, Error, TEXT("%s(): the passed in ASC was NULL"), *FString(__FUNCTION__));
		return;
	}

	for (FGameplayAttribute Attribute : AttributesToListenFor)
	{
		if (Attribute.IsValid() == false)
		{
			UE_LOG(LogUI, Warning, TEXT("%s(): %s attribute was not valid when trying to bind to change delegate"), *FString(__FUNCTION__), *(Attribute.AttributeName));
			continue;
		}

		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UUW_AttributeBacked::OnAttributeChanged);

		FOnAttributeChangeData ChangeData;
		ChangeData.Attribute = Attribute;
		ChangeData.NewValue = ASC->GetNumericAttribute(Attribute);
		ChangeData.OldValue = ChangeData.NewValue;

		OnAttributeChanged(ChangeData); // manually call this so we get the initial attribute value
	}
}

void UUW_AttributeBacked::OnPlayerStateValid()
{
	SSOwningPlayerController->OnPlayerStateValid.RemoveAll(this);


	if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(SSOwningPlayerController->PlayerState))
	{
		PlayerASC = AbilitySystem->GetAbilitySystemComponent();


		SetUpAttributeListeningFor(PlayerASC);
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): Cast from player state to ability system FAILED"), *FString(__FUNCTION__));
	}
}

void UUW_AttributeBacked::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


#if 0
	if (Attribute == MyAttribute) // check which attribute changed
	{
		SetMyValueForUI(NewValue); // update UI for this attribute
	}
#endif
}

void UUW_AttributeBacked::NativeDestruct()
{
	Super::NativeDestruct();


	if (SSOwningPlayerController)
	{
		// In case we were destructed before PS was valid (or in case something weird happened)
		SSOwningPlayerController->OnPlayerStateValid.RemoveAll(this);
	}

	if (PlayerASC)
	{
		// Stop listening
		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			PlayerASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}
}
