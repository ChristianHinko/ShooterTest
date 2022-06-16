// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/SSObject_BulletSpread.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "Inventory/Item/Gun/SSAttributeSet_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"



void USSObject_BulletSpread::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(USSObject_BulletSpread, CurrentBulletSpread, Params);

}
bool USSObject_BulletSpread::IsSupportedForNetworking() const
{
	return true;
}
bool USSObject_BulletSpread::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

USSObject_BulletSpread::USSObject_BulletSpread(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)

	, CurrentBulletSpread(this, TEXT("CurrentBulletSpread"), 0.f)

	, OwnerASC(nullptr)
	, CMC(nullptr)

	, MinBulletSpread(0.f)
	, MovingBulletSpread(0.f)
	, BulletSpreadIncRate(0.f)
	, FireBulletSpread(0.f)
	, BulletSpreadDecSpeed(0.f)
{

}


void USSObject_BulletSpread::SetAbilitySystemComponent(const UAbilitySystemComponent* NewASC)
{
	// Set the ASC
	OwnerASC = NewASC;

	if (const UAbilitySystemComponent* ASC = OwnerASC.Get())
	{
		// Refresh attribute values
		MinBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute());

		// Set our CMC
		if (const FGameplayAbilityActorInfo* ActorInfo = ASC->AbilityActorInfo.Get())
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


float USSObject_BulletSpread::GetRestBulletSpread() const
{
	float RetVal = MinBulletSpread;
	if (IsMovingToIncBulletSpread())
	{
		RetVal = MovingBulletSpread;
	}

	return RetVal;
}

void USSObject_BulletSpread::ApplyFireBulletSpread()
{
	CurrentBulletSpread = CurrentBulletSpread + FireBulletSpread;
}

void USSObject_BulletSpread::ResetBulletSpread()
{
	CurrentBulletSpread = MinBulletSpread;
}

bool USSObject_BulletSpread::IsMovingToIncBulletSpread() const
{
	if (BulletSpreadIncRate <= 0)
	{
		return false;
	}
	if (!CMC.IsValid())
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

void USSObject_BulletSpread::Tick(float DeltaTime)
{
	//UKismetSystemLibrary::PrintString(this, "USSAttributeSet_Gun::Tick()", true, false);
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
bool USSObject_BulletSpread::IsTickable() const
{
	// Refresh attribute values
	if (const UAbilitySystemComponent* ASC = OwnerASC.Get())
	{
		// NOTE: this sets up the members for Tick() as well
		MinBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = ASC->GetNumericAttribute(USSAttributeSet_Gun::GetBulletSpreadDecSpeedAttribute());
	}

	if (CurrentBulletSpread < MinBulletSpread)
	{
		// NOTE: this sets up the member for Tick() as well
		CurrentBulletSpread = MinBulletSpread;
	}


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
