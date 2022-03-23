// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "SSHUD.generated.h"



/**
 * Base HUD class.
 * This class is being treated as a place to manage UUserWidgets (creating or adding and removing them from viewport).
 * But do this in organized sub-classes from this to stay organized and because this is just a base.
 */
UCLASS()
class SONICSHOOTER_API ASSHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASSHUD(const FObjectInitializer& ObjectInitializer);


#if 0
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUW_My> MyWidgetTSub;
	UPROPERTY()
		UUserWidget* MyWidget;

	// Points to an external MyOther Widget
	UPROPERTY()
		TWeakObjectPtr<UUW_MyOther> CurrentMyOtherWidget;
#endif

protected:
	//BEGIN AActor interface
	virtual void PostInitializeComponents() override;
	//END AActor interface

};
