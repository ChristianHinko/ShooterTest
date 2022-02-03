// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/O_Gun.h"

#include "Net/UnrealNetwork.h"
#include "BlueprintFunctionLibraries/BFL_InterfaceHelpers.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Types/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Item/Weapons/AS_Gun.h"
#include "GameFramework/CharacterMovementComponent.h"



void UO_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_OnChanged;
	Params.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UO_Gun, CurrentBulletSpread, Params);

}
bool UO_Gun::IsSupportedForNetworking() const
{
	return true;
}
bool UO_Gun::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = false;

	return bWroteSomething;
}

UO_Gun::UO_Gun(const FObjectInitializer& ObjectInitializer)
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
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMinBulletSpreadAttribute()).AddUObject(this, &UO_Gun::OnMinBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMovingBulletSpreadAttribute()).AddUObject(this, &UO_Gun::OnMovingBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadIncRateAttribute()).AddUObject(this, &UO_Gun::OnBulletSpreadIncRateChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetFireBulletSpreadAttribute()).AddUObject(this, &UO_Gun::OnFireBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadDecSpeedAttribute()).AddUObject(this, &UO_Gun::OnBulletSpreadDecSpeedChange);

		if (const FGameplayAbilityActorInfo* ActorInfo = OwnerASC->AbilityActorInfo.Get())
		{
			CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());

			if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(ActorInfo))
			{
				USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
				if (IsValid(InventoryComponent))
				{
					InventoryComponent->OnItemActive.AddDynamic(this, &UO_Gun::OnItemActive);
					InventoryComponent->OnItemActive.AddDynamic(this, &UO_Gun::OnItemInactive);
				}
			}
		}
	}
}

void UO_Gun::OnItemActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	if (IsValid(OwnerASC))
	{
		// Refresh attribute values
		MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());
	}

	ResetBulletSpread();
}
void UO_Gun::OnItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	if (IsValid(OwnerASC))
	{
		// Refresh attribute values
		MinBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMinBulletSpreadAttribute());
		MovingBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetMovingBulletSpreadAttribute());
		BulletSpreadIncRate = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadIncRateAttribute());
		FireBulletSpread = OwnerASC->GetNumericAttribute(UAS_Gun::GetFireBulletSpreadAttribute());
		BulletSpreadDecSpeed = OwnerASC->GetNumericAttribute(UAS_Gun::GetBulletSpreadDecSpeedAttribute());
	}

	ResetBulletSpread();
}


float UO_Gun::GetRestBulletSpread() const
{
	float RetVal = MinBulletSpread;
	if (IsMovingToIncBulletSpread())
	{
		RetVal = MovingBulletSpread;
	}

	return RetVal;
}

void UO_Gun::ApplyFireBulletSpread()
{
	CurrentBulletSpread = CurrentBulletSpread + FireBulletSpread;
}

void UO_Gun::ResetBulletSpread()
{
	CurrentBulletSpread = MinBulletSpread;
}

bool UO_Gun::IsMovingToIncBulletSpread() const
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

void UO_Gun::Tick(float DeltaTime)
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
