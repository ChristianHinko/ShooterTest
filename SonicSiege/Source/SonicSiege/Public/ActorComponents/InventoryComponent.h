// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/NetSerialization.h"

#include "InventoryComponent.generated.h"


class AWeapon;
class AEquipment;



#pragma region Fast Array
USTRUCT()
struct FFASI_Weapon : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		AWeapon* Weapon;

	UPROPERTY()
		uint8 index;

	void PreReplicatedRemove(const struct FFAS_Weapons& InArraySerializer);
	void PostReplicatedAdd(const struct FFAS_Weapons& InArraySerializer);
	void PostReplicatedChange(const struct FFAS_Weapons& InArraySerializer);
};

USTRUCT()
struct FFAS_Weapons : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FFASI_Weapon> Items;


	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FFASI_Weapon, FFAS_Weapons>(Items, DeltaParms, *this);
	}
};
template<>
struct TStructOpsTypeTraits<FFAS_Weapons> : public TStructOpsTypeTraitsBase2<FFAS_Weapons>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};









USTRUCT()
struct FFASI_Equipment : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		AEquipment* Equipment;

	void PreReplicatedRemove(const struct FFAS_Equipments& InArraySerializer);
	void PostReplicatedAdd(const struct FFAS_Equipments& InArraySerializer);
	void PostReplicatedChange(const struct FFAS_Equipments& InArraySerializer);
};

USTRUCT()
struct FFAS_Equipments : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		TArray<FFASI_Equipment> Items;


	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FFASI_Equipment, FFAS_Equipments>(Items, DeltaParms, *this);
	}
};
template<>
struct TStructOpsTypeTraits<FFAS_Equipments> : public TStructOpsTypeTraitsBase2<FFAS_Equipments>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
#pragma endregion


UCLASS( ClassGroup=(Siege), meta=(BlueprintSpawnableComponent) )
class SONICSIEGE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();


	void AddWeaponToInventory(AWeapon* Weapon);
	void RemoveWeaponFromInventory(AWeapon* Weapon);

protected:
	FFAS_Weapons Weapons;
	FFAS_Equipments Equipments;

};
