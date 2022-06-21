// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SSCharacterMovementComponent_Shooter.h"

#include "Engine/ActorChannel.h"
#include "Subobjects/SSObject_Stamina.h"
#include "AbilitySystem/AttributeSets/SSAttributeSet_Stamina.h"

#include "Kismet/KismetSystemLibrary.h"



bool USSCharacterMovementComponent_Shooter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
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

USSCharacterMovementComponent_Shooter::USSCharacterMovementComponent_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCrouchCancelsDesireToRun = true;
	bRunCancelsDesireToCrouch = true;
	bJumpCancelsDesireToCrouch = true;
	bJumpCancelsDesireToRun = false;


	bCanCrouchJump = false;
	bCanWalkOffLedgesWhenCrouching = true;

	StaminaSubobject = CreateDefaultSubobject<USSObject_Stamina>(TEXT("StaminaSubobject"));
	if (StaminaSubobject)
	{
		StaminaSubobject->OnStaminaFullyDrained.AddUObject(this, &USSCharacterMovementComponent_Shooter::OnStaminaFullyDrained);
	}
}

//BEGIN Prediciton Data Client
FNetworkPredictionData_Client* USSCharacterMovementComponent_Shooter::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
		USSCharacterMovementComponent_Shooter* MutableThis = const_cast<USSCharacterMovementComponent_Shooter*>(this);
		MutableThis->ClientPredictionData = new FSSNetworkPredictionData_Client_ShooterCharacter(*this);
	}

	return ClientPredictionData;
}

FSSNetworkPredictionData_Client_ShooterCharacter::FSSNetworkPredictionData_Client_ShooterCharacter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}
FSavedMovePtr FSSNetworkPredictionData_Client_ShooterCharacter::AllocateNewMove()
{
	// Return our custom move struct instead
	return FSavedMovePtr(new FSSSavedMove_ShooterCharacter());
}
//END Prediciton Data Client

void USSCharacterMovementComponent_Shooter::OnInitializeAbilitySystemComponent(UAbilitySystemComponent* const ASC)
{
	Super::OnInitializeAbilitySystemComponent(ASC);

	// Bind to Attribute value change delegates
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetMaxStaminaAttribute()).AddUObject(this, &USSCharacterMovementComponent_Shooter::OnMaxStaminaAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaDrainAttribute()).AddUObject(this, &USSCharacterMovementComponent_Shooter::OnStaminaDrainAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaGainAttribute()).AddUObject(this, &USSCharacterMovementComponent_Shooter::OnStaminaGainAttributeChange);
	ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaRegenPauseAttribute()).AddUObject(this, &USSCharacterMovementComponent_Shooter::OnStaminaRegenPauseAttributeChange);

	// Get initial values
	if (IsValid(StaminaSubobject))
	{
		StaminaSubobject->SetMaxStamina(ASC->GetNumericAttribute(USSAttributeSet_Stamina::GetMaxStaminaAttribute()));
		StaminaSubobject->SetStaminaDrain(ASC->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaDrainAttribute()));
		StaminaSubobject->SetStaminaGain(ASC->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaGainAttribute()));
		StaminaSubobject->SetStaminaRegenPause(ASC->GetNumericAttribute(USSAttributeSet_Stamina::GetStaminaRegenPauseAttribute()));
	}
}

//BEGIN Attribute value change delegates
void USSCharacterMovementComponent_Shooter::OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSSCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's MaxStamina value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetMaxStamina(Data.NewValue);
}
void USSCharacterMovementComponent_Shooter::OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSSCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaDrain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaDrain(Data.NewValue);
}
void USSCharacterMovementComponent_Shooter::OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSSCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaGain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaGain(Data.NewValue);
}
void USSCharacterMovementComponent_Shooter::OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogSSCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaRegenPause value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaRegenPause(Data.NewValue);
}
//END Attribute value change delegates


void USSCharacterMovementComponent_Shooter::OnStaminaFullyDrained()
{
	SetWantsToRun(false);
}

bool USSCharacterMovementComponent_Shooter::CanRunInCurrentState() const
{
	bool RetVal = Super::CanRunInCurrentState();


	if (StaminaSubobject && StaminaSubobject->Stamina <= 0)
	{
		// Out of stamina
		return false;
	}

	return RetVal;
}

void USSCharacterMovementComponent_Shooter::Run()
{
	Super::Run();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(true);
	}
}
void USSCharacterMovementComponent_Shooter::UnRun()
{
	Super::UnRun();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(false);
	}
}


FString USSCharacterMovementComponent_Shooter::GetMovementName() const
{
	if (MovementMode == MOVE_Custom)
	{
		const UEnum* ShooterCustomMovementModeEnum = FindObject<const UEnum>(ANY_PACKAGE, TEXT("ESSCustomMovementMode_Shooter"));
		if (IsValid(ShooterCustomMovementModeEnum))
		{
			// If this value is in our custom movement enum
			if (ShooterCustomMovementModeEnum->IsValidEnumValue(CustomMovementMode))
			{
				// Return the display name
				return ShooterCustomMovementModeEnum->GetDisplayNameTextByValue(CustomMovementMode).ToString();
			}
		}
	}

	return Super::GetMovementName();
}

void USSCharacterMovementComponent_Shooter::TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const
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

void USSCharacterMovementComponent_Shooter::BeginDestroy()
{
	//BEGIN Attribute value change delegates
	if (UAbilitySystemComponent* ASC = OwnerASC.Get())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetMaxStaminaAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaDrainAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaGainAttribute()).RemoveAll(this);
		ASC->GetGameplayAttributeValueChangeDelegate(USSAttributeSet_Stamina::GetStaminaRegenPauseAttribute()).RemoveAll(this);
	}
	//END Attribute value change delegates


	Super::BeginDestroy();
}
