// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UMG/SSUserWidget.h"
#include "AttributeSet.h"

#include "UW_AttributeBacked.generated.h"


class UAbilitySystemComponent;
struct FOnAttributeChangeData;
class ASSPlayerController;



/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UUW_AttributeBacked : public USSUserWidget
{
	GENERATED_BODY()

public:
	UUW_AttributeBacked();


	TArray<FGameplayAttribute> AttributesToListenFor;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


	UAbilitySystemComponent* PlayerASC;
	ASSPlayerController* SSOwningPlayerController; // only have this for the PS valid delegate

	void OnPlayerStateValid();


	virtual void OnAttributeChanged(const FOnAttributeChangeData& Data);

private:
	void SetUpAttributeListeningFor(UAbilitySystemComponent* ASC);
};
