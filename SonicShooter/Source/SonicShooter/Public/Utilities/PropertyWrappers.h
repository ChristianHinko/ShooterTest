// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PropertyWrappers.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float&, OldValue, const float&, NewValue);


USTRUCT()
struct SONICSHOOTER_API FFloatPropertyWrapper
{
	GENERATED_BODY()


public:
	FFloatPropertyWrapper()
	{

	}
	FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate);

	~FFloatPropertyWrapper();


	float GetValue() const { return Value; }

	FName GetPropertyName() const { return PropertyName; }

	FFloatValueChange* GetValueChangeDelegate() const { return ValueChangeDelegate; }


	float operator=(const float& NewValue);
	//float operator=(const FFloatPropertyWrapper& NewValue)
	//{
	//	return operator=(NewValue.Value);
	//}

	bool operator==(const float& Other) const
	{
		return (Value == Other);
	}
	//bool operator==(const FFloatPropertyWrapper& Other) const
	//{
	//	return operator==(Other.Value);
	//}

private:
	float Value;


	FName PropertyName;

	FFloatValueChange* ValueChangeDelegate;

};
