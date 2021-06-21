// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "SSAnimInstance.generated.h"



/**
 * Base Animation Instance
 */
UCLASS()
class SONICSHOOTER_API USSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USSAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool PCV_ShouldWarnAboutNodesNotUsingFastPath() const override
	{
		return true;
	}
	virtual bool PCV_ShouldNotifyAboutNodesNotUsingFastPath() const override
	{
		return true;
	}

};
