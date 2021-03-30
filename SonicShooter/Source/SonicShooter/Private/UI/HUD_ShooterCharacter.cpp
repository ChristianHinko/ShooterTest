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


	// NOTE: last time i tried using begin play for spawning a widget i got weirdness happening with the owning PC but give it a try anyways

	//MyWidget = UWidgetBlueprintLibrary::Create(this, MyWidgetTSub, GetOwningPlayerController());
	//MyWidget->AddToViewport();
}
