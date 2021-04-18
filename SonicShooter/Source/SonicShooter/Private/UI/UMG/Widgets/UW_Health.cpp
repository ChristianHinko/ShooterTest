// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_Health.h"

#include "AbilitySystem/AttributeSets/AS_Health.h"



UUW_Health::UUW_Health(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttributesToListenFor.Add(UAS_Health::GetHealthAttribute());
}


void UUW_Health::OnAttributeChanged(const FOnAttributeChangeData& Data)
{
	const FGameplayAttribute Attribute = Data.Attribute;
	const float NewValue = Data.NewValue;


	if (Attribute == UAS_Health::GetHealthAttribute())
	{
		SetCurrentHealth(NewValue);
	}
}

void UUW_Health::SetCurrentHealth(float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;
	UpdateHealthStatus();
}
