// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/USSArcItemBPFunctionLibrary.h"

#include "Inventory\SSArcItemStackWorldObject.h"
#include "Kismet/GameplayStatics.h"

class ASSArcItemStackWorldObject* USSArcItemBPFunctionLibrary::SpawnWorldItem(UObject* WorldContextObject, UArcItemStack* ItemStack, const FTransform& Transform, TSubclassOf<AArcItemStackWorldObject> StackWorldObjectClass)
{
	UWorld* World = WorldContextObject->GetWorld();

	if (IsValid(World))
	{
		ASSArcItemStackWorldObject* StackObject = World->SpawnActorDeferred<ASSArcItemStackWorldObject>(StackWorldObjectClass, Transform);
		if (IsValid(StackObject))
		{
			StackObject->SetInventoryStack(ItemStack);
			UGameplayStatics::FinishSpawningActor(StackObject, Transform);
			return StackObject;
		}
	}
	return nullptr;
}