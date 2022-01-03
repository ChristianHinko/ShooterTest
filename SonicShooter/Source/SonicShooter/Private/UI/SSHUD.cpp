// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHUD.h"



ASSHUD::ASSHUD()
{

}

// Our owner (PlayerController) becomes valid after Super call (but not his player state, so ASSEUserWidgets has an event for when it is).
// THERE IS A NOTICABLE DELAY IF BeginPlay() IS USED INSTEAD OF THIS EVENT SO DO NOT USE IT! There is no benefit to BeginPlay() and the PS is still invalid on it.
// This is the best event to add widgets!
void ASSHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	// NOTE: player state isnt valid right away (but we have event for when it is now in base ASSEUserWidget)

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
