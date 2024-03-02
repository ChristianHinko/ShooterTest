// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/STUserWidget_Health.h"

#include "AttributeSets/ASSEAttributeSet_Health.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"



USTUserWidget_Health::USTUserWidget_Health(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}


void USTUserWidget_Health::OnPlayerASCValid()
{
    // Get and bind to updates for Health
    CurrentHealth = PlayerASC->GetNumericAttribute(UASSEAttributeSet_Health::GetHealthAttribute());
    UpdateHealthStatus();
    PlayerASC->GetGameplayAttributeValueChangeDelegate(UASSEAttributeSet_Health::GetHealthAttribute()).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data)
        {
            CurrentHealth = Data.NewValue;
            UpdateHealthStatus();
        }
    );

    // Get and bind to updates for MaxHealth
    MaxHealth = PlayerASC->GetNumericAttribute(UASSEAttributeSet_Health::GetMaxHealthAttribute());
    UpdateHealthStatus();
    PlayerASC->GetGameplayAttributeValueChangeDelegate(UASSEAttributeSet_Health::GetMaxHealthAttribute()).AddWeakLambda(this, [&](const FOnAttributeChangeData& Data)
        {
            MaxHealth = Data.NewValue;
            UpdateHealthStatus();
        }
    );
}

void USTUserWidget_Health::UpdateHealthStatus()
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
