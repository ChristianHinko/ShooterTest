// Copyright 2017-2020 Puny Human, All Rights Reserved.

 
#include "ArcInventoryAttributeSet.h"
#include "Net/UnrealNetwork.h"




UArcInventoryAttributeSet::UArcInventoryAttributeSet(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventorySize(1)
{
	
}

void UArcInventoryAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
															
	DOREPLIFETIME_CONDITION_NOTIFY(UArcInventoryAttributeSet, InventorySize, COND_None, REPNOTIFY_Always);
}

void UArcInventoryAttributeSet::OnRep_InventorySize(FGameplayAttributeData OldInventorySize)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UArcInventoryAttributeSet, InventorySize, OldInventorySize);
}

FGameplayAttribute UArcInventoryAttributeSet::InventorySizeAttribute()
{
	static FProperty* Property = FindFProperty<FProperty>(UArcInventoryAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UArcInventoryAttributeSet, InventorySize));
	return FGameplayAttribute(Property);
}
