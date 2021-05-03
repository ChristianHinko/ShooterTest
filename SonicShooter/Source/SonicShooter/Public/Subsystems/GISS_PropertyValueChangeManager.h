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


	UObject* GetOwner() const { return Owner; }
	int32 GetId() const { return Id; }

	FFloatValueChange& GetFloatValueChangeDelegate();


	void SetValue(float NewValue);
	float operator=(const float& NewValue)
	{
		SetValue(NewValue);
		return Value;
	}

	float GetValue();
	bool operator==(const float& Other) const
	{
		return (Value == Other);
	}

private:
	float Value;


	UObject* Owner;

	TWeakObjectPtr<UGISS_PropertyValueChangeManager> ChangeManager;
	int32 Id;
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



	FFloatValueChange& GetFloatValueChangeDelegate(const int32& Id);

private:
	TMap<int32, FFloatValueChange> FloatValueChangeDelegates;

	int32 NextPropertyId;
};
