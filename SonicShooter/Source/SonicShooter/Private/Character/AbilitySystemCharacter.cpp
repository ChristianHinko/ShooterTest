// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AbilitySystemCharacter.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Player/SSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Player/AS_PlayerState.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SonicShooter/Private/Utilities/LogCategories.h"
#include "Character/AS_Character.h"
#include "Actor/AS_Health.h"

#include "Character/SSCharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"




void AAbilitySystemCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AAbilitySystemCharacter, CharacterAttributeSet);
	DOREPLIFETIME(AAbilitySystemCharacter, HealthAttributeSet);
	DOREPLIFETIME_CONDITION(AAbilitySystemCharacter, CharacterJumpAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AAbilitySystemCharacter, CharacterCrouchAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AAbilitySystemCharacter, CharacterRunAbilitySpecHandle, COND_OwnerOnly);
	//DOREPLIFETIME(AAbilitySystemCharacter, PlayerAbilitySystemComponent);			//can be helpful for debugging
}


AAbilitySystemCharacter::AAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AIAbilitySystemComponentReplicationMode = EGameplayEffectReplicationMode::Minimal;
	bUnregisterAttributeSetsOnUnpossessed = true;
	bRemoveAbilitiesOnUnpossessed = true;
	bRemoveCharacterTagsOnUnpossessed = true;

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


void AAbilitySystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


#pragma region Ability System Possess
USSAbilitySystemComponent* AAbilitySystemCharacter::GetAbilitySystemComponent() const
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

void AAbilitySystemCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	SetupWithAbilitySystem();
}

void AAbilitySystemCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// make sure its not when unpossessing (when unpossessed player state is null)
	if (GetPlayerState())
	{
		SetupWithAbilitySystem();
	}
}

void AAbilitySystemCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();


	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RefreshAbilityActorInfo();		// COME BACK TO THIS. ONLY REASON I HAVE THIS HERE RN IS BECAUSE KAOSSPECRUM SAID TO REFRESH IN HERE. i think it's mainly for AIs
	}
}

void AAbilitySystemCharacter::SetupWithAbilitySystem()
{
	if (IsPlayerControlled())
	{
		SSPlayerState = GetPlayerState<ASSPlayerState>();
		if (!SSPlayerState)
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Character with GAS on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). Character's player state is not an ASSPlayerState (Cast failed)"), *FString(__FUNCTION__));
			return;
		}
		PlayerAbilitySystemComponent = SSPlayerState->GetAbilitySystemComponent();
		if (!PlayerAbilitySystemComponent)
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Character with GAS on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). PlayerAbilitySystemComponent was NULL"), *FString(__FUNCTION__));
			return;
		}
		if (GetAbilitySystemComponent() != PlayerAbilitySystemComponent)	// Check to make sure GetAbilitySystemComponent() returns the same ASC we are now trying to set up and switch to
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() GetAbilitySystemComponent() not returning PlayerAbilitySystemComponent when a PlayerController just took possesion and is trying to InitAbilityActorInfo() on the character"), *FString(__FUNCTION__));
			return;
		}


		// This must be done on both client and server
		PlayerAbilitySystemComponent->InitAbilityActorInfo(SSPlayerState, this);

		// Bind player input to the AbilitySystemComponent. Also called in SetupPlayerInputComponent because of a potential race condition.
		BindASCInput();

		if (!bAttributesAndStartupEffectsInitialized)
		{


			if (GetLocalRole() == ROLE_Authority)
			{
				// Moved these attribute set stuff into this check because seems to make more sence. move outside if problems arise
				CreateAttributeSets();
				RegisterAttributeSets();
				// Must call ForceReplication after registering an attribute set(s)
				PlayerAbilitySystemComponent->ForceReplication();
			}
			
			PreApplyStartupEffects.Broadcast();	// Good place to bind to Attribute/Tag events, but currently effect replicates to client faster than it can broadcast, so we need to fix this

			if (GetLocalRole() == ROLE_Authority)
			{
				InitializeAttributes();
				ApplyStartupEffects();
			}

			bAttributesAndStartupEffectsInitialized = true;
		}
		else    // If something is posessing this Character a second time
		{
			// Just register this Character's already-created attribute sets with the player's ASC
			RegisterAttributeSets();
			if (GetLocalRole() == ROLE_Authority)
			{
				// Must call ForceReplication after registering an attribute set(s)
				PlayerAbilitySystemComponent->ForceReplication();
			}
		}

		// Refresh ASC Actor Info for clients. Server will be refreshed by its AIController/PlayerController when it possesses a new Actor.
		if (IsLocallyControlled()) // CLIENT
		{
			PlayerAbilitySystemComponent->RefreshAbilityActorInfo();
			ServerOnSetupWithAbilitySystemCompletedOnOwningClient();
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
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Character with AI GAS setup on (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities). AIAbilitySystemComponent was NULL"), *FString(__FUNCTION__));
			return;
		}
		if (GetAbilitySystemComponent() != AIAbilitySystemComponent)	// Check to make sure GetAbilitySystemComponent() returns the same ASC we are now trying to set up and switch to
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() GetAbilitySystemComponent() not returning AIAbilitySystemComponent when an AIController just took possesion and is trying to InitAbilityActorInfo() on the character"), *FString(__FUNCTION__));
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
			PreApplyStartupEffects.Broadcast();					// at this point the asc is safe to use
			InitializeAttributes();
			ApplyStartupEffects();

			bAttributesAndStartupEffectsInitialized = true;
		}
		else    // If something is posessing this Character a second time
		{
			// Just register this Character's already-created attribute sets with the player's ASC
			RegisterAttributeSets();
			// Must call ForceReplication after registering an attribute set(s)
			AIAbilitySystemComponent->ForceReplication();
		}
		// When posessing this Character always grant the player's ASC his starting abilities. Also since this is an AI we don't need to wait for client to setup to grant abilities
		GrantStartingAbilities();	//Come back to this later. Things like character earned abilities WILL NOT BE GIVEN ON POSSESSION
		GrantNonHandleStartingAbilities();
	}

	SetupWithAbilitySystemCompleted.Broadcast();
}
#pragma endregion

bool AAbilitySystemCharacter::ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Validate()
{
	return true;
}
void AAbilitySystemCharacter::ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Implementation()
{
	// Wanted to make it clear that THIS IS NOT HOW THINGS SHOULD BE IMPLEMENTED. This RPC makes the server wait on the client to grant the ability which can be bad. Initially I thought the server needed to wait for the client or something, but I no longer think that is the case anymore since solving this race condition by RPCing is basicly the same thing as solving it using a delay node.
	// Fix in GameTemplate!

	// When posessing this Character always grant the player's ASC his starting abilities
	GrantStartingAbilities();	//Come back to this later. Things like character earned abilities WILL NOT BE GIVEN ON POSSESSION
	GrantNonHandleStartingAbilities();

	OnServerAknowledgeClientSetupAbilitySystem.Broadcast();
}

#pragma region ASC Setup Helpers
void AAbilitySystemCharacter::CreateAttributeSets()
{
	if (!CharacterAttributeSet)
	{
		CharacterAttributeSet = NewObject<UAS_Character>(this, UAS_Character::StaticClass(), TEXT("CharacterAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *CharacterAttributeSet->GetName());
	}

	if (!HealthAttributeSet)
	{
		HealthAttributeSet = NewObject<UAS_Health>(this, UAS_Health::StaticClass(), TEXT("HealthAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *HealthAttributeSet->GetName());
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

void AAbilitySystemCharacter::RegisterAttributeSets()
{
	// give the ASC the default Character attribute set
	if (CharacterAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(CharacterAttributeSet))	// If CharacterAttributeSet is valid and it's not yet registered with the Character's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(CharacterAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() CharacterAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}

	if (HealthAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(HealthAttributeSet))	// If HealthAttributeSet is valid and it's not yet registered with the Character's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(HealthAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() HealthAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
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
					UE_CLOG((GetLocalRole() == ROLE_Authority), LogTemp, Warning, TEXT("%s() MyAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
				}
	*/
	// -------------------------------------------------------------------------------------------------- //


}

void AAbilitySystemCharacter::InitializeAttributes()
{
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("GetAbilitySystemComponent() returned null on %s"), *FString(__FUNCTION__));
		return;
	}
	if (!DefaultAttributeValuesEffectTSub)
	{
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Missing DefaultAttributeValuesEffect for %s. Please fill DefaultAttributeValuesEffect in the Character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddInstigator(this, this);
	EffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle NewEffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributeValuesEffectTSub, 1/*GetLevel()*/, EffectContextHandle);
	if (NewEffectSpecHandle.IsValid())
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*NewEffectSpecHandle.Data.Get());
	}
	else
	{
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Tried to apply the default attributes effect on %s but failed. Maybe check if you filled out your DefaultAttributeValuesEffect correctly in character Blueprint"), *FString(__FUNCTION__), *GetName());
	}
}

void AAbilitySystemCharacter::ApplyStartupEffects()
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

bool AAbilitySystemCharacter::GrantStartingAbilities()
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
	CharacterJumpAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(CharacterJumpAbilityTSub, this, EAbilityInputID::Jump/*, GetLevel()*/);
	CharacterCrouchAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(CharacterCrouchAbilityTSub, this, EAbilityInputID::Crouch/*, GetLevel()*/);
	CharacterRunAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(CharacterRunAbilityTSub, this, EAbilityInputID::Run/*, GetLevel()*/);

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

void AAbilitySystemCharacter::GrantNonHandleStartingAbilities()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to grant NonHandleStartingAbilities on %s but GetAbilitySystemComponent() returned NULL"), *FString(__FUNCTION__), *GetName());
		return;
	}

	// GetLevel() doesn't exist in this template. Will need to implement one if you want a level system
	for (int i = 0; i < NonHandleStartingAbilities.Num(); i++)
	{
		GetAbilitySystemComponent()->GrantAbility(NonHandleStartingAbilities[i], this, EAbilityInputID::None/*, GetLevel()*/);
	}
}
#pragma endregion

#pragma region Input
void AAbilitySystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("ConfirmTarget", IE_Pressed, this, &AAbilitySystemCharacter::OnConfirmTargetPressed);
	PlayerInputComponent->BindAction("ConfirmTarget", IE_Released, this, &AAbilitySystemCharacter::OnConfirmTargetReleased);

	PlayerInputComponent->BindAction("CancelTarget", IE_Pressed, this, &AAbilitySystemCharacter::OnCancelTargetPressed);
	PlayerInputComponent->BindAction("CancelTarget", IE_Released, this, &AAbilitySystemCharacter::OnCancelTargetReleased);

	// Bind player input to the AbilitySystemComponent. Also called in OnRep_PlayerState because of a potential race condition.
	BindASCInput();
}

void AAbilitySystemCharacter::BindASCInput()
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
				FString("EAbilityInputID")		// Name of our GAS input enum that gives the names of the rest of our inputs in the project settings
			)
		);

		bASCInputBound = true;	// Only run this function only once
	}
}
//----------------------------------------------------------------------------- \/\/\/\/ EVENTS \/\/\/\/ ------------------------


void AAbilitySystemCharacter::OnConfirmTargetPressed()
{
	GetAbilitySystemComponent()->LocalInputConfirm();
}
void AAbilitySystemCharacter::OnConfirmTargetReleased()
{

}

void AAbilitySystemCharacter::OnCancelTargetPressed()
{
	GetAbilitySystemComponent()->LocalInputCancel();
}
void AAbilitySystemCharacter::OnCancelTargetReleased()
{

}

void AAbilitySystemCharacter::OnInteractPressed()
{
	
}
void AAbilitySystemCharacter::OnInteractReleased()
{

}

void AAbilitySystemCharacter::OnPrimaryFirePressed()
{
	
}
void AAbilitySystemCharacter::OnPrimaryFireReleased()
{

}
#pragma endregion


#pragma region Ability System Unpossess
int32 AAbilitySystemCharacter::UnregisterCharacterOwnedAttributeSets()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return 0;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to remove Character owned attribute sets from ASC before the Character gets destroyed but GetAbilitySystemComponent() returned NULL. ASC probably now has unneeded attribute sets and possibly attribute set duplicates now (very bad). Character: %s"), *FString(__FUNCTION__), *GetName());
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

int32 AAbilitySystemCharacter::RemoveCharacterOwnedAbilities()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return 0;
	}
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Tried to remove Character owned abilities from ASC before the Character gets destroyed but GetAbilitySystemComponent() returned NULL. ASC probably now has unneeded abilitie(s) and possibly duplicates. Character: %s"), *FString(__FUNCTION__), *GetName());
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

void AAbilitySystemCharacter::RemoveAllCharacterTags()	// Only called on Authority
{
	//	Needs implementation. Below I was trying to find a way to get all tags containing a parent of Character.
	//int32 amountFound = GetAbilitySystemComponent()->GetTagCount(FGameplayTag::RequestGameplayTag("Character"));
}

void AAbilitySystemCharacter::UnPossessed()
{
	//this goes before Super because we need to make sure we are dealing with the correct ASC (the old one)
	if (IsPlayerControlled() || (!IsPlayerControlled() && bShouldHandleAIAbilitySystemSetup))	//	If you were a player or were an AI with the AIAbilitySystemComponent subobject
	{
		if (bUnregisterAttributeSetsOnUnpossessed)
		{
			UnregisterCharacterOwnedAttributeSets();
		}
		if (bRemoveAbilitiesOnUnpossessed)
		{
			RemoveCharacterOwnedAbilities();
		}
		if (bRemoveCharacterTagsOnUnpossessed)
		{
			RemoveAllCharacterTags();
		}
	}
	
	Super::UnPossessed(); // actual unpossession happens here



}
#pragma endregion
