// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UMG/Widgets/UW_ActiveItem.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "Item/AS_Ammo.h"



UUW_ActiveItem::UUW_ActiveItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}




void UUW_ActiveItem::NativeDestruct()
{
	Super::NativeDestruct();
}
