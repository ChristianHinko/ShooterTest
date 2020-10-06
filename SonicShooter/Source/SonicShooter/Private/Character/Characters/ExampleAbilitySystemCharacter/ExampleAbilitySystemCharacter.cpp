// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"



void AExampleAbilitySystemCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AExampleAbilitySystemCharacter, ExampleAbilitySystemCharacterAttributeSet);
	DOREPLIFETIME_CONDITION(AExampleAbilitySystemCharacter, ExampleAbilitySpecHandle, COND_OwnerOnly);
}

AExampleAbilitySystemCharacter::AExampleAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Rotate the character in the movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;


	// Third person, so let player see mesh
	GetMesh()->SetOwnerNoSee(false);

	// Configure CameraBoom arm length for third person
	GetCameraBoom()->TargetArmLength = 300.f;
}


void AExampleAbilitySystemCharacter::CreateAttributeSets()
{
	Super::CreateAttributeSets();


	if (!ExampleAbilitySystemCharacterAttributeSet)
	{
		ExampleAbilitySystemCharacterAttributeSet = NewObject<UAS_ExampleAbilitySystemCharacter>(this, UAS_ExampleAbilitySystemCharacter::StaticClass(), TEXT("ExampleAbilitySystemCharacterAttributeSet"));
	}
	else
	{
		//=@REVIEW MARKER@= replace this LogTemp with your own log category
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogTemp, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *ExampleAbilitySystemCharacterAttributeSet->GetName());
	}
}

void AExampleAbilitySystemCharacter::RegisterAttributeSets()
{
	Super::RegisterAttributeSets();


	if (ExampleAbilitySystemCharacterAttributeSet && !GetAbilitySystemComponent()->SpawnedAttributes.Contains(ExampleAbilitySystemCharacterAttributeSet))
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(ExampleAbilitySystemCharacterAttributeSet);
	}
	else
	{
		//=@REVIEW MARKER@= replace this LogTemp with your own log category
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogTemp, Warning, TEXT("%s() ExampleAbilitySystemCharacterAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}
}

bool AExampleAbilitySystemCharacter::GrantStartingAbilities()
{
	if (Super::GrantStartingAbilities() == false)
	{
		return false;	// Did not pass predefined checks
	}
	//	We are on authority and have a valid ASC to work with




	ExampleAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(ExampleAbilityTSub, this, EAbilityInputID::PrimaryFire/*, GetLevel()*/);


	return true;
}

void AExampleAbilitySystemCharacter::OnPrimaryFirePressed()
{
	Super::OnPrimaryFirePressed();

	GetAbilitySystemComponent()->TryActivateAbility(ExampleAbilitySpecHandle);
}