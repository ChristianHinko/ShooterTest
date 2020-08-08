// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AbilitySystemActor.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Actor/AS_Actor.h"



void AAbilitySystemActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AAbilitySystemActor, ActorAttributeSet);
	DOREPLIFETIME_CONDITION(AAbilitySystemActor, ActorAbilitySpecHandle, COND_OwnerOnly);
	//DOREPLIFETIME(AAbilitySystemActor, ActorAbilitySystemComponent);			//can be helpful for debugging
}

// Sets default values
AAbilitySystemActor::AAbilitySystemActor()
{
	// Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	ActorAbilitySystemComponentReplicationMode = EGameplayEffectReplicationMode::Minimal;

	bAbilitySystemSetupInitialized = false;

	ActorAbilitySystemComponent = CreateDefaultSubobject<USSAbilitySystemComponent>(TEXT("ActorAbilitySystemComponent"));
	if (ActorAbilitySystemComponent)
	{
		ActorAbilitySystemComponent->SetReplicationMode(ActorAbilitySystemComponentReplicationMode);
		ActorAbilitySystemComponent->SetIsReplicated(true);
	}
}


void AAbilitySystemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	SetupWithAbilitySystem();
}

void AAbilitySystemActor::SetupWithAbilitySystem()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}

	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("%s() Failed to setup Actor (failed to InitAbilityActorInfo, AddExistingAttributeSets, InitializeAttributes, ApplyStartupEffects, and GrantStartingAbilities. GetAbilitySystemComponent() returned null"), *FString(__FUNCTION__));
		return;
	}



	if (!bAbilitySystemSetupInitialized)
	{
		//From my understanding, only needs to be done on server since no player is controlling it
		ActorAbilitySystemComponent->InitAbilityActorInfo(this, this);

		// Must run these on Server but we run them on client too so that we don't have to wait.. It's how Dan does it so seams legit
		CreateAttributeSets();
		RegisterAttributeSets();
		// Must call ForceReplication after registering an attribute set(s)
		ActorAbilitySystemComponent->ForceReplication();
		InitializeAttributes();
		ApplyStartupEffects();
		GrantStartingAbilities();

		bAbilitySystemSetupInitialized = true;
	}
}

#pragma region ASC Setup Helpers
void AAbilitySystemActor::CreateAttributeSets()
{
	if (!ActorAttributeSet)
	{
		ActorAttributeSet = NewObject<UAS_Actor>(this, UAS_Actor::StaticClass(), TEXT("ActorAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *ActorAttributeSet->GetName());
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

void AAbilitySystemActor::RegisterAttributeSets()
{
	// give the ASC the default Actor attribute set
	if (ActorAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(ActorAttributeSet))	// If ActorAttributeSet is valid and it's not yet registered with the Actor's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(ActorAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogAbilitySystemSetup, Warning, TEXT("%s() ActorAttributeSet was either NULL or already added to the Actor's ASC. Actor: %s"), *FString(__FUNCTION__), *GetName());
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

void AAbilitySystemActor::InitializeAttributes()
{
	if (!GetAbilitySystemComponent())
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("GetAbilitySystemComponent() returned null on %s"), *FString(__FUNCTION__));
		return;
	}
	if (!DefaultAttributeValuesEffect)
	{
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Missing DefaultAttributeValuesEffect for %s. Please fill DefaultAttributeValuesEffect in the Actor's Blueprint."), *FString(__FUNCTION__), *GetName());
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
		UE_LOG(LogAbilitySystemSetup, Warning, TEXT("%s() Tried to apply the default attributes effect on %s but failed. Maybe check if you filled out your DefaultAttributeValuesEffect correctly in Actor Blueprint"), *FString(__FUNCTION__), *GetName());
	}
}

void AAbilitySystemActor::ApplyStartupEffects()
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

bool AAbilitySystemActor::GrantStartingAbilities()
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
	ActorAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(ActorAbilityTSub, this, EAbilityInputID::Interact/*, GetLevel()*/);

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
