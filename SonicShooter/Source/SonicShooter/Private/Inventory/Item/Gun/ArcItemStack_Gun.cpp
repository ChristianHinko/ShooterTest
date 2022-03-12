// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/ArcItemStack_Gun.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Subobjects/O_Ammo.h"
#include "Subobjects/O_Gun.h"



void UArcItemStack_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UArcItemStack_Gun, BulletTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UArcItemStack_Gun, BulletInflictEffectTSub, COND_OwnerOnly);
}
bool UArcItemStack_Gun::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// Give AmmoSubobject an opportunity to replicate
	if (IsValid(AmmoSubobject))
	{
		bWroteSomething |= AmmoSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);

		if (AmmoSubobject->IsSupportedForNetworking())
		{
			bWroteSomething |= Channel->ReplicateSubobject(AmmoSubobject, *Bunch, *RepFlags);
		}
	}

	// Give GunSubobject an opportunity to replicate
	if (IsValid(GunSubobject))
	{
		bWroteSomething |= GunSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);

		if (GunSubobject->IsSupportedForNetworking())
		{
			bWroteSomething |= Channel->ReplicateSubobject(GunSubobject, *Bunch, *RepFlags);
		}
	}

	return bWroteSomething;
}

UArcItemStack_Gun::UArcItemStack_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AmmoSubobject = CreateDefaultSubobject<UO_Ammo>(TEXT("AmmoSubobject"));
	GunSubobject = CreateDefaultSubobject<UO_Gun>(TEXT("GunSubobject"));

}
