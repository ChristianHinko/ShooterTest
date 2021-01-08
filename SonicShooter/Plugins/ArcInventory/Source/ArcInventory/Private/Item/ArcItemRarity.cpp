// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "Item/ArcItemRarity.h"




UArcItemRarity::UArcItemRarity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RarityName = NSLOCTEXT("RarityColor", "ErrorColor", "Error Color");
	RarityColor = FLinearColor(1, 0, 1);
}
