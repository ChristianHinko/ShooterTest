// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ASSEUserWidget.h"

#include "UW_Ammo.generated.h"


struct FOnAttributeChangeData;
class UO_ClipAmmo;
class UTextBlock;



/**
 * Base ammo widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a ammo attribute values and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_Ammo : public UASSEUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* ClipAmmoText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* BackupAmmoText;
	
public:
	UUW_Ammo(const FObjectInitializer& ObjectInitializer);


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
		TWeakObjectPtr<UO_ClipAmmo> ClipAmmoSubobject;
	UFUNCTION()
		void OnClipAmmoChange(const float& OldValue, const float& NewValue);

	/** Called on ammo values changed. Use this to update UI */
	UFUNCTION()
		void UpdateAmmoStatus();

};
