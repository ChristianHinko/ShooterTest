// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "ArcInventoryDeveloperSettings.h"
#include "ArcItemStack.h"
#include "Item/ArcItemStackWorldObject.h"



UArcInventoryDeveloperSettings::UArcInventoryDeveloperSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultItemStackClass = UArcItemStack::StaticClass();
	ItemStackWorldObjectClass = AArcItemStackWorldObject::StaticClass();

}
