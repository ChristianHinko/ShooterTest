// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PropertyWrappers.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float&, OldValue, const float&, NewValue);


USTRUCT(BlueprintType)
struct SONICSHOOTER_API FFloatPropertyWrapper
{
	GENERATED_BODY()


public:
	FFloatPropertyWrapper()
	{
		ValueChangeDelegate = nullptr;
	}
	FFloatPropertyWrapper(UObject* Owner, FName InPropertyName);
	FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate);
	FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, const TSharedRef<FFloatValueChange>& InValueChangeDelegate);

	virtual ~FFloatPropertyWrapper();

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FFloatPropertyWrapper::StaticStruct();
	}


	float GetValue() const { return Value; }

	FName GetPropertyName() const { return PropertyName; }

	FFloatValueChange* GetValueChangeDelegate() const { return ValueChangeDelegate.Get(); }
	void SetValueChangeDelegate(FFloatValueChange* InValueChangeDelegate)
	{
		MakeShared<FFloatValueChange>(*InValueChangeDelegate);
	}
	void SetValueChangeDelegate(const TSharedRef<FFloatValueChange>& InValueChangeDelegate)
	{
		ValueChangeDelegate = InValueChangeDelegate;
	}


	float operator=(const float& NewValue);

	bool operator==(const float& Other) const
	{
		return (Value == Other);
	}
	bool operator!=(const float& Other) const
	{
		return !(FFloatPropertyWrapper::operator==(Other));
	}
	bool operator>(const float& Other) const
	{
		return (Value > Other);
	}
	bool operator<(const float& Other) const
	{
		return (Value < Other);
	}
	bool operator>=(const float& Other) const
	{
		return (Value >= Other);
	}
	bool operator<=(const float& Other) const
	{
		return (Value <= Other);
	}

private:
	float Value;


	FName PropertyName;

	TSharedPtr<FFloatValueChange> ValueChangeDelegate;

};
