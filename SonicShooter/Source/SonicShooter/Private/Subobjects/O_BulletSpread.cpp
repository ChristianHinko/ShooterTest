// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_BulletSpread.h"

#include "Net/UnrealNetwork.h"
#include "BlueprintFunctionLibraries/BFL_InterfaceHelpers.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
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

	, OnCurrentBulletSpreadChange(MakeShared<FFloatValueChange>())
	, CurrentBulletSpread(0.f, this, FName("CurrentBulletSpread"), OnCurrentBulletSpreadChange)

	, OwnerASC(nullptr)
	, CMC(nullptr)

	, MinBulletSpread(0.f)
	, MovingBulletSpread(0.f)
	, BulletSpreadIncRate(0.f)
	, FireBulletSpread(0.f)
	, BulletSpreadDecSpeed(0.f)
{

}


void UO_BulletSpread::SetAbilitySystemComponent(UAbilitySystemComponent* NewASC)
{
	// Keep track of the old ASC
	UAbilitySystemComponent* const OldASC = OwnerASC;

	// Set the ASC
	OwnerASC = NewASC;

	// Handle changed
	if (OldASC != OwnerASC)
	{
		if (IsValid(OldASC))
		{
			// Unbind from change delegates
			OldASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMinBulletSpreadAttribute()).RemoveAll(this);
			OldASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMovingBulletSpreadAttribute()).RemoveAll(this);
			OldASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadIncRateAttribute()).RemoveAll(this);
			OldASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetFireBulletSpreadAttribute()).RemoveAll(this);
			OldASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadDecSpeedAttribute()).RemoveAll(this);
		}
		
		if (IsValid(OwnerASC))
		{
			// Bind to change delegates
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMinBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnMinBulletSpreadChange);
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMovingBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnMovingBulletSpreadChange);
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadIncRateAttribute()).AddUObject(this, &UO_BulletSpread::OnBulletSpreadIncRateChange);
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetFireBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnFireBulletSpreadChange);
			OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadDecSpeedAttribute()).AddUObject(this, &UO_BulletSpread::OnBulletSpreadDecSpeedChange);

			// Get initial values
			MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
			MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
			BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
			FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
			BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());


			// Set our CMC
			if (const FGameplayAbilityActorInfo* ActorInfo = OwnerASC->AbilityActorInfo.Get())
			{
				CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());
			}
		}
		else
		{
			CMC = nullptr;
		}
	}

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
	// Refresh attribute values
	if (IsValid(OwnerASC))
	{
		MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());
	}

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

	float interptedBulletSpread = FMath::FInterpTo(CurrentBulletSpread, GetRestBulletSpread(), DeltaTime, BulletSpreadDecSpeed);
	CurrentBulletSpread = interptedBulletSpread;
	if (CurrentBulletSpread < GetRestBulletSpread())
	{
		CurrentBulletSpread = GetRestBulletSpread();
	}
}
bool UO_BulletSpread::IsTickable() const
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







void UO_BulletSpread::BeginDestroy()
{
	// BEGIN Unbind from attribute value change delegates
	if (IsValid(OwnerASC))
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMinBulletSpreadAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMovingBulletSpreadAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadIncRateAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetFireBulletSpreadAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadDecSpeedAttribute()).RemoveAll(this);
	}
	// END Unbind from attribute value change delegates


	Super::BeginDestroy();
}
