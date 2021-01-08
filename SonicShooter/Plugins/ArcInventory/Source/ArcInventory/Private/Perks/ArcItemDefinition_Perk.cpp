// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Perks/ArcItemDefinition_Perk.h"
#include "Perks/ArcItemStack_Perk.h"

UArcItemDefinition_Perk::UArcItemDefinition_Perk()
	: Super()
{
	DefaultItemStackClass = UArcItemStack_Perk::StaticClass();
}
