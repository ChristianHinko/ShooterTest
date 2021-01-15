// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Poolable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPoolable : public UInterface
{
	GENERATED_BODY()
};




class ASSActor;

/**
 * 
 */
class SONICSHOOTER_API IPoolable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	IPoolable();
	// This is set automatically by the interface. You shouldn't touch this
	uint8 bIsCurentlyInPool : 1;

	/** Make sure to call super when overriding */
	virtual void OnPooled();
	/** Make sure to call super when overriding */
	virtual void OnUnpooled();

	/** You can assure this will be called whenever this actor gets spawned or activated from the pool. Like BeginPlay() but works for pooled objects */
	virtual void StartLogic();
	/** You can assure this will be called whenever this actor gets deactivated to the pool. (One thing to note is this doesn't get called before destruction) */
	virtual void EndLogic();
};
