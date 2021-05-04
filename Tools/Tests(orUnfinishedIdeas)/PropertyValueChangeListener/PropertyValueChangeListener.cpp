// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PropertyValueChangeListener.h"



FFloatValueProperty::FFloatValueProperty(IPropertyValueChangeListener* InListener)
{
	Listener = InListener;
	Id = (Listener->NextPropertyId)++;
}

void FFloatValueProperty::SetValue(double NewValue)
{
	double OldValue = Value;

	Value = NewValue;

	if (FFloatValueChange* ChangeDelegate = Listener->FloatValueChangeDelegates.Find(*this))
	{
		ChangeDelegate->Broadcast(OldValue, NewValue);
	}
}

double FFloatValueProperty::GetValue()
{
	return Value;
}

// Add default functionality here for any IPropertyValueChangeListener functions that are not pure virtual.

FFloatValueChange& IPropertyValueChangeListener::GetFloatValueChangeDelegate(const FFloatValueProperty& Property)
{
	return FloatValueChangeDelegates.FindOrAdd(Property);
}
