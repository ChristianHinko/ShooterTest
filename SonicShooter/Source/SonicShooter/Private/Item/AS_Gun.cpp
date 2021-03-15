// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/AS_Gun.h"

#include "Net/UnrealNetwork.h"

#include "Kismet/KismetSystemLibrary.h"



void UAS_Gun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MinBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, MaxBulletSpread, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadIncPerShot, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_Gun, BulletSpreadDecRate, COND_None, REPNOTIFY_Always);
}

UAS_Gun::UAS_Gun()
	: MinBulletSpread(0.f),
	MaxBulletSpread(10.f),
	BulletSpreadIncPerShot(2.f),
	BulletSpreadDecRate(10.f)
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


	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	ASC->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag("Character.State.HasActiveItemActive"), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UAS_Gun::OnHasActiveItemActiveTagChanged);
}

void UAS_Gun::OnHasActiveItemActiveTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (GetOwningAbilitySystemComponent()->HasAttributeSetForAttribute(GetCurrentBulletSpreadAttribute()))
	{
		SetCurrentBulletSpread(GetMinBulletSpread());
	}
}


void UAS_Gun::IncCurrentBulletSpread()
{
	SetCurrentBulletSpread(GetCurrentBulletSpread() + GetBulletSpreadIncPerShot());
	if (GetCurrentBulletSpread() > GetMaxBulletSpread())
	{
		SetCurrentBulletSpread(GetMaxBulletSpread());
	}

	//UKismetSystemLibrary::PrintString(this, "Current bullet spread: " + FString::SanitizeFloat(GetCurrentBulletSpread()), true, false);
}

void UAS_Gun::Tick(float DeltaTime)
{
	SetCurrentBulletSpread(GetCurrentBulletSpread() - (GetBulletSpreadDecRate() * DeltaTime));
	if (GetCurrentBulletSpread() < GetMinBulletSpread())
	{
		SetCurrentBulletSpread(GetMinBulletSpread());
	}

	//UKismetSystemLibrary::PrintString(this, "Current bullet spread: " + FString::SanitizeFloat(GetCurrentBulletSpread()), true, false);
}
bool UAS_Gun::ShouldTick() const
{
	return (GetCurrentBulletSpread() > GetMinBulletSpread());
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

void UAS_Gun::OnRep_BulletSpreadIncPerShot(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadIncPerShot, ServerBaseValue);
}

void UAS_Gun::OnRep_BulletSpreadDecRate(const FGameplayAttributeData& ServerBaseValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Gun, BulletSpreadDecRate, ServerBaseValue);
}
