// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/ExampleAbilitySystemCharacter/PushModelCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

#include "Kismet/KismetSystemLibrary.h"



void APushModelCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	FDoRepLifetimeParams Params;

	Params.bIsPushBased = true;
	DOREPLIFETIME_WITH_PARAMS_FAST(APushModelCharacter, MyPushModelFloat, Params);
}

APushModelCharacter::APushModelCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void APushModelCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	UKismetSystemLibrary::PrintString(this, "MyPushModelFloat: " + FString::SanitizeFloat(MyPushModelFloat), true, false);
}

void APushModelCharacter::OnPrimaryFirePressed()
{
	ServerPrimaryFirePressed();
}
bool APushModelCharacter::ServerPrimaryFirePressed_Validate()
{
	return true;
}
void APushModelCharacter::ServerPrimaryFirePressed_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET MARKED DIRTY", true, false, FLinearColor::Green);
	SetMyPushModelFloat(MyPushModelFloat + 5);
}

void APushModelCharacter::OnSecondaryFirePressed()
{
	ServerSecondaryFirePressed();
}
bool APushModelCharacter::ServerSecondaryFirePressed_Validate()
{
	return true;
}
void APushModelCharacter::ServerSecondaryFirePressed_Implementation()
{
	UKismetSystemLibrary::PrintString(this, "SET NO DIRTY", true, false, FLinearColor::Red);
	MyPushModelFloat = MyPushModelFloat + 5;
}

void APushModelCharacter::SetMyPushModelFloat(const float NewPushModelFloat)
{
	MyPushModelFloat = NewPushModelFloat;
	MARK_PROPERTY_DIRTY_FROM_NAME(APushModelCharacter, MyPushModelFloat, this);
}
