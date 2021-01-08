// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArcInventoryInterface.generated.h"

class UArcInventoryComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UArcInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARCINVENTORY_API IArcInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UArcInventoryComponent* GetInventoryComponent() const = 0;
};
