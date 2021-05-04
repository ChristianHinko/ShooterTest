// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/PropertyWrappers.h"



FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate)
{
	PropertyName = InPropertyName;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	FProperty* FoundProperty = FindFProperty<FProperty>(Owner->GetClass(), PropertyName); // ensure this property exists on the owner!

	if (FoundProperty == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given PropertyName \"%s\" was not found on the PropertyOwner \"%s\". Ensure correct spelling for the property you are looking for and make sure it is a UPROPERTY so we can find it!"), *FString(__FUNCTION__), *(InPropertyName.ToString()), *(Owner->GetName()));
	}
	//else if (Cast<FFloatPropertyWrapper>(FoundProperty) == nullptr) // ensure this property is a FFloatPropertyWrapper
	//{
	//	UE_LOG(LogTemp, Fatal, TEXT("%s(): The given FProperty \"%s::%s\" is not a %s!"), *FString(__FUNCTION__), *(Owner->GetClass()->GetName()), *(InPropertyName.ToString()), *(FFloatPropertyWrapper::StaticStruct()->GetName()));
	//}

#endif

	ValueChangeDelegate = InValueChangeDelegate;

}
FFloatPropertyWrapper::~FFloatPropertyWrapper()
{

}

bool FFloatPropertyWrapper::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	uint8 RepBits = 0;
    if (Ar.IsSaving())
    {
		RepBits |= 1 << 0;
    }

	Ar.SerializeBits(&RepBits, 0);



	if (RepBits & (1 << 0))
	{
		Ar << Value;
	}



    bOutSuccess = true;
    return true;
}

float FFloatPropertyWrapper::operator=(const float& NewValue)
{
	const float OldValue = Value;

	Value = NewValue;
	if (LIKELY(ValueChangeDelegate))
	{
		ValueChangeDelegate->Broadcast(OldValue, NewValue);
	}

	return Value;
}
