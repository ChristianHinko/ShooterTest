// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Characters\Examples\SSCharacter_PushModelDemo.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void ASSCharacter_PushModelDemo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(ASSCharacter_PushModelDemo, MyPushModelFloat, Params);
}

ASSCharacter_PushModelDemo::ASSCharacter_PushModelDemo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASSCharacter_PushModelDemo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	UKismetSystemLibrary::PrintString(this, "MyPushModelFloat: " + FString::SanitizeFloat(MyPushModelFloat), true, false);
}

void ASSCharacter_PushModelDemo::OnPressedPrimaryFire()
{
	ServerOnPressedPrimaryFire();
}
bool ASSCharacter_PushModelDemo::ServerOnPressedPrimaryFire_Validate()
{
	return true;
}
void ASSCharacter_PushModelDemo::ServerOnPressedPrimaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET MARKED DIRTY", true, false, FLinearColor::Green);
	SetMyPushModelFloat(MyPushModelFloat + 5);
}

void ASSCharacter_PushModelDemo::OnPressedSecondaryFire()
{
	ServerOnPressedSecondaryFire();
}
bool ASSCharacter_PushModelDemo::ServerOnPressedSecondaryFire_Validate()
{
	return true;
}
void ASSCharacter_PushModelDemo::ServerOnPressedSecondaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET NO DIRTY", true, false, FLinearColor::Red);
	MyPushModelFloat = MyPushModelFloat + 5;
}

void ASSCharacter_PushModelDemo::SetMyPushModelFloat(const float NewPushModelFloat)
{
	MyPushModelFloat = NewPushModelFloat;
	MARK_PROPERTY_DIRTY_FROM_NAME(ASSCharacter_PushModelDemo, MyPushModelFloat, this);
}
