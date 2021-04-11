// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD_ShooterCharacter.h"

#include "Blueprint/WidgetBlueprintLibrary.h"



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

	//MyWidget = UWidgetBlueprintLibrary::Create(this, MyWidgetTSub, GetOwningPlayerController());
	//MyWidget->AddToViewport();
}
