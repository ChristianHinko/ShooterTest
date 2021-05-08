// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem\GATD_BulletTraceTargetHit.h"

#include "AbilitySystem\GEC_Shooter.h"
#include "Utilities/LogCategories.h"



void FGATD_BulletTraceTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const
{
	if (FGEC_Shooter* SSContext = static_cast<FGEC_Shooter*>(Context.Get()))
	{
		SSContext->SetBulletTotalTravelDistanceBeforeHit(bulletTotalTravelDistanceBeforeHit);
		SSContext->SetRicochetsBeforeHit(ricochetsBeforeHit);
	}
	else
	{
		UE_LOG(LogGameplayAbilityTargetData, Warning, TEXT("%s() Cast to FSSGameplayEffectContext failed. Bullet specific target data info will not be in our GEEC"), *FString(__FUNCTION__));
	}
}


bool FGATD_BulletTraceTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	HitResult.NetSerialize(Ar, Map, bOutSuccess);


	uint32 RepBits = 0;
	if (Ar.IsSaving())
	{
		RepBits |= 1 << 0;
		RepBits |= 1 << 1;
	}
    Ar.SerializeBits(&RepBits, 2);	// Kaos wouldv used 1 here (based on how he did it with the effect context net serialize) but we get disconnected when we hit someone in game if it's 1. My guess is 1 is not big enough of a length (which makes sense to me since we have 2 bits but idk)


	//	I have a feeling these if checks before archiving is for when you want to send something to the server. I think if it is the server replicating to the client, then you don't do these checks but idk.
	if (RepBits & (1 << 0))
	{
		Ar << bulletTotalTravelDistanceBeforeHit;
	}
	if (RepBits & (1 << 1))
	{
		Ar << ricochetsBeforeHit;
	}
	

	return true;
}