// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "STAnimInstance.generated.h"



/**
 * Base Animation Instance
 */
UCLASS()
class SHOOTERTEST_API USTAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    USTAnimInstance(const FObjectInitializer& ObjectInitializer);

protected:
#if WITH_EDITORONLY_DATA // ANIMINST_PostCompileValidation
    virtual bool PCV_ShouldWarnAboutNodesNotUsingFastPath() const override
    {
        return true;
    }
    virtual bool PCV_ShouldNotifyAboutNodesNotUsingFastPath() const override
    {
        return true;
    }
#endif // WITH_EDITORONLY_DATA

};
