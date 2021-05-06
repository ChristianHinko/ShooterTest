// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PropertyWrappers.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float&, OldValue, const float&, NewValue);


/**
 * 
 */
USTRUCT(BlueprintType)
struct SONICSHOOTER_API FFloatPropertyWrapper
{
	GENERATED_BODY()


public:
	FFloatPropertyWrapper()
	{
		ValueChangeDelegate = nullptr;
		PropertyOwner = nullptr;
		Property = nullptr;

		bMarkNetDirtyOnChange = false;
	}
	FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName);
	FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate);
	FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName, const TSharedRef<FFloatValueChange>& InValueChangeDelegate);

	virtual ~FFloatPropertyWrapper();

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FFloatPropertyWrapper::StaticStruct();
	}

	/** Our custom replication for this struct (we only want to replicate Value) */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);




	// Property
	FName GetPropertyName() const { return PropertyName; }
	UObject* GetPropertyOwner() const { return PropertyOwner; }
	FProperty* GetProperty() const { return Property; }

	// Change delegate
	FFloatValueChange* GetValueChangeDelegate() const { return ValueChangeDelegate.Get(); }
	void SetValueChangeDelegate(FFloatValueChange* InValueChangeDelegate);
	void SetValueChangeDelegate(const TSharedRef<FFloatValueChange>& InValueChangeDelegate);

	/**
	 * If true, will MARK_PROPERTY_DIRTY() when Value is assigned.
	 * 
	 * This can be toggled whenever you want.
	 */
	uint8 bMarkNetDirtyOnChange : 1;
	/** Marks the property dirty */
	void MarkNetDirty();


	/** Where the magic happens. Broadcasts ValueChangeDelegate and does MARK_PROPERTY_DIRTY() */
	float operator=(const float& NewValue);

	/** An easy conversion from this struct to float */
	operator float() const
	{
		return Value;
	}


private:
	/** The actual value of this float property */
	UPROPERTY()
		float Value;


	UObject* PropertyOwner;
	FName PropertyName;
	FProperty* Property;

	TSharedPtr<FFloatValueChange> ValueChangeDelegate;

};

template<>
struct TStructOpsTypeTraits<FFloatPropertyWrapper> : public TStructOpsTypeTraitsBase2<FFloatPropertyWrapper>
{
	enum
	{
		WithNetSerializer = true/*,
		WithCopy = true*/			// Not sure if we need this but will leave it here just to remind
	};
};
