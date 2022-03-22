// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletSpread.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Inventory/Item/Gun/AS_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"



void UO_BulletSpread::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_BulletSpread, CurrentBulletSpread, Params);

}
bool UO_BulletSpread::IsSupportedForNetworking() const
{
	return true;
}
bool UO_BulletSpread::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

UO_BulletSpread::UO_BulletSpread(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

	, CurrentBulletSpread(0.f, this, TEXT("CurrentBulletSpread"))

	, OwnerASC(nullptr)
	, CMC(nullptr)

	, MinBulletSpread(0.f)
	, MovingBulletSpread(0.f)
	, BulletSpreadIncRate(0.f)
	, FireBulletSpread(0.f)
	, BulletSpreadDecSpeed(0.f)
{

}


void UO_BulletSpread::SetAbilitySystemComponent(const UAbilitySystemComponent* NewASC)
{
	// Set the ASC
	OwnerASC = NewASC;

	if (IsValid(OwnerASC))
	{
		// Refresh attribute values
		if (IsValid(OwnerASC))
		{
			MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
			MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
			BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
			FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
			BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());
		}

		// Set our CMC
		if (const FGameplayAbilityActorInfo* ActorInfo = OwnerASC->AbilityActorInfo.Get())
		{
			CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
		}
	}
	else
	{
		MinBulletSpread = 0.f;
		MovingBulletSpread = 0.f;
		BulletSpreadIncRate = 0.f;
		FireBulletSpread = 0.f;
		BulletSpreadDecSpeed = 0.f;

		CMC = nullptr;
	}

	CurrentBulletSpread = FMath::Clamp<float>(CurrentBulletSpread, MinBulletSpread, MovingBulletSpread);
}


float UO_BulletSpread::GetRestBulletSpread() const
{
	float RetVal = MinBulletSpread;
	if (IsMovingToIncBulletSpread())
	{
		RetVal = MovingBulletSpread;
	}

	return RetVal;
}

void UO_BulletSpread::ApplyFireBulletSpread()
{
	CurrentBulletSpread = CurrentBulletSpread + FireBulletSpread;
}

void UO_BulletSpread::ResetBulletSpread()
{
	CurrentBulletSpread = MinBulletSpread;
}

bool UO_BulletSpread::IsMovingToIncBulletSpread() const
{
	if (BulletSpreadIncRate <= 0)
	{
		return false;
	}
	if (!CMC)
	{
		return false;
	}
	if (CMC->IsMovingOnGround() && CMC->GetCurrentAcceleration().SizeSquared() > KINDA_SMALL_NUMBER)
	{
		return true;
	}
	if (CMC->IsFalling())
	{
		return true;
	}

	return false;
}

void UO_BulletSpread::Tick(float DeltaTime)
{
	//UKismetSystemLibrary::PrintString(this, "UAS_Gun::Tick()", true, false);
	if (IsMovingToIncBulletSpread())
	{
		if (CurrentBulletSpread < MovingBulletSpread)
		{
			CurrentBulletSpread = CurrentBulletSpread + (BulletSpreadIncRate * DeltaTime);
			if (CurrentBulletSpread > MovingBulletSpread)
			{
				CurrentBulletSpread = MovingBulletSpread;
			}
			return;
		}
	}

	float InterptedBulletSpread = FMath::FInterpTo(CurrentBulletSpread, GetRestBulletSpread(), DeltaTime, BulletSpreadDecSpeed);
	CurrentBulletSpread = InterptedBulletSpread;
	if (CurrentBulletSpread < GetRestBulletSpread())
	{
		CurrentBulletSpread = GetRestBulletSpread();
	}
}
bool UO_BulletSpread::IsTickable() const
{
	// Refresh attribute values
	if (IsValid(OwnerASC))
	{
		// NOTE: this sets up the members for Tick() as well
		MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());
	}

	// NOTE: this sets up the member for Tick() as well
	CurrentBulletSpread = FMath::Clamp<float>(CurrentBulletSpread, MinBulletSpread, MovingBulletSpread);


	if (IsMovingToIncBulletSpread()/* && CurrentBulletSpread < GetMovingBulletSpread()*/)
	{
		return true;
	}

	// We are above our rest state, return true
	if (CurrentBulletSpread > GetRestBulletSpread())
	{
		return true;
	}

	return false;
}
