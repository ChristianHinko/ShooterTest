// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Characters\Examples\C_PushModelDemo.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void AC_PushModelDemo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(AC_PushModelDemo, MyPushModelFloat, Params);
}

AC_PushModelDemo::AC_PushModelDemo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void AC_PushModelDemo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	UKismetSystemLibrary::PrintString(this, "MyPushModelFloat: " + FString::SanitizeFloat(MyPushModelFloat), true, false);
}

void AC_PushModelDemo::OnPressedPrimaryFire()
{
	ServerOnPressedPrimaryFire();
}
bool AC_PushModelDemo::ServerOnPressedPrimaryFire_Validate()
{
	return true;
}
void AC_PushModelDemo::ServerOnPressedPrimaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET MARKED DIRTY", true, false, FLinearColor::Green);
	SetMyPushModelFloat(MyPushModelFloat + 5);
}

void AC_PushModelDemo::OnPressedSecondaryFire()
{
	ServerOnPressedSecondaryFire();
}
bool AC_PushModelDemo::ServerOnPressedSecondaryFire_Validate()
{
	return true;
}
void AC_PushModelDemo::ServerOnPressedSecondaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET NO DIRTY", true, false, FLinearColor::Red);
	MyPushModelFloat = MyPushModelFloat + 5;
}

void AC_PushModelDemo::SetMyPushModelFloat(const float NewPushModelFloat)
{
	MyPushModelFloat = NewPushModelFloat;
	MARK_PROPERTY_DIRTY_FROM_NAME(AC_PushModelDemo, MyPushModelFloat, this);
}
