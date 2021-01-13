// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Perks/ArcItemStack_Perk.h"

#include "Net/UnrealNetwork.h"

UArcItemStack_Perk::UArcItemStack_Perk(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UArcItemStack_Perk::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UArcItemStack_Perk, Modifiers);
}

bool UArcItemStack_Perk::CanAttachTo_Implementation(UArcItemStack* OtherStack)
{
	//Perks can't contain perks
	if (OtherStack->IsA(UArcItemStack_Perk::StaticClass()))
	{
		return false;
	}

	return true;
}
