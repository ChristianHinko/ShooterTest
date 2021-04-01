// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AS_Gun.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystem/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Character/SSCharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MinBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MovingBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadIncPerShot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadMovingIncRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadDecSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, DamageFalloff, COND_None, REPNOTIFY_Always);
}

UAS_Gun::UAS_Gun()
	: MinBulletSpread(10.f),
	MovingBulletSpread(20.f),
	BulletSpreadIncPerShot(50.f),
	BulletSpreadMovingIncRate(70.f),
	BulletSpreadDecSpeed(15.f),
	DamageFalloff(.5f)
{
	SetSoftAttributeDefaults();




}

void UAS_Gun::SetSoftAttributeDefaults()
{
	Super::SetSoftAttributeDefaults();


	CurrentBulletSpread = GetMinBulletSpread();
}

void UAS_Gun::PostInitProperties()
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
	//---------------------------------------- safe "BeginPlay" logic here ------------------------



	UpdateFromActorInfo();

	if (FSSGameplayAbilityActorInfo* SSActorInfo = static_cast<FSSGameplayAbilityActorInfo*>(GetActorInfo()))
	{
		SSActorInfo->OnInited.AddUObject(this, &UAS_Gun::OnActorInfoInited);
	}
}

void UAS_Gun::OnActorInfoInited()
{
	UpdateFromActorInfo();
}

void UAS_Gun::UpdateFromActorInfo()
{
	if (Inventory)
	{
		Inventory->OnItemActive.RemoveAll(this);
		Inventory->OnItemInactive.RemoveAll(this);
	}
	if (CMC)
	{
		CMC->OnAccelerationStart.RemoveAll(this);
		CMC->OnAccelerationStop.RemoveAll(this);

		CMC->OnStartedFalling.RemoveAll(this);
		CMC->OnStoppedFalling.RemoveAll(this);
	}


	if (const FSSGameplayAbilityActorInfo* const SSActorInfo = static_cast<const FSSGameplayAbilityActorInfo* const>(GetActorInfo()))
	{
		Inventory = SSActorInfo->GetInventoryComponent();
		CMC = SSActorInfo->GetSSCharacterMovementComponent();
	}

	if (Inventory)
	{
		Inventory->OnItemActive.AddDynamic(this, &UAS_Gun::OnInventoryItemActive);
		Inventory->OnItemInactive.AddDynamic(this, &UAS_Gun::OnInventoryItemInactive);
	}

	if (CMC)
	{
		CMC->OnAccelerationStart.AddUObject(this, &UAS_Gun::OnAccelerationStartCMC);
		CMC->OnAccelerationStop.AddUObject(this, &UAS_Gun::OnAccelerationStopCMC);

		CMC->OnStartedFalling.AddUObject(this, &UAS_Gun::OnStartedFallingCMC);
		CMC->OnStoppedFalling.AddUObject(this, &UAS_Gun::OnStoppedFallingCMC);
	}
}

void UAS_Gun::OnInventoryItemActive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	if (GetOwningAbilitySystemComponent()->HasAttributeSetForAttribute(GetCurrentBulletSpreadAttribute()))
	{
		SetCurrentBulletSpread(GetMinBulletSpread());
		//UKismetSystemLibrary::PrintString(this, "RESETED", true, false, FLinearColor::Yellow);
	}
}
void UAS_Gun::OnInventoryItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	if (GetOwningAbilitySystemComponent()->HasAttributeSetForAttribute(GetCurrentBulletSpreadAttribute()))
	{
		SetCurrentBulletSpread(GetMinBulletSpread());
		//UKismetSystemLibrary::PrintString(this, "RESETED", true, false, FLinearColor::Yellow);
	}
}

float UAS_Gun::GetRestBulletSpread() const
{
	float RetVal = GetMinBulletSpread();
	if (IsMovingToIncBulletSpread())
	{
		RetVal = GetMovingBulletSpread();
	}

	return RetVal;
}

void UAS_Gun::FireBulletSpread()
{
	SetCurrentBulletSpread(GetCurrentBulletSpread() + GetBulletSpreadIncPerShot());
}

bool UAS_Gun::IsMovingToIncBulletSpread() const
{
	if (GetBulletSpreadMovingIncRate() <= 0)
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

void UAS_Gun::Tick(float DeltaTime)
{
	//UKismetSystemLibrary::PrintString(this, "UAS_Gun::Tick()", true, false);
	if (IsMovingToIncBulletSpread())
	{
		if (GetCurrentBulletSpread() < GetMovingBulletSpread())
		{
			SetCurrentBulletSpread(GetCurrentBulletSpread() + (GetBulletSpreadMovingIncRate() * DeltaTime));
			if (GetCurrentBulletSpread() > GetMovingBulletSpread())
			{
				SetCurrentBulletSpread(GetMovingBulletSpread());
			}
			return;
		}
	}

	float interptedBulletSpread = FMath::FInterpTo(GetCurrentBulletSpread(), GetRestBulletSpread(), DeltaTime, GetBulletSpreadDecSpeed());
	SetCurrentBulletSpread(interptedBulletSpread);
	if (GetCurrentBulletSpread() < GetRestBulletSpread())
	{
		SetCurrentBulletSpread(GetRestBulletSpread());
	}
}
bool UAS_Gun::ShouldTick() const
{
	if (IsMovingToIncBulletSpread()/* && GetCurrentBulletSpread() < GetMovingBulletSpread()*/)
	{
		return true;
	}

	// We are above our rest state, return true
	if (GetCurrentBulletSpread() > GetRestBulletSpread())
	{
		return true;
	}

	return false;
}

void UAS_Gun::OnAccelerationStartCMC()
{
	if (IsMovingToIncBulletSpread() == false)
	{
		return;
	}

	GetOwningAbilitySystemComponent()->UpdateShouldTick();
}
void UAS_Gun::OnAccelerationStopCMC()
{
	if (IsMovingToIncBulletSpread() == false)
	{
		return;
	}

	GetOwningAbilitySystemComponent()->UpdateShouldTick();
}

void UAS_Gun::OnStartedFallingCMC()
{
	if (IsMovingToIncBulletSpread() == false)
	{
		return;
	}

	GetOwningAbilitySystemComponent()->UpdateShouldTick();
}
void UAS_Gun::OnStoppedFallingCMC()
{
	if (IsMovingToIncBulletSpread() == false)
	{
		return;
	}

	GetOwningAbilitySystemComponent()->UpdateShouldTick();
}


// OnReps:


void UAS_Gun::OnRep_MinBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MinBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_MovingBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MovingBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadMovingIncRate(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadMovingIncRate, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadIncPerShot(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadIncPerShot, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadDecSpeed, ServerBaseValue);
}

void UAS_Gun::OnRep_DamageFalloff(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, DamageFalloff, ServerBaseValue);
}
