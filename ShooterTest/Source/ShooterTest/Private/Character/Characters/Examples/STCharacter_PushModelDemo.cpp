// Fill out your copyright notice in the Description page of Project Settings.


#include "Character\Characters\Examples\STCharacter_PushModelDemo.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void ASTCharacter_PushModelDemo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(ASTCharacter_PushModelDemo, MyPushModelFloat, Params);
}

ASTCharacter_PushModelDemo::ASTCharacter_PushModelDemo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void ASTCharacter_PushModelDemo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	UKismetSystemLibrary::PrintString(this, "MyPushModelFloat: " + FString::SanitizeFloat(MyPushModelFloat), true, false);
}

void ASTCharacter_PushModelDemo::OnPressedPrimaryFire()
{
	ServerOnPressedPrimaryFire();
}
bool ASTCharacter_PushModelDemo::ServerOnPressedPrimaryFire_Validate()
{
	return true;
}
void ASTCharacter_PushModelDemo::ServerOnPressedPrimaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET MARKED DIRTY", true, false, FLinearColor::Green);
	SetMyPushModelFloat(MyPushModelFloat + 5);
}

void ASTCharacter_PushModelDemo::OnPressedSecondaryFire()
{
	ServerOnPressedSecondaryFire();
}
bool ASTCharacter_PushModelDemo::ServerOnPressedSecondaryFire_Validate()
{
	return true;
}
void ASTCharacter_PushModelDemo::ServerOnPressedSecondaryFire_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET NO DIRTY", true, false, FLinearColor::Red);
	MyPushModelFloat = MyPushModelFloat + 5;
}

void ASTCharacter_PushModelDemo::SetMyPushModelFloat(const float NewPushModelFloat)
{
	MyPushModelFloat = NewPushModelFloat;
	MARK_PROPERTY_DIRTY_FROM_NAME(ASTCharacter_PushModelDemo, MyPushModelFloat, this);
}
