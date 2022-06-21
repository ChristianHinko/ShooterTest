// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHUD_Shooter.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/UMG/Widgets/SSUserWidget_Health.h"



ASSHUD_Shooter::ASSHUD_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ASSHUD_Shooter::PostInitializeComponents()
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
		UE_LOG(LogSSUI, Error, TEXT("%s(): Failed to create HealthWidget. Ensure to fill out TSubs in BP"), ANSI_TO_TCHAR(__FUNCTION__));
	}
}
