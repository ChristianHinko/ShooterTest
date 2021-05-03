// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GISS_PropertyValueChangeManager.generated.h"


class UGISS_PropertyValueChangeManager;



DECLARE_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float& OldValue, const float& NewValue);


USTRUCT()
struct SONICSHOOTER_API FFloatValueProperty
{
	GENERATED_BODY()


public:
	FFloatValueProperty()
	{

	}
	FFloatValueProperty(UObject* InOwner);


	~FFloatValueProperty();


	void SetValue(float NewValue);

	double GetValue();

	//BEGIN TMap requirements
	friend uint32 GetTypeHash(const FFloatValueProperty& InValueProperty)
	{
		return InValueProperty.Id;
	}

	/** Equality/Inequality operators */
	bool operator==(const FFloatValueProperty& Other) const
	{
		return ((Other.Id == Id));
	}
	bool operator!=(const FFloatValueProperty& Other) const
	{
		return ((Other.Id != Id));
	}
	//END TMap requirements

	float operator=(const float& NewValue)
	{
		SetValue(NewValue);
		return Value;
	}

	bool operator==(const float& Other) const
	{
		return (Value == Other);
	}

private:
	UObject* Owner;

	float Value;

	int32 Id;
	UGISS_PropertyValueChangeManager* ChangeManager;
};


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGISS_PropertyValueChangeManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	friend struct FFloatValueProperty;

public:
	UGISS_PropertyValueChangeManager();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;



	FFloatValueChange& GetFloatValueChangeDelegate(const FFloatValueProperty& Property);

private:
	TMap<FFloatValueProperty, FFloatValueChange> FloatValueChangeDelegates;

	int32 NextPropertyId;
};
