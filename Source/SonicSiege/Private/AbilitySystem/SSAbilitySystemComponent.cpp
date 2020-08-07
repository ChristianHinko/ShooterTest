// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SSAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"
#include "AbilitySystem/SSGameplayAbility.h"
#include "GameplayCueManager.h"
#include "SonicSiege/Private/Utilities/LogCategories.h"
#include "Abilities/GameplayAbilityTargetActor.h"



USSAbilitySystemComponent::USSAbilitySystemComponent()
{
	// Some projects may want to use GAS' automatic input binding by default. Set these to false if you do		=@REVIEW MARKER@=
	bDoNotAutoActivateFromGASBindings = true;
	// If false, this one will automatially trigger confirmation / cancellation for target actors
	bDoNotAutoConfirmAndCancelFromGASBindings = true;


	/** The linked Anim Instance that this component will play montages in. Use NAME_None for the main anim instance. (Havn't explored this much yet)*/
	AffectedAnimInstanceTag = NAME_None;
}


/*
	Wrapper version of GiveAbility. Always call this instead for our games. InSourceObject is the actor that owns the granted ability. Make sure InSourceObject isset to a meaningful value (shouldn't pass null for it).
	By default this method will look at the ability's AbilityInputID variable and use that as the ability's inputID. But if you specify one it will override it.
*/
FGameplayAbilitySpecHandle USSAbilitySystemComponent::GrantAbility(TSubclassOf<USSGameplayAbility> NewAbility, UObject* InSourceObject, EAbilityInputID inputID, int32 level)
{
	if (IsOwnerActorAuthoritative() == false)
	{
		return FGameplayAbilitySpecHandle();
	}

	if (NewAbility)
	{
		USSGameplayAbility* AbilityToGive = NewAbility.GetDefaultObject();
		ActivatableAbilities;
		// if we don't have the ability yet give it, else log an error and let it return an invalid spec handle
		if (GetActivatableAbilities().ContainsByPredicate([&AbilityToGive](const FGameplayAbilitySpec& Spec) { return Spec.Ability == AbilityToGive; }) == false)
		{
			return GiveAbility(FGameplayAbilitySpec(AbilityToGive, level, static_cast<int32>(inputID), InSourceObject));
		}
		else
		{
			UE_LOG(LogAbilitySystemSetup, Error, TEXT("Tried granting an already-activatable ability. %s was not granted"), *(AbilityToGive->GetName()));
		}
	}
	else
	{
		UE_LOG(LogAbilitySystemSetup, Error, TEXT("Could'nt grant ability. NewAbility was null"));
	}
	return FGameplayAbilitySpecHandle();
}

void USSAbilitySystemComponent::TargetConfirmByAbility(UGameplayAbility* AbilityToConfirmTargetOn)
{
	// this code is taken from TargetConfirm in AbilitySystemComponent_Abilities and
	// modified to only confirm targeting to the target actor(s?) associated with the AbilityToConfirmTargetOn

	// Callbacks may modify the spawned target actor array so iterate over a copy instead
	TArray<AGameplayAbilityTargetActor*> LocalTargetActors = SpawnedTargetActors;
	SpawnedTargetActors.Reset();
	for (AGameplayAbilityTargetActor* TargetActor : LocalTargetActors)
	{
		if (TargetActor)
		{
			if (TargetActor->IsConfirmTargetingAllowed())
			{
				if (TargetActor->OwningAbility == AbilityToConfirmTargetOn)						// <-- our added if statement
				{
					//TODO: There might not be any cases where this bool is false
					if (!TargetActor->bDestroyOnConfirmation)
					{
						SpawnedTargetActors.Add(TargetActor);
					}
					TargetActor->ConfirmTargeting();
				}
			}
			else
			{
				SpawnedTargetActors.Add(TargetActor);
			}
		}
	}
}

void USSAbilitySystemComponent::TargetCancelByAbility(UGameplayAbility* AbilityToCancelTargetOn)
{
	// this code is taken from TargetCancel in AbilitySystemComponent_Abilities and
	// modified to re-add the target actors that are not associated with the AbilityToCancelTargetOn

	// Callbacks may modify the spawned target actor array so iterate over a copy instead
	TArray<AGameplayAbilityTargetActor*> LocalTargetActors = SpawnedTargetActors;
	SpawnedTargetActors.Reset();
	for (AGameplayAbilityTargetActor* TargetActor : LocalTargetActors)
	{
		if (TargetActor)
		{
			if (TargetActor->OwningAbility == AbilityToCancelTargetOn)							// <-- our added if statement
			{
				TargetActor->CancelTargeting();
			}
			else																				// <-- our added else statement
			{
				SpawnedTargetActors.Add(TargetActor);
			}
		}
	}
}

#pragma region Input Binding
/*
	this is the same thing as the Super exept it doesn't force the Confirm/Cancel binding to confirm/cancel the target actor directly.
	We added a bool (bDoNotAutoConfirmAndCancelFromGASBindings) - set this to false to if you want Confirm/Cancel bindings to directly confirm / cancel the target actors.
	If you set this bool to false, make sure you get rid of the LocalInputConfirm / Cancel in the OnConfirmTargetPressed / Released and OnCancelTargetPressed / Released implementations in
	the AbilitySystemCharacter so that it doesn't double fire LocalInputConfirm and LocalInputCancel
*/
void USSAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
	UEnum* EnumBinds = BindInfo.GetBindEnum();

	SetBlockAbilityBindingsArray(BindInfo);

	for (int32 idx = 0; idx < EnumBinds->NumEnums(); ++idx)
	{
		const FString FullStr = EnumBinds->GetNameStringByIndex(idx);

		// Pressed event
		{
			FInputActionBinding AB(FName(*FullStr), IE_Pressed);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::AbilityLocalInputPressed, idx);
			InputComponent->AddActionBinding(AB);
		}

		// Released event
		{
			FInputActionBinding AB(FName(*FullStr), IE_Released);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::AbilityLocalInputReleased, idx);
			InputComponent->AddActionBinding(AB);
		}
	}

	// Bind Confirm/Cancel. Note: these have to come last!
	if (!bDoNotAutoConfirmAndCancelFromGASBindings) //	Original implemntation didn't have this and forced a binding to confirm / cancel
	{
		if (BindInfo.ConfirmTargetCommand.IsEmpty() == false)
		{
			FInputActionBinding AB(FName(*BindInfo.ConfirmTargetCommand), IE_Pressed);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::LocalInputConfirm);
			InputComponent->AddActionBinding(AB);
		}

		if (BindInfo.CancelTargetCommand.IsEmpty() == false)
		{
			FInputActionBinding AB(FName(*BindInfo.CancelTargetCommand), IE_Pressed);
			AB.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &UAbilitySystemComponent::LocalInputCancel);
			InputComponent->AddActionBinding(AB);
		}
	}

	if (BindInfo.CancelTargetInputID >= 0)
	{
		GenericCancelInputID = BindInfo.CancelTargetInputID;
	}
	if (BindInfo.ConfirmTargetInputID >= 0)
	{
		GenericConfirmInputID = BindInfo.ConfirmTargetInputID;
	}
}

/* 
										--- Our thought process here that took us few hours to decide what to do ---
													relates to AAbilitySystemCharacter::BindASCInput()
	Idk why this what the pourpose is for the first 2 if statements because they never passed even when you pass in the last 2 optional parameters for
	the FGameplayAbilityInputBinds struct for the BindAbilityActivationToInputComponent() function and put confirm and cancel inputs in the Enum we made.
	Decided to just not have this function run for confirm and cancel since nothing happens in this function for them. We did this by not including
	confirm and cancel in the GAS input enum and not setting the optional parameters for the confirm and cancel input IDs for 
	BindAbilityActivationToInputComponent(). We figure this is the right way to setup the ability system since LocalInputConfirm() and LocalInputCancel()
	still get called and it prevents an extra call to this function which would have don't nothing anyways. Technically there may be importance to this 
	function running for the confirm and cancel inputs since there seems to be some kind of logic in the beginning for them, but Dart does it our way
	so at least were not the only ones. Dan doesn't do it this way though but we think he should have.
*/
/*
	this is the same thing as the Super exept it doesn't force the try activate ability when a bound input is pressed.
	We added a bool (bDoNotAutoActivateFromGASBindings) - set this to false if you want to make bound input directly call try activate ability
*/
void USSAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	// Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
	if (IsGenericConfirmInputBound(InputID))
	{
		LocalInputConfirm();
		return;
	}

	if (IsGenericCancelInputBound(InputID))
	{
		LocalInputCancel();
		return;
	}

	// ---------------------------------------------------------

	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.InputID == InputID)
		{
			// Confirm and Cancel Target never gets past here. Maybe it's because it hanldes those internally
			if (Spec.Ability)
			{
				Spec.InputPressed = true;
				if (Spec.IsActive())
				{
					if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
					{
						ServerSetInputPressed(Spec.Handle);
					}

					AbilitySpecInputPressed(Spec);

					// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
				}
				else
				{
					if (!bDoNotAutoActivateFromGASBindings) //	Original implemntation only had TryActivateAbility() in this else statement
					{
						// Ability is not active, so try to activate it
						TryActivateAbility(Spec.Handle);
					}
				}
			}
		}
	}
}
#pragma endregion

USSAbilitySystemComponent* USSAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<USSAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}

void USSAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UGameplayAbility>(ActiveAbility));
		}
	}
}

FGameplayAbilitySpecHandle USSAbilitySystemComponent::FindAbilitySpecHandleFromClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject)
{
	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		TSubclassOf<UGameplayAbility> SpecAbilityClass = Spec.Ability->GetClass();
		if (SpecAbilityClass == AbilityClass)
		{
			if (!OptionalSourceObject || (OptionalSourceObject && Spec.SourceObject == OptionalSourceObject))
			{
				return Spec.Handle;
			}
		}
	}

	return FGameplayAbilitySpecHandle();
}

void USSAbilitySystemComponent::ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Executed, GameplayCueParameters);
}
void USSAbilitySystemComponent::AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::OnActive, GameplayCueParameters);
}
void USSAbilitySystemComponent::RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters)
{
	UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(GetOwner(), GameplayCueTag, EGameplayCueEvent::Type::Removed, GameplayCueParameters);
}



void USSAbilitySystemComponent::FullReset()
{
	//	Stop ASC from doing things
	DestroyActiveState();
	

	if (IsOwnerActorAuthoritative())
	{
		//	Ungrant abilities. Will remove all abilitity tags/blocked bindings as well
		ClearAllAbilities();

		//	Clear Effects. Will remove all granted tags and cues as well
		for (const FActiveGameplayEffect& Effect : &ActiveGameplayEffects)
		{
			RemoveActiveGameplayEffect(Effect.Handle);
		}

		//	Remove Attribute Sets
		SpawnedAttributes.Empty();
	}


	//	If cue still exists because it was not from an effect
	RemoveAllGameplayCues();

	//	Now clean up any loose gameplay tags
	ResetTagMap();
	MinimalReplicationTags.RemoveAllTags();		//	This line may not be necessary

	//	Give clients changes ASAP
	ForceReplication();
}
