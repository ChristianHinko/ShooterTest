// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapons/AS_Gun.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystem/SSGameplayAbilityTypes.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;
	Params.Condition = COND_None;
	Params.RepNotifyCondition = REPNOTIFY_Always;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MinBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MovingBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpreadIncRate, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, FireBulletSpread, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpreadDecSpeed, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, NumberOfBulletsPerFire, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, MaxRange, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, Ricochets, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, Penetrations, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, InitialBulletSpeed, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, BulletSpeedFalloff, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, bFullAuto, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenShots, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenFiresOverride, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, TimeBetweenBurstsOverride, Params);

	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, NumShotsPerBurst, Params);
	DOREPLIFETIME_WITH_PARAMS_FAST(UAS_Gun, AmmoCost, Params);
}

UAS_Gun::UAS_Gun()
	: MinBulletSpread(10.f),
	MovingBulletSpread(20.f),
	BulletSpreadIncRate(70.f),
	FireBulletSpread(50.f),
	BulletSpreadDecSpeed(15.f),

	NumberOfBulletsPerFire(1.f),
	MaxRange(100000.f),
	Penetrations(-1),
	Ricochets(-1),
	InitialBulletSpeed(20.f),
	BulletSpeedFalloff(.9f),

	bFullAuto(0),
	TimeBetweenShots(0.1f),
	TimeBetweenFiresOverride(-1.f),
	TimeBetweenBurstsOverride(-1.f),

	NumShotsPerBurst(3),
	AmmoCost(1.f)
{
	CurrentBulletSpread = FFloatPropertyWrapper(this, FName(TEXT("CurrentBulletSpread")));
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

	if (FGAAI_Shooter* ShooterActorInfo = static_cast<FGAAI_Shooter*>(GetActorInfo()))
	{
		ShooterActorInfo->OnInited.AddUObject(this, &UAS_Gun::OnActorInfoInited);

		if (UASC_Shooter* ShooterASC = ShooterActorInfo->GetShooterAbilitySystemComponent())
		{
			CurrentBulletSpread.SetValueChangeDelegate(ShooterASC->OnCurrentBulletSpreadChange);
		}
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


	if (const FGAAI_Shooter* const ShooterActorInfo = static_cast<const FGAAI_Shooter* const>(GetActorInfo()))
	{
		Inventory = ShooterActorInfo->GetInventoryComponent();
		CMC = ShooterActorInfo->GetSSCharacterMovementComponent();
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
	for (const UAttributeSet* AttributeSet : GetOwningAbilitySystemComponent()->GetSpawnedAttributes())
	{
		if (AttributeSet->IsA<UAS_Gun>())
		{
			CurrentBulletSpread = GetMinBulletSpread();
			//UKismetSystemLibrary::PrintString(this, "RESETED", true, false, FLinearColor::Yellow);
		}
	}


}
void UAS_Gun::OnInventoryItemInactive(UArcInventoryComponent_Active* InventoryComponent, UArcItemStack* ItemStack)
{
	for (const UAttributeSet* AttributeSet : GetOwningAbilitySystemComponent()->GetSpawnedAttributes())
	{
		if (AttributeSet->IsA<UAS_Gun>())
		{
			CurrentBulletSpread = GetMinBulletSpread();
			//UKismetSystemLibrary::PrintString(this, "RESETED", true, false, FLinearColor::Yellow);
		}
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

void UAS_Gun::ApplyFireBulletSpread()
{
	CurrentBulletSpread = CurrentBulletSpread + GetFireBulletSpread();

	GetOwningAbilitySystemComponent()->UpdateShouldTick();
}

bool UAS_Gun::IsMovingToIncBulletSpread() const
{
	if (GetBulletSpreadIncRate() <= 0)
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
		if (CurrentBulletSpread < GetMovingBulletSpread())
		{
			CurrentBulletSpread = CurrentBulletSpread + (GetBulletSpreadIncRate() * DeltaTime);
			if (CurrentBulletSpread > GetMovingBulletSpread())
			{
				CurrentBulletSpread = GetMovingBulletSpread();
			}
			return;
		}
	}

	float interptedBulletSpread = FMath::FInterpTo(CurrentBulletSpread, GetRestBulletSpread(), DeltaTime, GetBulletSpreadDecSpeed());
	CurrentBulletSpread = interptedBulletSpread;
	if (CurrentBulletSpread < GetRestBulletSpread())
	{
		CurrentBulletSpread = GetRestBulletSpread();
	}
}
bool UAS_Gun::ShouldTick() const
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

void UAS_Gun::OnRep_BulletSpreadIncRate(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadIncRate, ServerBaseValue);
}

void UAS_Gun::OnRep_FireBulletSpread(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, FireBulletSpread, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadDecSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadDecSpeed, ServerBaseValue);
}



void UAS_Gun::OnRep_NumberOfBulletsPerFire(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, NumberOfBulletsPerFire, ServerBaseValue);
}

void UAS_Gun::OnRep_MaxRange(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, MaxRange, ServerBaseValue);
}

void UAS_Gun::OnRep_Ricochets(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, Ricochets, ServerBaseValue);
}

void UAS_Gun::OnRep_Penetrations(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, Penetrations, ServerBaseValue);
}

void UAS_Gun::OnRep_InitialBulletSpeed(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, InitialBulletSpeed, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpeedFalloff(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpeedFalloff, ServerBaseValue);
}



void UAS_Gun::OnRep_bFullAuto(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, bFullAuto, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenShots(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenShots, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenFiresOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenFiresOverride, ServerBaseValue);
}

void UAS_Gun::OnRep_TimeBetweenBurstsOverride(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, TimeBetweenBurstsOverride, ServerBaseValue);
}


void UAS_Gun::OnRep_NumShotsPerBurst(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, NumShotsPerBurst, ServerBaseValue);
}

void UAS_Gun::OnRep_AmmoCost(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, AmmoCost, ServerBaseValue);
}
