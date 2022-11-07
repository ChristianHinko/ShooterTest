// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "STUserWidget_Ammo.generated.h"


class USTObject_ClipAmmo;
class UTextBlock;



/**
 * Base ammo widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a ammo attribute values and events for when to update UI.
 */
UCLASS()
class SHOOTERTEST_API USTUserWidget_Ammo : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UTextBlock> ClipAmmoText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		TObjectPtr<UTextBlock> BackupAmmoText;
	
public:
	USTUserWidget_Ammo(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		FText ActiveItemName;
	/** The current clip ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		int32 CurrentClipAmmo;
	/** The current backup ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		float CurrentBackupAmmo;

protected:
	virtual void NativeDestruct() override;

	virtual void OnPlayerASCValid() override;

	UPROPERTY()
		TWeakObjectPtr<USTObject_ClipAmmo> ClipAmmoSubobject;
	UFUNCTION()
		void OnClipAmmoChange(const int32& OldValue, const int32& NewValue);

	/** Called on ammo values changed. Use this to update UI */
	UFUNCTION()
		void UpdateAmmoStatus();

};
