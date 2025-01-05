// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Characters/Examples/STCharacter_PushModelDemo.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "ISEngineSubsystem_InputActionAssetReferences.h"
#include "GCPrintToScreen.h"

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

    FGCPrintToScreen(this, FString::Printf(TEXT("My push model float: `%f`."), MyPushModelFloat));
}

void ASTCharacter_PushModelDemo::SetupPlayerInputComponent(UInputComponent* inPlayerInputComponent)
{
    check(inPlayerInputComponent);
    Super::SetupPlayerInputComponent(inPlayerInputComponent);

    UEnhancedInputComponent* playerEnhancedInputComponent = Cast<UEnhancedInputComponent>(inPlayerInputComponent);
    if (!ensure(playerEnhancedInputComponent))
    {
        return;
    }

    check(GEngine);
    const UISEngineSubsystem_InputActionAssetReferences& inputActionAssetReferenceSubsystem = UISEngineSubsystem_InputActionAssetReferences::GetChecked(*GEngine);

    if (const UInputAction* inputActionPrimaryFire = inputActionAssetReferenceSubsystem.GetInputAction(STNativeGameplayTags::InputAction_PrimaryFire))
    {
        playerEnhancedInputComponent->BindAction(inputActionPrimaryFire, ETriggerEvent::Started, this, &ThisClass::OnPressedPrimaryFire);
    }

    if (const UInputAction* inputActionSecondaryFire = inputActionAssetReferenceSubsystem.GetInputAction(STNativeGameplayTags::InputAction_SecondaryFire))
    {
        playerEnhancedInputComponent->BindAction(inputActionSecondaryFire, ETriggerEvent::Started, this, &ThisClass::OnPressedSecondaryFire);
    }
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
    FGCPrintToScreen(this, TEXT("SET MARKED DIRTY")).Color(FColor::Green);
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
    FGCPrintToScreen(this, TEXT("SET NO DIRTY")).Color(FColor::Red);
    MyPushModelFloat = MyPushModelFloat + 5;
}

void ASTCharacter_PushModelDemo::SetMyPushModelFloat(const float NewPushModelFloat)
{
    MyPushModelFloat = NewPushModelFloat;
    MARK_PROPERTY_DIRTY_FROM_NAME(ASTCharacter_PushModelDemo, MyPushModelFloat, this);
}
