// Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "FirearmParts/BaseClasses/FPSTemplate_PartSkeletal.h"
#include "FPSTemplate_FlipMount.generated.h"

class UAnimationAsset;

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplate_FlipMount : public AFPSTemplate_PartSkeletal
{
	GENERATED_BODY()
public:
	AFPSTemplate_FlipMount();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimationAsset* FoldedAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimationAsset* OpenAnimation;

	UPROPERTY(ReplicatedUsing = OnRep_IsFolded)
	bool bIsFolded;
	UFUNCTION()
	void OnRep_IsFolded();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetFolded(bool Folded);

public:
	virtual void Use_Implementation() override;
	virtual void DisableRenderTarget(bool Disable) override;

	UFUNCTION(BlueprintPure, Category = "FPSTemplate | FlipMount")
	bool IsFolded() const { return bIsFolded; }
};
