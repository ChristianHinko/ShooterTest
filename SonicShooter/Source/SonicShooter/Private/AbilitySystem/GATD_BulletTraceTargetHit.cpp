// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem\GATD_BulletTraceTargetHit.h"

#include "AbilitySystem\GEC_Shooter.h"
#include "Utilities/LogCategories.h"



FGATD_BulletTraceTargetHit::FGATD_BulletTraceTargetHit()
{

}


void FGATD_BulletTraceTargetHit::AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const
{
	if (FGEC_Shooter* SSContext = static_cast<FGEC_Shooter*>(Context.Get()))
	{
		SSContext->SetBulletTotalTravelDistanceBeforeHit(BulletTotalTravelDistanceBeforeHit);
		SSContext->SetBulletTracePoints(BulletTracePoints);
	}
	else
	{
		UE_LOG(LogGameplayAbilityTargetData, Warning, TEXT("%s() Cast to FSSGameplayEffectContext failed. Bullet specific target data info will not be in our GEEC"), *FString(__FUNCTION__));
	}
}


bool FGATD_BulletTraceTargetHit::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	uint8 RepBits;
	if (Ar.IsSaving())
	{
		// We are a writer, lets find some optimizations and pack them into RepBits


	}

	// Pack/unpack our RepBits into/outof the Archive
	Ar.SerializeBits(&RepBits, 0);
	if (Ar.IsLoading())
	{
		// We are a reader, lets unpack our optimization bools from RepBits

	}


	Ar << BulletTotalTravelDistanceBeforeHit;

	bool bOutSuccessLocal = true;
	bOutSuccessLocal = SafeNetSerializeTArray_WithNetSerialize<31>(Ar, BulletTracePoints, Map);
	bOutSuccess &= bOutSuccessLocal;






	bOutSuccess = true;
	return true;
}
