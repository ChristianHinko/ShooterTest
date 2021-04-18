// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHUD.h"



ASSHUD::ASSHUD()
{

}

// Our owner (PlayerController) becomes valid after Super call (but not his player state, so SSUserWidgets have an event for that. The PS is not valid on BeginPlayer either)
void ASSHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();


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
}
