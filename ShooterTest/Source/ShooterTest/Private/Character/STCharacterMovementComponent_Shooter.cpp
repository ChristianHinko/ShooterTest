// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/STCharacterMovementComponent_Shooter.h"

#include "Engine/ActorChannel.h"
#include "Subobjects/STObject_Stamina.h"
#include "AbilitySystem/AttributeSets/STAttributeSet_Stamina.h"

#include "Kismet/KismetSystemLibrary.h"



bool USTCharacterMovementComponent_Shooter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// Give StaminaSubobject an opportunity to replicate NOTE: it won't actually replicate because the CMC has bReplicates to false
	if (IsValid(StaminaSubobject))
	{
		bWroteSomething |= StaminaSubobject->ReplicateSubobjects(Channel, Bunch, RepFlags);

		if (StaminaSubobject->IsSupportedForNetworking())
		{
			bWroteSomething |= Channel->ReplicateSubobject(StaminaSubobject, *Bunch, *RepFlags);
		}
	}

	return bWroteSomething;
}

USTCharacterMovementComponent_Shooter::USTCharacterMovementComponent_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCrouchCancelsDesireToRun = true;
	bRunCancelsDesireToCrouch = true;
	bJumpCancelsDesireToCrouch = true;
	bJumpCancelsDesireToRun = false;


	bCanCrouchJump = false;
	bCanWalkOffLedgesWhenCrouching = true;

	StaminaSubobject = CreateDefaultSubobject<USTObject_Stamina>(TEXT("StaminaSubobject"));
	if (StaminaSubobject)
	{
		StaminaSubobject->OnStaminaFullyDrained.AddUObject(this, &USTCharacterMovementComponent_Shooter::OnStaminaFullyDrained);
	}
}

//  BEGIN Prediciton Data Client
FNetworkPredictionData_Client* USTCharacterMovementComponent_Shooter::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
		USTCharacterMovementComponent_Shooter* MutableThis = const_cast<USTCharacterMovementComponent_Shooter*>(this);
		MutableThis->ClientPredictionData = new FSTNetworkPredictionData_Client_ShooterCharacter(*this);
	}

	return ClientPredictionData;
}

FSTNetworkPredictionData_Client_ShooterCharacter::FSTNetworkPredictionData_Client_ShooterCharacter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}
FSavedMovePtr FSTNetworkPredictionData_Client_ShooterCharacter::AllocateNewMove()
{
	// Return our custom move struct instead
	return FSavedMovePtr(new FSTSavedMove_ShooterCharacter());
}
//  END Prediciton Data Client

void USTCharacterMovementComponent_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	Super::OnInitializeAbilitySystemComponent(ASC);

	// Bind to Attribute value change delegates
	ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetMaxStaminaAttribute()).AddUObject(this, &USTCharacterMovementComponent_Shooter::OnMaxStaminaAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaDrainAttribute()).AddUObject(this, &USTCharacterMovementComponent_Shooter::OnStaminaDrainAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaGainAttribute()).AddUObject(this, &USTCharacterMovementComponent_Shooter::OnStaminaGainAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaRegenPauseAttribute()).AddUObject(this, &USTCharacterMovementComponent_Shooter::OnStaminaRegenPauseAttributeChange);

	// Get initial values
	if (IsValid(StaminaSubobject))
	{
		StaminaSubobject->SetMaxStamina(ASC->GetNumericAttribute(USTAttributeSet_Stamina::GetMaxStaminaAttribute()));
		StaminaSubobject->SetStaminaDrain(ASC->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaDrainAttribute()));
		StaminaSubobject->SetStaminaGain(ASC->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaGainAttribute()));
		StaminaSubobject->SetStaminaRegenPause(ASC->GetNumericAttribute(USTAttributeSet_Stamina::GetStaminaRegenPauseAttribute()));
	}
}

//  BEGIN Attribute value change delegates
void USTCharacterMovementComponent_Shooter::OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSTCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's MaxStamina value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetMaxStamina(Data.NewValue);
}
void USTCharacterMovementComponent_Shooter::OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSTCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaDrain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaDrain(Data.NewValue);
}
void USTCharacterMovementComponent_Shooter::OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSTCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaGain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaGain(Data.NewValue);
}
void USTCharacterMovementComponent_Shooter::OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSTCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaRegenPause value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaRegenPause(Data.NewValue);
}
//  END Attribute value change delegates


void USTCharacterMovementComponent_Shooter::OnStaminaFullyDrained()
{
	SetWantsToRun(false);
}

bool USTCharacterMovementComponent_Shooter::CanRunInCurrentState() const
{
	bool RetVal = Super::CanRunInCurrentState();


	if (StaminaSubobject && StaminaSubobject->Stamina <= 0)
	{
		// Out of stamina
		return false;
	}

	return RetVal;
}

void USTCharacterMovementComponent_Shooter::Run()
{
	Super::Run();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(true);
	}
}
void USTCharacterMovementComponent_Shooter::UnRun()
{
	Super::UnRun();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(false);
	}
}


FString USTCharacterMovementComponent_Shooter::GetMovementName() const
{
	if (MovementMode == MOVE_Custom)
	{
		// If this value is in our custom movement enum
		if (StaticEnum<ESTCustomMovementMode_Shooter>()->IsValidEnumValue(CustomMovementMode))
		{
			// Return the display name
			return StaticEnum<ESTCustomMovementMode_Shooter>()->GetDisplayNameTextByValue(CustomMovementMode).ToString();
		}
	}

	return Super::GetMovementName();
}

void USTCharacterMovementComponent_Shooter::TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const
{
	if (StaminaSubobject && StaminaSubobject->Stamina <= 0.f)
	{
		if (IsMovingOnGround()) // only if we are on the ground. if we are in the air, the player will be expecting to run anyways
		{
			// We don't want to run if we are fully out of stamina or else when stamina starts regening we would run right away and be back at zero stamina
			outTweakedWantsToRun = false;
		}
	}

	Super::TweakWantsToRunBeforeTick(outTweakedWantsToRun);
}

void USTCharacterMovementComponent_Shooter::BeginDestroy()
{
	//  BEGIN Attribute value change delegates
	if (UAbilitySystemComponent* ASC = OwnerASC.Get())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetMaxStaminaAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaDrainAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaGainAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USTAttributeSet_Stamina::GetStaminaRegenPauseAttribute()).RemoveAll(this);
	}
	//  END Attribute value change delegates


	Super::BeginDestroy();
}
