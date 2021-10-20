// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArcTeam_UIObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, Blueprintable)
class ARCTEAMS_API UArcTeam_UIObject : public UObject
{
	GENERATED_BODY()
public: 
	UArcTeam_UIObject(const FObjectInitializer& ObjectInitializer);
	
};
