//Copyright 2021, Dakota Dawe, All rights reserved

#pragma once

#include "Templates/SubclassOf.h"
#include "DataTypes.generated.h"

UENUM(BlueprintType)
enum class EMagazineState : uint8
{
	InUse		UMETA(DisplayName, "InUse"),
	NotInUse	UMETA(DisplayName, "NotInUse"),
	OnGround	UMETA(DisplayName, "OnGround")
};

UENUM(BlueprintType)
enum class EFirearmGripType : uint8
{
	None			UMETA(DisplayName, "None"),
	VerticalGrip	UMETA(DisplayName, "ForwardGrip"),
	AngledGrip		UMETA(DisplayName, "AngledGrip")
};

UENUM(BlueprintType)
enum class EFirearmFireMode : uint8
{
	Safe			UMETA(DisplayName, "Safe"),
	Semi			UMETA(DisplayName, "Semi"),
	Burst			UMETA(DisplayName, "Burst"),
	FullAuto		UMETA(DisplayName, "FullAuto"),
	BoltAction		UMETA(DisplayName, "BoltAction")
};

UENUM(BlueprintType)
enum class ELeaning : uint8
{
	None	UMETA(DisplayName, "None"),
	Left	UMETA(DisplayName, "Left"),
	Right	UMETA(DisplayName, "Right")
};

UENUM(BlueprintType)
enum class EPortPose : uint8
{
	None	UMETA(DisplayName, "None"),
	High	UMETA(DisplayName, "High"),
	Low		UMETA(DisplayName, "Low")
};

UENUM(BlueprintType)
enum class EPartType : uint8
{
	Sight			UMETA(DisplayName, "Sight"),
	Magnifier		UMETA(DisplayName, "Magnifier"),
	FlipMount		UMETA(DisplayName, "FlipMount"),
	LightLaser		UMETA(DisplayName, "LightLaser"),
	Handguard		UMETA(DisplayName, "Handguard"),
	Barrel			UMETA(DisplayName, "Barrel"),
	MuzzleDevice	UMETA(DisplayName, "MuzzleDevice"),
	Stock			UMETA(DisplayName, "Stock"),
	PistolGrip		UMETA(DisplayName, "PistolGrip"),
	ForwardGrip		UMETA(DisplayName, "ForwardGrip"),
	Other			UMETA(DisplayName, "Other")
};

UENUM(BlueprintType)
enum class EFirearmInHand : uint8
{
	None		UMETA(DisplayName, "None"),
	M4			UMETA(DisplayName, "M4"),
	Test		UMETA(DisplayName, "Test"),
};

class UMaterialInstance;
class UMaterialInstanceDynamic;
class UFXSystemAsset;
class USoundBase;

USTRUCT(BlueprintType)
struct FFirearmPartStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float Weight = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float ErgonomicsChangePercentage = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float RecoilChangePercentage = 0.0f;

	FFirearmPartStats operator+ (const FFirearmPartStats& Stats) const
	{
		FFirearmPartStats NewStats;
		NewStats.Weight = this->Weight + Stats.Weight;
		NewStats.ErgonomicsChangePercentage = this->ErgonomicsChangePercentage + Stats.ErgonomicsChangePercentage;
		NewStats.RecoilChangePercentage = this->RecoilChangePercentage + Stats.RecoilChangePercentage;

		return NewStats;
	}
	
	FFirearmPartStats& operator+= (const FFirearmPartStats& Stats)
	{
		this->Weight += Stats.Weight;
		this->ErgonomicsChangePercentage += Stats.ErgonomicsChangePercentage;
		this->RecoilChangePercentage += Stats.RecoilChangePercentage;

		return *this;
	}
};

USTRUCT(BlueprintType)
struct FFirearmStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float Weight = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float Ergonomics = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float VerticalRecoil = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	float HorizontalRecoil = 0.0f;
};

USTRUCT(BlueprintType)
struct FSightData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "FPSTemplate")
	class AFPSTemplate_SightBase* Sight = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "FPSTemplate")
	FName Socket = NAME_None;

	bool operator==(const FSightData& SightData) const
	{
		return this->Sight == SightData.Sight;
	}
};

USTRUCT(BlueprintType)
struct FFirearmPartData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	TSubclassOf<class AFPSTemplate_PartBase> PartClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate")
	class UTexture2D* PartImage = nullptr;
};

USTRUCT(BlueprintType)
struct FReticleMaterial
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FPSTemplate | Reticle")
	UMaterialInstance* ReticleMaterial = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "FPSTemplate | Reticle")
	UMaterialInstanceDynamic* DynamicReticleMaterial = nullptr;
};

USTRUCT(BlueprintType)
struct FImpactEffects
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFXSystemAsset* ImpactEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* ImpactDecal = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUseParticlesRotation = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector DecalSize = FVector(2.5f, 2.5f, 2.5f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DecalLifeTime = 8.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};