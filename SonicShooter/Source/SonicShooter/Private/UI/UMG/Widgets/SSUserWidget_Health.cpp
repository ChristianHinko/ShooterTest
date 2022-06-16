// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/SSUserWidget_Health.h"

#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"



USSUserWidget_Health::USSUserWidget_Health(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UASSEAttributeSet_Health::GetHealthAttribute());
	AttributesToListenFor.Add(UASSEAttributeSet_Health::GetMaxHealthAttribute());
}


void USSUserWidget_Health::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute& Attribute = Data.Attribute;
	const float& NewValue = Data.NewValue;


	if (Attribute == UASSEAttributeSet_Health::GetHealthAttribute())
	{
		CurrentHealth = NewValue;
		UpdateHealthStatus();
	}
	if (Attribute == UASSEAttributeSet_Health::GetMaxHealthAttribute())
	{
		MaxHealth = NewValue;
		UpdateHealthStatus();
	}
}

void USSUserWidget_Health::UpdateHealthStatus()
{
	// Set our Text Block
	const int CeiledHealth = FMath::CeilToInt(CurrentHealth);
	HealthTextBlock->SetText(FText::AsNumber(CeiledHealth));


	if (MaxHealth <= 0)
	{
		// Avoid division by zero
		HealthProgressBar->SetPercent(0.f);
		return;
	}

	// Set our Progress Bar
	HealthProgressBar->SetPercent(CurrentHealth / MaxHealth);
}
