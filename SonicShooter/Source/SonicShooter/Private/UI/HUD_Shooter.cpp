// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD_Shooter.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Utilities/LogCategories.h"
#include "UI/UMG/Widgets/UW_Health.h"



AHUD_Shooter::AHUD_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AHUD_Shooter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	// NOTE: player state isnt valid right away (but we have event for when it is now in base ASSEUserWidget)

	HealthWidget = UWidgetBlueprintLibrary::Create(this, HealthWidgetTSub, GetOwningPlayerController());
	if (IsValid(HealthWidget))
	{
		HealthWidget->AddToPlayerScreen();
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): Failed to create HealthWidget. Ensure to fill out TSubs in BP"), ANSI_TO_TCHAR(__FUNCTION__));
	}
}
