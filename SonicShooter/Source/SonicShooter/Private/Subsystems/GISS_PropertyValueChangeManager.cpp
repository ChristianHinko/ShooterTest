// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/GISS_PropertyValueChangeManager.h"

#include "Kismet/GameplayStatics.h"



FFloatValueProperty::FFloatValueProperty(UObject* InOwner, FName InPropertyName)
{
	PropertyOwner = InOwner;
	PropertyName = InPropertyName;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	FProperty* FoundProperty = FindFProperty<FProperty>(PropertyOwner->GetClass(), PropertyName); // ensure this property exists on the owner!

	if (FoundProperty == nullptr)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%s(): The given PropertyName \"%s\" was not found on the PropertyOwner \"%s\". Ensure correct spelling for the property you are looking for and make sure it is a UPROPERTY so we can find it!"), *FString(__FUNCTION__), *(InPropertyName.ToString()), *(InOwner->GetName()));
	}
	//else if (Cast<FFloatValueProperty>(FoundProperty) == nullptr) // ensure this property is a FFloatValueProperty
	//{
	//	UE_LOG(LogTemp, Fatal, TEXT("%s(): The given FProperty \"%s::%s\" is not a %s!"), *FString(__FUNCTION__), *(InOwner->GetClass()->GetName()), *(InPropertyName.ToString()), *(FFloatValueProperty::StaticStruct()->GetName()));
	//}

#endif

	ChangeManager = UGameplayStatics::GetGameInstance(PropertyOwner)->GetSubsystem<UGISS_PropertyValueChangeManager>();
	if (ChangeManager.IsValid())
	{
		ValueChangeDelegate = &(ChangeManager->FloatValueChangeDelegates.Add(TTuple<UObject*, FName>(PropertyOwner, PropertyName)));
	}
}
FFloatValueProperty::~FFloatValueProperty()
{
	if (ChangeManager.IsValid())
	{
		ChangeManager->FloatValueChangeDelegates.Remove(TTuple<UObject*, FName>(PropertyOwner, PropertyName));
	}
}

float FFloatValueProperty::operator=(const float& NewValue)
{
	const float OldValue = Value;

	Value = NewValue;

	ValueChangeDelegate->Broadcast(OldValue, NewValue);
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




FFloatValueChange* UGISS_PropertyValueChangeManager::GetFloatValueChangeDelegate(UObject* Owner, FName PropertyName)
{
	return FloatValueChangeDelegates.Find(TTuple<UObject*, FName>(Owner, PropertyName));
}

