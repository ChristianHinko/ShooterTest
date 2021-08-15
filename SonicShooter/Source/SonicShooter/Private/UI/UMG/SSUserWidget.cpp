// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/SSUserWidget.h"

#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Utilities/LogCategories.h"



USSUserWidget::USSUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if 0
	AttributesToListenFor.Add(UAS_MyAttributeSet::GetMyAttributeAttribute());

	MyGameplayTag = FGameplayTag::RequestGameplayTag("My.Gameplay.Tag");
	TagsToListenFor.Add(MyGameplayTag);
#endif


}


void USSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


	// Handle calling OnPlayerStateValid():

	if (APlayerController* OwningPlayer = GetOwningPlayer())
	{
		if (OwningPlayer->PlayerState)
		{
			OnPlayerStateValid();
		}
		else
		{
			// Player state was null, so wait for it to be valid (this happens on NM_Client because the PS has to replicate)
			PlayerStateValidTickFunction.Target = this;
			PlayerStateValidTickFunction.RegisterTickFunction(OwningPlayer->GetLevel());
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): OwningPlayer was NULL"), *FString(__FUNCTION__));
	}
}

void FTF_PlayerStateValid::ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
{
	if (Target == nullptr || Target->IsPendingKillOrUnreachable())
	{
		return;
	}

	if (APlayerController* OwningPlayer = Target->GetOwningPlayer())
	{
		// Check if it became valid
		if (OwningPlayer->PlayerState)
		{
			// It became valid so stop checking here
			UnRegisterTickFunction();

			// Call event
			Target->OnPlayerStateValid();

			// Forget about us now
			Target = nullptr;
		}
	}
}

void USSUserWidget::OnPlayerStateValid()
{

	// Handle calling OnPlayerASCValid()

	if (APlayerController* OwningPlayer = GetOwningPlayer())
	{
		if (IAbilitySystemInterface* AbilitySystem = Cast<IAbilitySystemInterface>(OwningPlayer->PlayerState))
		{
			PlayerASC = AbilitySystem->GetAbilitySystemComponent();

			if (PlayerASC)
			{
				OnPlayerASCValid();
			}
			else
			{
				UE_LOG(LogUI, Error, TEXT("%s(): Player State's AbilitySystem returned a NULL Ability System Component"), *FString(__FUNCTION__));
			}
		}
		else
		{
			UE_LOG(LogUI, Error, TEXT("%s(): Cast from Player State to ability system FAILED"), *FString(__FUNCTION__));
		}
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): OwningPlayer was NULL"), *FString(__FUNCTION__));
	}
}

void USSUserWidget::OnPlayerASCValid()
{
	SetUpAttributeListeningFor(PlayerASC);
	SetUpTagListeningFor(PlayerASC);

}

void USSUserWidget::SetUpAttributeListeningFor(UAbilitySystemComponent* ASC)
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

		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &USSUserWidget::OnAttributeChanged);


		FOnAttributeChangeData ChangeData;
		ChangeData.Attribute = Attribute;
		ChangeData.NewValue = ASC->GetNumericAttribute(Attribute);
		ChangeData.OldValue = ChangeData.NewValue;

		OnAttributeChanged(ChangeData); // manually call this so we get the initial attribute value
	}
}
void USSUserWidget::SetUpTagListeningFor(UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		UE_LOG(LogUI, Error, TEXT("%s(): the passed in ASC was NULL"), *FString(__FUNCTION__));
		return;
	}

	for (FGameplayTag Tag : TagsToListenFor)
	{
		if (Tag.IsValid() == false)
		{
			UE_LOG(LogUI, Warning, TEXT("%s(): %s tag was not valid when trying to bind to change delegate"), *FString(__FUNCTION__), *(Tag.GetTagName().ToString()));
			continue;
		}

		ASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange).AddUObject(this, &USSUserWidget::OnTagChanged);

		OnTagChanged(Tag, ASC->GetTagCount(Tag)); // manually call this so we get the initial tag value
	}
}

void USSUserWidget::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


#if 0
	if (Attribute == UAS_MyAttributeSet::GetMyAttributeAttribute()) // check which attribute changed
	{
		SetMyValueForUI(NewValue); // update UI state for this attribute
	}
#endif
}
void USSUserWidget::OnTagChanged(const FGameplayTag Tag, int32 NewCount)
{


#if 0
	if (Tag == FGameplayTag::RequestGameplayTag(MyGameplayTag)) // check which tag changed
	{
		// For tag treated as boolean

		if (NewCount > 0)
		{
			SetMyBoolForUI(true); // update UI state for this tag
		}
		else
		{
			SetMyBoolForUI(false); // update UI state for this tag
		}
	}

	if (Tag == FGameplayTag::RequestGameplayTag(MyGameplayTag)) // check which tag changed
	{
		// For tag counting

		SetMyCountForUI(NewCount); // update UI state for this tag
	}
#endif
}


void USSUserWidget::NativeDestruct()
{
	if (PlayerASC)
	{
		// Stop listening for attribute changes
		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			PlayerASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}

		// Stop listening for tag changes
		for (FGameplayTag Tag : TagsToListenFor)
		{
			PlayerASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange).RemoveAll(this);
		}
	}

	// Ensure our PlayerStateValidTickFunction is unregistered
	PlayerStateValidTickFunction.UnRegisterTickFunction();
	PlayerStateValidTickFunction.Target = nullptr;


	Super::NativeDestruct();
}
