// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/GunStack.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Subobjects/O_Ammo.h"
#include "Subobjects/O_Gun.h"



void UGunStack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UGunStack, BulletTraceTargetActorTSub, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UGunStack, BulletHitEffectTSub, COND_OwnerOnly);
}
bool UGunStack::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// Give AmmoSubobject an opportunity to replicate
	if (AmmoSubobject->IsSupportedForNetworking())
	{
		bWroteSomething |= Channel->ReplicateSubobject(AmmoSubobject, *Bunch, *RepFlags);
		bWroteSomething |= AmmoSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	// Give GunSubobject an opportunity to replicate
	if (GunSubobject->IsSupportedForNetworking())
	{
		bWroteSomething |= Channel->ReplicateSubobject(GunSubobject, *Bunch, *RepFlags);
		bWroteSomething |= GunSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	return bWroteSomething;
}

UGunStack::UGunStack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AmmoSubobject = CreateDefaultSubobject<UO_Ammo>(TEXT("AmmoSubobject"));
	GunSubobject = CreateDefaultSubobject<UO_Gun>(TEXT("GunSubobject"));

}

