// Copyright 2017-2020 Puny Human, All Rights Reserved.


#include "Item/Definitions/ArcItemDefinition_Active.h"

UArcItemDefinition_Active::UArcItemDefinition_Active()
	: Super()
{

}

void UArcItemDefinition_Active::SetHeldItemMesh_Implementation(UArcItemStack* ItemStack, AActor* ActorToSetup)
{
	TArray<UMeshComponent*> MeshComps;
	IArcHeldItemInterface::Execute_GetHeldMeshComponents(ActorToSetup, MeshComps);

	for (UMeshComponent* Comp : MeshComps)
	{
		if (IsValid(Comp))
		{
			Comp->SetVisibility(true, true);
		}

		//TODO: Forward this to the item definition, because perhaps it has additional ways to set the held item mesh
		if (USkeletalMeshComponent* SkelMesh = Cast<USkeletalMeshComponent>(Comp))
		{
			SkelMesh->SetSkeletalMesh(HeldItemMesh);
		}
		else if (UStaticMeshComponent* StatMesh = Cast<UStaticMeshComponent>(Comp))
		{
			StatMesh->SetStaticMesh(WorldItemModel);
		}
	}
}
