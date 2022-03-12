// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/ArcItemStack_Gun.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Subobjects/O_ClipAmmo.h"
#include "Subobjects/O_BulletSpread.h"



void UArcItemStack_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UArcItemStack_Gun, BulletTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UArcItemStack_Gun, BulletInflictEffectTSub, COND_OwnerOnly);
}
bool UArcItemStack_Gun::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// Give ClipAmmoSubobject an opportunity to replicate
	if (IsValid(ClipAmmoSubobject))
	{
		bWroteSomething |= ClipAmmoSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);

		if (ClipAmmoSubobject->IsSupportedForNetworking())
		{
			bWroteSomething |= Channel->ReplicateSubobject(ClipAmmoSubobject, *Bunch, *RepFlags);
		}
	}

	// Give BulletSpreadSubobject an opportunity to replicate
	if (IsValid(BulletSpreadSubobject))
	{
		bWroteSomething |= BulletSpreadSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);

		if (BulletSpreadSubobject->IsSupportedForNetworking())
		{
			bWroteSomething |= Channel->ReplicateSubobject(BulletSpreadSubobject, *Bunch, *RepFlags);
		}
	}

	return bWroteSomething;
}

UArcItemStack_Gun::UArcItemStack_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ClipAmmoSubobject = CreateDefaultSubobject<UO_ClipAmmo>(TEXT("ClipAmmoSubobject"));
	BulletSpreadSubobject = CreateDefaultSubobject<UO_BulletSpread>(TEXT("BulletSpreadSubobject"));

}
