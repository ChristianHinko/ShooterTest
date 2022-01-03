// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "PropertyValueChangeListener.generated.h"


class IPropertyValueChangeListener;



DECLARE_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float& OldValue, const float& NewValue);


USTRUCT()
struct SONICSHOOTER_API FFloatValueProperty
{
	GENERATED_BODY()


public:
	FFloatValueProperty()
	{

	}
	FFloatValueProperty(IPropertyValueChangeListener* InListener);

	~FFloatValueProperty()
	{

	}


	void SetValue(double NewValue);

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
	float Value;


	IPropertyValueChangeListener* Listener;

	int32 Id;

};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPropertyValueChangeListener : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class SONICSHOOTER_API IPropertyValueChangeListener
{
	GENERATED_BODY()

private:
	friend struct FFloatValueProperty;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FFloatValueChange& GetFloatValueChangeDelegate(const FFloatValueProperty& Property);

private:
	TMap<FFloatValueProperty, FFloatValueChange> FloatValueChangeDelegates;

	int32 NextPropertyId;

};
