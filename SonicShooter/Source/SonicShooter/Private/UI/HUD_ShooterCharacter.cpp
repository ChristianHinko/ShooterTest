// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD_ShooterCharacter.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Utilities/LogCategories.h"
#include "UI/UMG/Widgets/UW_Health.h"



AHUD_ShooterCharacter::AHUD_ShooterCharacter()
{

}
void AHUD_ShooterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void AHUD_ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();


	// NOTE: player state isnt valid right away (but we have event for when it is now in base SSUserWidget)

#if 0
	MyWidget = UWidgetBlueprintLibrary::Create(this, MyWidgetTSub, GetOwningPlayerController());
	if (MyWidget)
	{
		MyWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): Failed to create MyWidget. Ensure to fill out TSubs in BP"), *FString(__FUNCTION__));
	}
#endif

	HealthWidget = UWidgetBlueprintLibrary::Create(this, HealthWidgetTSub, GetOwningPlayerController());
	if (HealthWidget)
	{
		HealthWidget->AddToViewport();
	}
	else
	{
		UE_LOG(LogUI, Error, TEXT("%s(): Failed to create HealthWidget. Ensure to fill out TSubs in BP"), *FString(__FUNCTION__));
	}
}
