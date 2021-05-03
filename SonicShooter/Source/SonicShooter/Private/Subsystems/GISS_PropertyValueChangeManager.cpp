// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GISS_PropertyValueChangeManager.h"

#include "Kismet/GameplayStatics.h"



FFloatValueProperty::FFloatValueProperty(UObject* InOwner)
{
	Owner = InOwner;
	ChangeManager = UGameplayStatics::GetGameInstance(Owner)->GetSubsystem<UGISS_PropertyValueChangeManager>();
	Id = (ChangeManager->NextPropertyId)++;

	ChangeManager->FloatValueChangeDelegates.Add(*this);
}
FFloatValueProperty::~FFloatValueProperty() // TODO: this gets hit and breaks on engine startup
{
	if (ChangeManager)
	{
		ChangeManager->FloatValueChangeDelegates.Remove(*this);
	}
}


void FFloatValueProperty::SetValue(float NewValue)
{
	const float OldValue = Value;

	Value = NewValue;

	if (FFloatValueChange* ChangeDelegate = ChangeManager->FloatValueChangeDelegates.Find(*this))
	{
		ChangeDelegate->Broadcast(OldValue, NewValue);
	}
}

double FFloatValueProperty::GetValue()
{
	return Value;
}





UGISS_PropertyValueChangeManager::UGISS_PropertyValueChangeManager()
{

}

bool UGISS_PropertyValueChangeManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}


void UGISS_PropertyValueChangeManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);


}

void UGISS_PropertyValueChangeManager::Deinitialize()
{
	Super::Deinitialize();


	FloatValueChangeDelegates.Empty();
}



FFloatValueChange& UGISS_PropertyValueChangeManager::GetFloatValueChangeDelegate(const FFloatValueProperty& Property)
{
	return FloatValueChangeDelegates.FindOrAdd(Property);
}
