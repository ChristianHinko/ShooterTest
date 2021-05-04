// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"

#include "UW_Ammo.generated.h"


struct FOnAttributeChangeData;


/**
 * Base ammo widget. No visuals and is meant for subclassing in BP.
 * Provides the value of a ammo attribute values and events for when to update UI.
 */
UCLASS()
class SONICSHOOTER_API UUW_Ammo : public USSUserWidget
{
	GENERATED_BODY()
	
public:
	UUW_Ammo(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		FText ActiveItemName;
	/** The current clip ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		float ClipAmmo;
	/** The current backup ammo value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
		float BackupAmmo;

protected:
	virtual void OnPlayerASCValid();

	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data) override;
	UFUNCTION()
		void OnClipAmmoChange(const float& OldValue, const float& NewValue);

	void SetClipAmmo(float NewClipAmmo);
	void SetBackupAmmo(float NewBackupAmmo);

	/** Called on CurrentSpread changed. Use this to update CurrentSpread based UI */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = "Ammo", meta = (Keywords = "Tick"))
		void UpdateAmmoStatus();
};
