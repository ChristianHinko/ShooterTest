// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "SSUserWidget_Ammo.generated.h"


struct FOnAttributeChangeData;
class USSObject_ClipAmmo;
class UTextBlock;



/**
 * Base ammo widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a ammo attribute values and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API USSUserWidget_Ammo : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UTextBlock> ClipAmmoText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UTextBlock> BackupAmmoText;
	
public:
	USSUserWidget_Ammo(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		FText ActiveItemName;
	/** The current clip ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		float CurrentClipAmmo;
	/** The current backup ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		float CurrentBackupAmmo;

protected:
	virtual void NativeDestruct() override;


	virtual void OnPlayerASCValid() override;
	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data) override;

	UPROPERTY()
		TWeakObjectPtr<USSObject_ClipAmmo> ClipAmmoSubobject;
	UFUNCTION()
		void OnClipAmmoChange(const float& OldValue, const float& NewValue);

	/** Called on ammo values changed. Use this to update UI */
	UFUNCTION()
		void UpdateAmmoStatus();

};
