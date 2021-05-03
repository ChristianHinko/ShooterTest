// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GISS_PropertyValueChangeManager.h"

#include "Kismet/GameplayStatics.h"



FFloatValueProperty::FFloatValueProperty(UObject* InOwner)
{
	Owner = InOwner;
	ChangeManager = UGameplayStatics::GetGameInstance(Owner)->GetSubsystem<UGISS_PropertyValueChangeManager>();
	Id = (ChangeManager->NextPropertyId)++;
}
FFloatValueProperty::~FFloatValueProperty()
{
	if (UGISS_PropertyValueChangeManager* ChangeManagerPtr = ChangeManager.Get())
	{
		ChangeManagerPtr->FloatValueChangeDelegates.Remove(Id);
	}
}


FFloatValueChange& FFloatValueProperty::GetFloatValueChangeDelegate()
{
	return ChangeManager->GetFloatValueChangeDelegate(Id);
}

void FFloatValueProperty::SetValue(float NewValue)
{
	const float OldValue = Value;

	Value = NewValue;

	if (FFloatValueChange* ChangeDelegate = ChangeManager->FloatValueChangeDelegates.Find(Id))
	{
		ChangeDelegate->Broadcast(OldValue, NewValue);
	}
}

float FFloatValueProperty::GetValue()
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



FFloatValueChange& UGISS_PropertyValueChangeManager::GetFloatValueChangeDelegate(const int32& Id)
{
	return FloatValueChangeDelegates.FindOrAdd(Id);
}
