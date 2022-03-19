// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMC_Shooter.h"

#include "Engine/ActorChannel.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "Subobjects/O_Stamina.h"
#include "GameFramework/Character.h"
#include "Utilities/LogCategories.h"
#include "AbilitySystemSetupComponent/AbilitySystemSetupInterface.h"
#include "AbilitySystemSetupComponent/AbilitySystemSetupComponent.h"

#include "Kismet/KismetSystemLibrary.h"



bool UCMC_Shooter::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
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

UCMC_Shooter::UCMC_Shooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCrouchCancelsDesireToRun = true;
	bRunCancelsDesireToCrouch = true;
	bJumpCancelsDesireToCrouch = true;
	bJumpCancelsDesireToRun = false;


	bCanCrouchJump = false;
	bCanWalkOffLedgesWhenCrouching = true;

	StaminaSubobject = CreateDefaultSubobject<UO_Stamina>(TEXT("StaminaSubobject"));
	if (StaminaSubobject)
	{
		StaminaSubobject->OnStaminaFullyDrained.AddUObject(this, &UCMC_Shooter::OnStaminaFullyDrained);
	}
}

//BEGIN Prediciton Data Client
FNetworkPredictionData_Client* UCMC_Shooter::GetPredictionData_Client() const
{
	if (ClientPredictionData == nullptr)
	{
		// Return our custom client prediction struct instead
		UCMC_Shooter* MutableThis = const_cast<UCMC_Shooter*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_Shooter(*this);
	}

	return ClientPredictionData;
}

FNetworkPredictionData_Client_Shooter::FNetworkPredictionData_Client_Shooter(const UCharacterMovementComponent& ClientMovement)
	: Super(ClientMovement)
{

}
FSavedMovePtr FNetworkPredictionData_Client_Shooter::AllocateNewMove()
{
	// Return our custom move struct instead
	return FSavedMovePtr(new FSavedMove_Shooter());
}
//END Prediciton Data Client

void UCMC_Shooter::OnAbilitySystemSetUp(UAbilitySystemComponent* const PreviousASC, UAbilitySystemComponent* const NewASC)
{
	Super::OnAbilitySystemSetUp(PreviousASC, NewASC);


	if (IsValid(OwnerASC))
	{
		// Bind to Attribute value change delegates
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetMaxStaminaAttribute()).AddUObject(this, &UCMC_Shooter::OnMaxStaminaAttributeChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaDrainAttribute()).AddUObject(this, &UCMC_Shooter::OnStaminaDrainAttributeChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaGainAttribute()).AddUObject(this, &UCMC_Shooter::OnStaminaGainAttributeChange);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaRegenPauseAttribute()).AddUObject(this, &UCMC_Shooter::OnStaminaRegenPauseAttributeChange);

		// Get initial values
		if (IsValid(StaminaSubobject))
		{
			StaminaSubobject->SetMaxStamina(OwnerASC->GetNumericAttribute(UAS_Stamina::GetMaxStaminaAttribute()));
			StaminaSubobject->SetStaminaDrain(OwnerASC->GetNumericAttribute(UAS_Stamina::GetStaminaDrainAttribute()));
			StaminaSubobject->SetStaminaGain(OwnerASC->GetNumericAttribute(UAS_Stamina::GetStaminaGainAttribute()));
			StaminaSubobject->SetStaminaRegenPause(OwnerASC->GetNumericAttribute(UAS_Stamina::GetStaminaRegenPauseAttribute()));
		}
	}
}

//BEGIN Attribute value change delegates
void UCMC_Shooter::OnMaxStaminaAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's MaxStamina value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetMaxStamina(Data.NewValue);
}
void UCMC_Shooter::OnStaminaDrainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaDrain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaDrain(Data.NewValue);
}
void UCMC_Shooter::OnStaminaGainAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaGain value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaGain(Data.NewValue);
}
void UCMC_Shooter::OnStaminaRegenPauseAttributeChange(const FOnAttributeChangeData& Data)
{
	if (!IsValid(StaminaSubobject))
	{
		UE_LOG(LogCharacterMovement, Warning, TEXT("%s() Couldn't update StaminaSubobject's StaminaRegenPause value - StaminaSubobject was not valid"), ANSI_TO_TCHAR(__FUNCTION__));
		check(0);
		return;
	}

	StaminaSubobject->SetStaminaRegenPause(Data.NewValue);
}
//END Attribute value change delegates


void UCMC_Shooter::OnStaminaFullyDrained()
{
	SetWantsToRun(false);
}

bool UCMC_Shooter::CanRunInCurrentState() const
{
	bool RetVal = Super::CanRunInCurrentState();


	if (StaminaSubobject && StaminaSubobject->Stamina <= 0)
	{
		// Out of stamina
		return false;
	}

	return RetVal;
}

void UCMC_Shooter::Run()
{
	Super::Run();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(true);
	}
}
void UCMC_Shooter::UnRun()
{
	Super::UnRun();

	if (StaminaSubobject)
	{
		StaminaSubobject->SetStaminaDraining(false);
	}
}

void UCMC_Shooter::TweakWantsToRunBeforeTick(bool& outTweakedWantsToRun) const
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

void UCMC_Shooter::BeginDestroy()
{
	//BEGIN Attribute value change delegates
	if (IsValid(OwnerASC))
	{
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetMaxStaminaAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaDrainAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaGainAttribute()).RemoveAll(this);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UAS_Stamina::GetStaminaRegenPauseAttribute()).RemoveAll(this);
	}
	//END Attribute value change delegates


	Super::BeginDestroy();
}
