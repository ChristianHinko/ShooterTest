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

void UO_BulletSpread::PostInitProperties()
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
		// TODO: right now this is referencing the AIAbilitySystemComponent on the client :(
		OwnerASC = AbilitySystem->GetAbilitySystemComponent();
	}

	if (IsValid(OwnerASC))
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMinBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnMinBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetMovingBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnMovingBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadIncRateAttribute()).AddUObject(this, &UO_BulletSpread::OnBulletSpreadIncRateChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetFireBulletSpreadAttribute()).AddUObject(this, &UO_BulletSpread::OnFireBulletSpreadChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Gun::GetBulletSpreadDecSpeedAttribute()).AddUObject(this, &UO_BulletSpread::OnBulletSpreadDecSpeedChange);

		if (const FGameplayAbilityActorInfo* ActorInfo = OwnerASC->AbilityActorInfo.Get())
		{
			CMC = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent.Get());

			if (const FGAAI_Shooter* ShooterActorInfo = static_cast<const FGAAI_Shooter*>(ActorInfo))
			{
				USSArcInventoryComponent_Active* InventoryComponent = ShooterActorInfo->GetInventoryComponent();
				if (IsValid(InventoryComponent))
				{
					InventoryComponent->OnItemActive.AddDynamic(this, &UO_BulletSpread::OnItemActive);
					InventoryComponent->OnItemActive.AddDynamic(this, &UO_BulletSpread::OnItemInactive);
				}
			}
		}
	}
}

void UO_BulletSpread::OnItemActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
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
void UO_BulletSpread::OnItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
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
