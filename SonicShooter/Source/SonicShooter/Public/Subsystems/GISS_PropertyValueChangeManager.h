// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GISS_PropertyValueChangeManager.generated.h"


class UGISS_PropertyValueChangeManager;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFloatValueChange, const float&, OldValue, const float&, NewValue);


USTRUCT()
struct SONICSHOOTER_API FFloatValueProperty
{
	GENERATED_BODY()


public:
	FFloatValueProperty()
	{

	}
	FFloatValueProperty(UObject* InOwner, FName InPropertyName);

	~FFloatValueProperty();


	float GetValue() const { return Value; }

	UObject* GetOwner() const { return PropertyOwner; }
	FName GetPropertyName() const { return PropertyName; }

	FFloatValueChange* GetValueChangeDelegate() const { return ValueChangeDelegate; }


	float operator=(const float& NewValue);
	//float operator=(const FFloatValueProperty& NewValue)
	//{
	//	return operator=(NewValue.Value);
	//}

	bool operator==(const float& Other) const
	{
		return (Value == Other);
	}
	//bool operator==(const FFloatValueProperty& Other) const
	//{
	//	return operator==(Other.Value);
	//}

private:
	float Value;


	UObject* PropertyOwner;
	FName PropertyName;

	TWeakObjectPtr<UGISS_PropertyValueChangeManager> ChangeManager;
	FFloatValueChange* ValueChangeDelegate;

};


/**
 * 
 */
UCLASS()
class SONICSHOOTER_API UGISS_PropertyValueChangeManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	friend struct FFloatValueProperty;

public:
	UGISS_PropertyValueChangeManager();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


	FFloatValueChange* GetFloatValueChangeDelegate(UObject* Owner, FName PropertyName);

private:
	TMap<TTuple<UObject*, FName>, FFloatValueChange> FloatValueChangeDelegates;
};
