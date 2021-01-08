// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArcHeldItemInterface.generated.h"

class UMeshComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArcHeldItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARCINVENTORY_API IArcHeldItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void GetHeldMeshComponents(TArray<UMeshComponent*>& OutMeshComponents);
	virtual void GetHeldMeshComponents_Implementation(TArray<UMeshComponent*>& OutMeshComponents);
	
};
