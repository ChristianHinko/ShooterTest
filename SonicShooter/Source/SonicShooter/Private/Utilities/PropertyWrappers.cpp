// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/PropertyWrappers.h"



FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* Owner, FName InPropertyName)
	: FFloatPropertyWrapper()
{
	PropertyName = InPropertyName;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	FProperty* FoundProperty = FindFProperty<FProperty>(Owner->GetClass(), PropertyName);

	if (FoundProperty == nullptr)
	{
		// Ensure this property exists on the owner!
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given PropertyName \"%s\" was not found on the PropertyOwner \"%s\". Ensure correct spelling for the property you are looking for and make sure it is a UPROPERTY so we can find it!"), *FString(__FUNCTION__), *(InPropertyName.ToString()), *(Owner->GetName()));
	}
	else if (!(CastField<FStructProperty>(FoundProperty) && CastField<FStructProperty>(FoundProperty)->Struct == FFloatPropertyWrapper::StaticStruct()))
	{
		// Ensure this property is a FFloatPropertyWrapper!
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given FProperty \"%s::%s\" is not a %s!"), *FString(__FUNCTION__), *(Owner->GetClass()->GetName()), *(InPropertyName.ToString()), *(FFloatPropertyWrapper::StaticStruct()->GetName()));
	}

#endif

}
FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, FFloatValueChange* InValueChangeDelegate)
	: FFloatPropertyWrapper(Owner, InPropertyName)
{
	SetValueChangeDelegate(InValueChangeDelegate);
}
FFloatPropertyWrapper::FFloatPropertyWrapper(UObject* Owner, FName InPropertyName, const TSharedRef<FFloatValueChange>& InValueChangeDelegate)
	: FFloatPropertyWrapper(Owner, InPropertyName)
{
	SetValueChangeDelegate(InValueChangeDelegate);
}

FFloatPropertyWrapper::~FFloatPropertyWrapper()
{

}


float FFloatPropertyWrapper::operator=(const float& NewValue)
{
	const float OldValue = Value;

	Value = NewValue;
	if (ValueChangeDelegate.IsValid())
	{
		ValueChangeDelegate->Broadcast(OldValue, NewValue);
	}

	return Value;
}
