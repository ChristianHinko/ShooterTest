// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Gun.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "Item/Weapons/AS_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BlueprintFunctionLibraries/BFL_InterfaceHelpers.h"

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

	, OnCurrentBulletSpreadChange(MakeShared<FFloatValueChange>())
	, CurrentBulletSpread(this, FName("CurrentBulletSpread"), OnCurrentBulletSpreadChange)

	, OwnerASC(nullptr)
	, CMC(nullptr)

	, MinBulletSpreadAttribute(UAS_Gun::GetMinBulletSpreadAttribute())
	, MovingBulletSpreadAttribute(UAS_Gun::GetMovingBulletSpreadAttribute())
	, BulletSpreadIncRateAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute())
	, FireBulletSpreadAttribute(UAS_Gun::GetFireBulletSpreadAttribute())
	, BulletSpreadDecSpeedAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute())
{
	CurrentBulletSpread = 0.f;

}

void UO_Gun::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld() == nullptr || GetWorld()->IsGameWorld() == false)
	{
		return;
	}
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}


	// Safe "BeginPlay" logic here

	if (const IAbilitySystemInterface* AbilitySystem = UBFL_InterfaceHelpers::GetInterfaceTypedOuter<IAbilitySystemInterface, UAbilitySystemInterface>(this))
	{
		OwnerASC = AbilitySystem->GetAbilitySystemComponent();
	}

	if (IsValid(OwnerASC))
	{
		if (const FGameplayAbilityActorInfo* ShooterActorInfo = OwnerASC->AbilityActorInfo.Get())
		{
			CMC = Cast<UCharacterMovementComponent>(ShooterActorInfo->MovementComponent.Get());
		}
	}
}


float UO_Gun::GetRestBulletSpread() const
{
	if (!IsValid(OwnerASC))
	{
		return CurrentBulletSpread;
	}

	const float& MinBulletSpread = OwnerASC->GetNumericAttribute(MinBulletSpreadAttribute);
	const float& MovingBulletSpread = OwnerASC->GetNumericAttribute(MovingBulletSpreadAttribute);
	const float& BulletSpreadIncRate = OwnerASC->GetNumericAttribute(BulletSpreadIncRateAttribute);
	const float& FireBulletSpread = OwnerASC->GetNumericAttribute(FireBulletSpreadAttribute);
	const float& BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(BulletSpreadDecSpeedAttribute);

	float RetVal = MinBulletSpread;
	if (IsMovingToIncBulletSpread())
	{
		RetVal = MovingBulletSpread;
	}

	return RetVal;
}

void UO_Gun::ApplyFireBulletSpread()
{
	if (!IsValid(OwnerASC))
	{
		return;
	}

	const float& MinBulletSpread = OwnerASC->GetNumericAttribute(MinBulletSpreadAttribute);
	const float& MovingBulletSpread = OwnerASC->GetNumericAttribute(MovingBulletSpreadAttribute);
	const float& BulletSpreadIncRate = OwnerASC->GetNumericAttribute(BulletSpreadIncRateAttribute);
	const float& FireBulletSpread = OwnerASC->GetNumericAttribute(FireBulletSpreadAttribute);
	const float& BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(BulletSpreadDecSpeedAttribute);

	CurrentBulletSpread = CurrentBulletSpread + FireBulletSpread;

}

bool UO_Gun::IsMovingToIncBulletSpread() const
{
	if (!IsValid(OwnerASC))
	{
		return false;
	}

	const float& MinBulletSpread = OwnerASC->GetNumericAttribute(MinBulletSpreadAttribute);
	const float& MovingBulletSpread = OwnerASC->GetNumericAttribute(MovingBulletSpreadAttribute);
	const float& BulletSpreadIncRate = OwnerASC->GetNumericAttribute(BulletSpreadIncRateAttribute);
	const float& FireBulletSpread = OwnerASC->GetNumericAttribute(FireBulletSpreadAttribute);
	const float& BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(BulletSpreadDecSpeedAttribute);

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

void UO_Gun::Tick(float DeltaTime)
{
	if (!IsValid(OwnerASC))
	{
		return;
	}

	const float& MinBulletSpread = OwnerASC->GetNumericAttribute(MinBulletSpreadAttribute);
	const float& MovingBulletSpread = OwnerASC->GetNumericAttribute(MovingBulletSpreadAttribute);
	const float& BulletSpreadIncRate = OwnerASC->GetNumericAttribute(BulletSpreadIncRateAttribute);
	const float& FireBulletSpread = OwnerASC->GetNumericAttribute(FireBulletSpreadAttribute);
	const float& BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(BulletSpreadDecSpeedAttribute);

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

	float interptedBulletSpread = FMath::FInterpTo(CurrentBulletSpread, GetRestBulletSpread(), DeltaTime, BulletSpreadDecSpeed);
	CurrentBulletSpread = interptedBulletSpread;
	if (CurrentBulletSpread < GetRestBulletSpread())
	{
		CurrentBulletSpread = GetRestBulletSpread();
	}
}
bool UO_Gun::IsTickable() const
{
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
