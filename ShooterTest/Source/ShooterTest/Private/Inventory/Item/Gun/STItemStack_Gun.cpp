// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item/Gun/STItemStack_Gun.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Subobjects/STObject_ClipAmmo.h"
#include "Subobjects/STObject_BulletSpread.h"



void USTItemStack_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USTItemStack_Gun, BulletTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(USTItemStack_Gun, BulletInflictEffectTSub, COND_OwnerOnly);
}
bool USTItemStack_Gun::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
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

USTItemStack_Gun::USTItemStack_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ClipAmmoSubobject = CreateDefaultSubobject<USTObject_ClipAmmo>(TEXT("ClipAmmoSubobject"));
	BulletSpreadSubobject = CreateDefaultSubobject<USTObject_BulletSpread>(TEXT("BulletSpreadSubobject"));

}
