// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/SSItemStack_Gun.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Subobjects/SSObject_ClipAmmo.h"
#include "Subobjects/SSObject_BulletSpread.h"



void USSItemStack_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USSItemStack_Gun, BulletTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(USSItemStack_Gun, BulletInflictEffectTSub, COND_OwnerOnly);
}
bool USSItemStack_Gun::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
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

USSItemStack_Gun::USSItemStack_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ClipAmmoSubobject = CreateDefaultSubobject<USSObject_ClipAmmo>(TEXT("ClipAmmoSubobject"));
	BulletSpreadSubobject = CreateDefaultSubobject<USSObject_BulletSpread>(TEXT("BulletSpreadSubobject"));

}
