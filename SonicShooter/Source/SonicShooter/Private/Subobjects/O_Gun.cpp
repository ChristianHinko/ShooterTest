// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Gun.h"

//#include "Net/UnrealNetwork.h"



//void UO_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//
//	FDoRepLifetimeParams Params;
//	Params.Condition = COND_None;
//	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
//	Params.bIsPushBased = true;
//
//	DOREPLIFETIME_WITH_PARAMS_FAST(UO_Gun, CurrentBulletSpread, Params);
//
//}

UO_Gun::UO_Gun(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OnCurrentBulletSpreadChange(TSharedRef<FFloatValueChange>())
	, CurrentBulletSpread(this, FName("CurrentBulletSpread"), OnCurrentBulletSpreadChange)
{
	CurrentBulletSpread = 0.f;

}


bool UO_Gun::IsTickable() const
{
	return false;
}
void UO_Gun::Tick(float DeltaTime)
{

}
