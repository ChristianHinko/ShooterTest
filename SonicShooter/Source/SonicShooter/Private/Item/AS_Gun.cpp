// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AS_Gun.h"

#include "Net/UnrealNetwork.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystem/SSGameplayAbilityTypes.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Character/SSCharacterMovementComponent.h"



void UAS_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MinBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MaxBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadIncPerShot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadMovingIncRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadDecSpeed, COND_None, REPNOTIFY_Always);
}

UAS_Gun::UAS_Gun()
	: MinBulletSpread(10.f),
	MaxBulletSpread(20.f),
	BulletSpreadIncPerShot(50.f),
	BulletSpreadMovingIncRate(50.f),
	BulletSpreadDecSpeed(10.f)
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


	// TODO: this doesnt work on the client for the first weapon (i think its using the AI ASC when he hits this or something)
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


void UAS_Gun::IncCurrentBulletSpread()
{
	SetCurrentBulletSpread(GetCurrentBulletSpread() + GetBulletSpreadIncPerShot());
	//if (GetCurrentBulletSpread() > GetMaxBulletSpread())
	//{
	//	SetCurrentBulletSpread(GetMaxBulletSpread());
	//}

	//UKismetSystemLibrary::PrintString(this, "Current bullet spread: " + FString::SanitizeFloat(GetCurrentBulletSpread()), true, false);
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
	if (IsMovingToIncBulletSpread())
	{
		SetCurrentBulletSpread(GetCurrentBulletSpread() + (GetBulletSpreadMovingIncRate() * DeltaTime));
		if (GetCurrentBulletSpread() > GetMaxBulletSpread())
		{
			SetCurrentBulletSpread(GetMaxBulletSpread());
		}
		//UKismetSystemLibrary::PrintString(this, "Current bullet spread: " + FString::SanitizeFloat(GetCurrentBulletSpread()), true, false);
		return;
	}

	float interptedBulletSpread = FMath::FInterpTo(GetCurrentBulletSpread(), GetMinBulletSpread(), DeltaTime, GetBulletSpreadDecSpeed());
	SetCurrentBulletSpread(interptedBulletSpread);
	if (GetCurrentBulletSpread() < GetMinBulletSpread())
	{
		SetCurrentBulletSpread(GetMinBulletSpread());
	}
	//UKismetSystemLibrary::PrintString(this, "Current bullet spread: " + FString::SanitizeFloat(GetCurrentBulletSpread()), true, false);
}
bool UAS_Gun::ShouldTick() const
{
	if (IsMovingToIncBulletSpread())
	{
		return true;
	}
	if (GetCurrentBulletSpread() > GetMinBulletSpread())
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

void UAS_Gun::OnRep_MaxBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MaxBulletSpread, ServerBaseValue);
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
