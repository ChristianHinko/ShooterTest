// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/PropertyWrappers.h"

#include "Net/Core/PushModel/PushModel.h"



FFloatPropertyWrapper::FFloatPropertyWrapper()
	: ValueChangeDelegate(nullptr),
	PropertyOwner(nullptr),
	PropertyName(NAME_None),
	Property(nullptr),
	Value(0.f)
{
	bMarkNetDirtyOnChange = false;


}
FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName)
	: FFloatPropertyWrapper()
{
	PropertyOwner = InPropertyOwner;
	PropertyName = InPropertyName;

	Property = FindFProperty<FProperty>(PropertyOwner->GetClass(), PropertyName);
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

	if (Property == nullptr)
	{
		// Ensure this property exists on the owner!
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given PropertyName \"%s\" was not found on the PropertyOwner \"%s\". Ensure correct spelling for the property you are looking for and make sure it is a UPROPERTY so we can find it!"), *FString(__FUNCTION__), *(InPropertyName.ToString()), *(InPropertyOwner->GetName()));
	}
	else if (!(CastField<FStructProperty>(Property) && CastField<FStructProperty>(Property)->Struct == FFloatPropertyWrapper::StaticStruct()))
	{
		// Ensure this property is a FFloatPropertyWrapper!
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given FProperty \"%s::%s\" is not a %s!"), *FString(__FUNCTION__), *(InPropertyOwner->GetClass()->GetName()), *(InPropertyName.ToString()), *(FFloatPropertyWrapper::StaticStruct()->GetName()));
	}

#endif

}
FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate)
	: FFloatPropertyWrapper(InPropertyOwner, InPropertyName)
{
	SetValueChangeDelegate(InValueChangeDelegate);
}
FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* InPropertyOwner, FName InPropertyName, const TSharedRef<FFloatValueChange>& InValueChangeDelegate)
	: FFloatPropertyWrapper(InPropertyOwner, InPropertyName)
{
	SetValueChangeDelegate(InValueChangeDelegate);
}

FFloatPropertyWrapper::~FFloatPropertyWrapper()
{

}


void FFloatPropertyWrapper::SetValueChangeDelegate(FFloatValueChange* InValueChangeDelegate)
{
	ValueChangeDelegate = MakeShared<FFloatValueChange>(*InValueChangeDelegate);
}
void FFloatPropertyWrapper::SetValueChangeDelegate(const TSharedRef<FFloatValueChange>& InValueChangeDelegate)
{
	ValueChangeDelegate = InValueChangeDelegate;
}


float FFloatPropertyWrapper::operator=(const float& NewValue)
{
	const float OldValue = Value;

	if (NewValue != OldValue)
	{
		Value = NewValue;
		if (ValueChangeDelegate.IsValid())
		{
			ValueChangeDelegate->Broadcast(OldValue, NewValue);
		}

		if (bMarkNetDirtyOnChange)
		{
			MARK_PROPERTY_DIRTY(PropertyOwner, Property);
		}
	}

	return Value;
}

void FFloatPropertyWrapper::MarkNetDirty()
{
	MARK_PROPERTY_DIRTY(PropertyOwner, Property);
}

bool FFloatPropertyWrapper::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	// Our optimizations
	bool bValueIsJustZero = false; // we're doing an overkill and useless optimization for example purposes


	uint8 RepBits;
	if (Ar.IsSaving())
	{
		// We are a writer, lets find some optimizations and pack them into RepBits

		if (Value == 0.f)
		{
			bValueIsJustZero = true;
		}


		RepBits = (bValueIsJustZero << 0);
	}

	// Pack/unpack our RepBits into/outof the Archive
	Ar.SerializeBits(&RepBits, 1);
	if (Ar.IsLoading())
	{
		// We are a reader, lets unpack our optimization bools from RepBits

		bValueIsJustZero = (RepBits & (1 << 0));
	}


	if (Ar.IsSaving())
	{
		if (!bValueIsJustZero) // only serialize Value if it wasn't zero
		{
			Ar << Value;
		}
	}

	if (Ar.IsLoading())
	{
		if (!bValueIsJustZero) // only unpack Value if it wasn't zero (because we can just do a quick set instead)
		{
			Ar << Value;
		}
		else
		{
			Value = 0.f;
		}
	}






	bOutSuccess = true;
	return true;
}
