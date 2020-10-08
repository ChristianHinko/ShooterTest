// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/AbilitySystemPawn.h"

#include "Net/UnrealNetwork.h"
#include "Player/SSPlayerState.h"
#include "Player/AS_PlayerState.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Pawn/AS_Pawn.h"

#include "Kismet/KismetSystemLibrary.h"



void AAbilitySystemPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AAbilitySystemPawn, PawnAttributeSet);
	//DOREPLIFETIME(AAbilitySystemPawn, PlayerAbilitySystemComponent);			//can be helpful for debugging
}


AAbilitySystemPawn::AAbilitySystemPawn()
{
	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AIAbilitySystemComponentReplicationMode = EGameplayEffectReplicationMode::Minimal;
	bUnregisterAttributeSetsOnUnpossessed = true;
	bRemoveAbilitiesOnUnpossessed = true;
	bRemovePawnTagsOnUnpossessed = true;

	bAttributesAndStartupEffectsInitialized = false;
	bASCInputBound = false;

	bShouldHandleAIAbilitySystemSetup = false;
	AIAbilitySystemComponent = CreateOptionalDefaultSubobject<USSAbilitySystemComponent>(TEXT("AIAbilitySystemComponent"));
	if (AIAbilitySystemComponent)
	{
		bShouldHandleAIAbilitySystemSetup = true;
		AIAbilitySystemComponent->SetReplicationMode(AIAbilitySystemComponentReplicationMode);
		AIAbilitySystemComponent->SetIsReplicated(true);
	}
}


#pragma region Ability System Possess
USSAbilitySystemComponent* AAbilitySystemPawn::GetAbilitySystemComponent() const
{
	if (IsPlayerControlled())
	{
		return PlayerAbilitySystemComponent;
	}
	else
	{
		return AIAbilitySystemComponent;
	}
}

void AAbilitySystemPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	SetupWithAbilitySystem();
}

void AAbilitySystemPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// make sure its not when unpossessing (when unpossessed player state is null)
	if (GetPlayerState())
	{
		SetupWithAbilitySystem();
	}
}

void AAbilitySystemPawn::OnRep_Controller()
{
	Super::OnRep_Controller();


	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RefreshAbilityActorInfo();		// COME BACK TO THIS. ONLY REASON I HAVE THIS HERE RN IS BECAUSE KAOSSPECRUM SAID TO REFRESH IN HERE. i think it's mainly for AIs
	}
}

void AAbilitySystemPawn::SetupWithAbilitySystem()
{
	if (IsPlayerControlled())
	{
		SSPlayerState = GetPlayerState<ASSPlayerState>();
		if (!SSPlayerState)
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Pawn with GAS on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). Pawn's player state is not an ASSPlayerState (Cast failed)"), *FString(__FUNCTION__));
			return;
		}
		PlayerAbilitySystemComponent = SSPlayerState->GetAbilitySystemComponent();
		if (!PlayerAbilitySystemComponent)
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Pawn with GAS on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). PlayerAbilitySystemComponent was NULL"), *FString(__FUNCTION__));
			return;
		}
		if (GetAbilitySystemComponent() != PlayerAbilitySystemComponent)	// Check to make sure GetAbilitySystemComponent() returns the same ASC we are now trying to set up and switch to
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() GetAbilitySystemComponent() not returning PlayerAbilitySystemComponent when a PlayerController just took possesion and is trying to InitAbilityActorInfo() on the pawn"), *FString(__FUNCTION__));
			return;
		}


		// This must be done on both client and server
		PlayerAbilitySystemComponent->InitAbilityActorInfo(SSPlayerState, this);

		// Bind player input to the AbilitySystemComponent. Also called in SetupPlayerInputComponent because of a potential race condition.
		BindASCInput();

		if (!bAttributesAndStartupEffectsInitialized)
		{
			// Must run these on Server but we run them on client too so that we don't have to wait.. It's how Dan does it so seams legit
			CreateAttributeSets();
			RegisterAttributeSets();
			if (GetLocalRole() == ROLE_Authority)
			{
				// Must call ForceReplication after registering an attribute set(s)
				PlayerAbilitySystemComponent->ForceReplication();
			}
			InitializeAttributes();
			ApplyStartupEffects();

			bAttributesAndStartupEffectsInitialized = true;
		}
		else    // If something is posessing this Pawn a second time
		{
			// Just register this Pawn's already-created attribute sets with the player's ASC
			RegisterAttributeSets();
			if (GetLocalRole() == ROLE_Authority)
			{
				// Must call ForceReplication after registering an attribute set(s)
				PlayerAbilitySystemComponent->ForceReplication();
			}
		}
		// When posessing this Pawn always grant the player's ASC his starting abilities
		GrantStartingAbilities();	//Come back to this later. Things like pawn earned abilities WILL NOT BE GIVEN ON POSSESSION


		// Refresh ASC Actor Info for clients. Server will be refreshed by its AIController/PlayerController when it possesses a new Actor.
		if (GetLocalRole() != ROLE_Authority) // CLIENT
		{
			PlayerAbilitySystemComponent->RefreshAbilityActorInfo();
		}
	}
	else // AI controlled   \/\/
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			return;
		}
		if (!bShouldHandleAIAbilitySystemSetup)
		{
			return;
		}
		if (!AIAbilitySystemComponent)
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Pawn with AI GAS setup on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). AIAbilitySystemComponent was NULL"), *FString(__FUNCTION__));
			return;
		}
		if (GetAbilitySystemComponent() != AIAbilitySystemComponent)	// Check to make sure GetAbilitySystemComponent() returns the same ASC we are now trying to set up and switch to
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() GetAbilitySystemComponent() not returning AIAbilitySystemComponent when an AIController just took possesion and is trying to InitAbilityActorInfo() on the pawn"), *FString(__FUNCTION__));
			return;
		}



		//From my understanding, only needs to be done on server since no player is controlling it
		AIAbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (!bAttributesAndStartupEffectsInitialized)
		{
			// Must run these on Server but we run them on client too so that we don't have to wait.. It's how Dan does it so seams legit
			CreateAttributeSets();
			RegisterAttributeSets();
			// Must call ForceReplication after registering an attribute set(s)
			AIAbilitySystemComponent->ForceReplication();
			InitializeAttributes();
			ApplyStartupEffects();

			bAttributesAndStartupEffectsInitialized = true;
		}
		else    // If something is posessing this Pawn a second time
		{
			// Just register this Pawn's already-created attribute sets with the player's ASC
			RegisterAttributeSets();
			// Must call ForceReplication after registering an attribute set(s)
			AIAbilitySystemComponent->ForceReplication();
		}
		// When posessing this Pawn always grant the player's ASC his starting abilities
		GrantStartingAbilities();	//Come back to this later. Things like pawn earned abilities WILL NOT BE GIVEN ON POSSESSION
	}
}
#pragma endregion

#pragma region ASC Setup Helpers
void AAbilitySystemPawn::CreateAttributeSets()
{
	if (!PawnAttributeSet)
	{
		PawnAttributeSet = NewObject<UAS_Pawn>(this, UAS_Pawn::StaticClass(), TEXT("PawnAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *PawnAttributeSet->GetName());
	}



	// Subclasses create extra attribute sets here but only if you want to

	// \/\/\/\/ This is how you should create each of your attribute sets after calling the Super \/\/\/\/
	// ------------------------------------------------------------------------------------------------ //
	/*
				if (!MyAttributeSet)
				{
					MyAttributeSet = NewObject<UAS_MyAttributeSet>(this, UAS_MyAttributeSet::StaticClass(), TEXT("MyAttributeSet"));
				}
				else
				{
					UE_CLOG((GetLocalRole() == ROLE_Authority), LogTemp, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *MyAttributeSet->GetName());
				}
	*/
	// ------------------------------------------------------------------------------------------------ //


}

void AAbilitySystemPawn::RegisterAttributeSets()
{
	// give the ASC the default Pawn attribute set
	if (PawnAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(PawnAttributeSet))	// If PawnAttributeSet is valid and it's not yet registered with the Pawn's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(PawnAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() PawnAttributeSet was either NULL or already added to the pawn's ASC. Pawn: %s"), *FString(__FUNCTION__), *GetName());
	}



	// Subclasses register extra attribute sets here but only if you want to

	// \/\/\/\/ This is how you should register each of your attribute sets after calling the Super \/\/\/\/
	// -------------------------------------------------------------------------------------------------- //
	/*
				if (MyAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(MyAttributeSet))
				{
					GetAbilitySystemComponent()->AddAttributeSetSubobject(MyAttributeSet);
				}
				else
				{
					UE_CLOG((GetLocalRole() == ROLE_Authority), LogTemp, Warning, TEXT("%s() MyAttributeSet was either NULL or already added to the pawn's ASC. Pawn: %s"), *FString(__FUNCTION__), *GetName());
				}
	*/
	// -------------------------------------------------------------------------------------------------- //


}

void AAbilitySystemPawn::InitializeAttributes()
{
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("GetAbilitySystemComponent() returned null on %s"), *FString(__FUNCTION__));
		return;
	}
	if (!DefaultAttributeValuesEffect)
	{
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Missing DefaultAttributeValuesEffect for %s. Please fill DefaultAttributeValuesEffect in the Pawn's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddInstigator(this, this);
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle NewEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributeValuesEffect, 1/*GetLevel()*/, EffectContextHandle);
	if (NewEffectSpecHandle.IsValid())
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*NewEffectSpecHandle.Data.Get());
	}
	else
	{
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Tried to apply the default attributes effect on %s but failed. Maybe check if you filled out your DefaultAttributeValuesEffect correctly in pawn Blueprint"), *FString(__FUNCTION__), *GetName());
	}
}

void AAbilitySystemPawn::ApplyStartupEffects()
{
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to apply startup effects on %s but GetAbilitySystemComponent() returned NULL"), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddInstigator(this, this);
	EffectContextHandle.AddSourceObject(this);
	for (int32 i = 0; i < EffectsToApplyOnStartup.Num(); i++)
	{
		FGameplayEffectSpecHandle NewEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectsToApplyOnStartup[i], 1/*GetLevel()*/, EffectContextHandle);
		if (NewEffectSpecHandle.IsValid())
		{
			GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*NewEffectSpecHandle.Data.Get());
		}
	}
}

bool AAbilitySystemPawn::GrantStartingAbilities()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return false;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to grant startup abilities on %s but GetAbilitySystemComponent() returned NULL"), *FString(__FUNCTION__), *GetName());
		return false;
	}


	// GetLevel() doesn't exist in this template. Will need to implement one if you want a level system


	return true;

	// \/\/\/\/ This should be your first bit of code in your overrided implementation \/\/\/\/
	// ------------------------------------------------------------------------------------- //
	/*
					if (Super::GrantStartingAbilities() == false)
					{
						return false;	// Did not pass predefined checks
					}
					//	We are on authority and have a valid ASC to work with
	*/
	// ------------------------------------------------------------------------------------- //
}
#pragma endregion

#pragma region Input
void AAbilitySystemPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("ConfirmTarget", IE_Pressed, this, &AAbilitySystemPawn::OnConfirmTargetPressed);
	PlayerInputComponent->BindAction("ConfirmTarget", IE_Released, this, &AAbilitySystemPawn::OnConfirmTargetReleased);

	PlayerInputComponent->BindAction("CancelTarget", IE_Pressed, this, &AAbilitySystemPawn::OnCancelTargetPressed);
	PlayerInputComponent->BindAction("CancelTarget", IE_Released, this, &AAbilitySystemPawn::OnCancelTargetReleased);

	// Bind player input to the AbilitySystemComponent. Also called in OnRep_PlayerState because of a potential race condition.
	BindASCInput();
}

void AAbilitySystemPawn::BindASCInput()
{
	if (!bASCInputBound && IsValid(GetAbilitySystemComponent()) && IsValid(InputComponent))
	{
		GetAbilitySystemComponent()->BindAbilityActivationToInputComponent
		(
			InputComponent,
			FGameplayAbilityInputBinds
			(
				FString("ConfirmTarget"),		// Name of our confirm input from the project settings
				FString("CancelTarget"),		// Name of our cancel input from the project settings
				FString("EAbilityInputID")	// Name of our GAS input enum that gives the names of the rest of our inputs in the project settings
			)
		);

		bASCInputBound = true;	// Only run this function only once
	}
}
//----------------------------------------------------------------------------- \/\/\/\/ EVENTS \/\/\/\/ ------------------------


void AAbilitySystemPawn::OnConfirmTargetPressed()
{
	GetAbilitySystemComponent()->LocalInputConfirm();
}
void AAbilitySystemPawn::OnConfirmTargetReleased()
{

}

void AAbilitySystemPawn::OnCancelTargetPressed()
{
	GetAbilitySystemComponent()->LocalInputCancel();
}
void AAbilitySystemPawn::OnCancelTargetReleased()
{

}

void AAbilitySystemPawn::OnJumpPressed()
{
	
}
void AAbilitySystemPawn::OnJumpReleased()
{

}

void AAbilitySystemPawn::OnRunPressed()
{
	
}
void AAbilitySystemPawn::OnRunReleased()
{

}
#pragma endregion

#pragma region Ability System Unpossess
int32 AAbilitySystemPawn::UnregisterPawnOwnedAttributeSets()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return 0;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to remove Pawn owned attribute sets from ASC before the Pawn gets destroyed but GetAbilitySystemComponent() returned NULL. ASC probably now has unneeded attribute sets and possibly attribute set duplicates now (very bad). Pawn: %s"), *FString(__FUNCTION__), *GetName());
		return 0;
	}

	int32 retVal = 0;
	for (int32 i = GetAbilitySystemComponent()->SpawnedAttributes.Num() - 1; i >= 0; i--)
	{
		if (UAttributeSet* AS = GetAbilitySystemComponent()->SpawnedAttributes[i])
		{
			if (AS->GetOwningActor() == this)	// for attribute sets we check the OwningActor since thats what they use. It's also automatically set by the engine so were good
			{
				GetAbilitySystemComponent()->SpawnedAttributes.RemoveAt(i);
				retVal++;
			}
		}
	}
	GetAbilitySystemComponent()->ForceReplication();

	return retVal;
}

int32 AAbilitySystemPawn::RemovePawnOwnedAbilities()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return 0;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to remove Pawn owned abilities from ASC before the Pawn gets destroyed but GetAbilitySystemComponent() returned NULL. ASC probably now has unneeded abilitie(s) and possibly duplicates. Pawn: %s"), *FString(__FUNCTION__), *GetName());
		return 0;
	}

	int32 retVal = 0;
	for (int32 i = GetAbilitySystemComponent()->GetActivatableAbilities().Num() - 1; i >= 0; i--)
	{
		FGameplayAbilitySpec Spec = GetAbilitySystemComponent()->GetActivatableAbilities()[i];
		if (Spec.SourceObject == this)	// for abilities we check the SourceObject since thats what they use. SourceObjects are expected to be correct when set on GrantAbility()
		{
			GetAbilitySystemComponent()->ClearAbility(Spec.Handle);
			retVal++;
		}
	}

	return retVal;
}

void AAbilitySystemPawn::RemoveAllPawnTags()	// Only called on Authority
{
	//	Needs implementation. Below I was trying to find a way to get all tags containing a parent of Pawn.
	//int32 amountFound = GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag("Pawn"));
}

void AAbilitySystemPawn::UnPossessed()
{
	//this goes before Super because we need to make sure we are dealing with the correct ASC (the old one)
	if (IsPlayerControlled() || (!IsPlayerControlled() && bShouldHandleAIAbilitySystemSetup))	//	If you were a player or were an AI with the AIAbilitySystemComponent subobject
	{
		if (bUnregisterAttributeSetsOnUnpossessed)
		{
			UnregisterPawnOwnedAttributeSets();
		}
		if (bRemoveAbilitiesOnUnpossessed)
		{
			RemovePawnOwnedAbilities();
		}
		if (bRemovePawnTagsOnUnpossessed)
		{
			RemoveAllPawnTags();
		}
	}

	Super::UnPossessed(); // actual unpossession happens here



}
#pragma endregion
