// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShooterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Utilities/LogCategories.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "ActorComponents/InteractorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/SSArcInventoryComponent_Active.h"
#include "ArcItemStack.h"
#include "AbilitySystem/ASSGameplayAbility.h"
#include "AttributeSets/AS_Health.h"



void AShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(AShooterCharacter, HealthAttributeSet);


	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractInstantAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, InteractDurationAbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToLastActiveItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToNextItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToPreviousItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem0AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem1AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem2AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem3AbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToItem4AbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AShooterCharacter, DropItemAbilitySpecHandle, COND_OwnerOnly);
}

const FName AShooterCharacter::InventoryComponentName(TEXT("InventoryComponent"));

AShooterCharacter::AShooterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSArcInventoryComponent_Active>(InventoryComponentName))
{
	InventoryComponent = CreateDefaultSubobject<UArcInventoryComponent>(InventoryComponentName);
	SSInventoryComponentActive = Cast<USSArcInventoryComponent_Active>(InventoryComponent);


	Interactor = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor"));

	CameraSwayAmount = FVector(0, 1.3f, .4f);
	AddedCameraSwayDuringADS = FVector(0, -1.1f, -.1f);
}

void AShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AShooterCharacter::CreateAttributeSets()
{
	Super::CreateAttributeSets();


	if (!HealthAttributeSet)
	{
		HealthAttributeSet = NewObject<UAS_Health>(this, UAS_Health::StaticClass(), TEXT("HealthAttributeSet"));
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), *FString(__FUNCTION__), *HealthAttributeSet->GetName());
	}
}

void AShooterCharacter::RegisterAttributeSets()
{
	Super::RegisterAttributeSets();


	if (HealthAttributeSet && !GetAbilitySystemComponent()->GetSpawnedAttributes().Contains(HealthAttributeSet))	// If HealthAttributeSet is valid and it's not yet registered with the Character's ASC
	{
		GetAbilitySystemComponent()->AddAttributeSetSubobject(HealthAttributeSet);
	}
	else
	{
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() HealthAttributeSet was either NULL or already added to the character's ASC. Character: %s"), *FString(__FUNCTION__), *GetName());
	}
}
void AShooterCharacter::GrantStartingAbilities()
{
	Super::GrantStartingAbilities();


	InteractInstantAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(InteractInstantAbilityTSub, this/*, GetLevel()*/);
	InteractDurationAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(InteractDurationAbilityTSub, this/*, GetLevel()*/);

	SwapToLastActiveItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToLastActiveItemAbilityTSub, this/*, GetLevel()*/);
	SwapToNextItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToNextItemAbilityTSub, this/*, GetLevel()*/);
	SwapToPreviousItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToPreviousItemAbilityTSub, this/*, GetLevel()*/);
	SwapToItem0AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem0AbilityTSub, this/*, GetLevel()*/);
	SwapToItem1AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem1AbilityTSub, this/*, GetLevel()*/);
	SwapToItem2AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem2AbilityTSub, this/*, GetLevel()*/);
	SwapToItem3AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem3AbilityTSub, this/*, GetLevel()*/);
	SwapToItem4AbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(SwapToItem4AbilityTSub, this/*, GetLevel()*/);

	DropItemAbilitySpecHandle = GetAbilitySystemComponent()->GrantAbility(DropItemAbilityTSub, this/*, GetLevel()*/);

}

#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/AS_Health.h"
#include "Item/AS_Ammo.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Item\ArcItemDefinition_New.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "GameFramework/SpringArmComponent.h"
void AShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetHealthAttributeSet())
	{
		//UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(GetHealthAttributeSet()->GetHealth()), true, false);
	}

	//for (int32 i = 0; i < SSInventoryComponentActive->ActiveItemHistory.Num(); ++i)
	//{
	//	FArcInventoryItemSlotReference current = SSInventoryComponentActive->ActiveItemHistory[i];

	//	UKismetSystemLibrary::PrintString(this, "["+FString::FromInt(current.SlotId)+"] " + current.SlotTags.GetByIndex(1).ToString(), true, false, FLinearColor::Green);
	//}

	if (SSInventoryComponentActive)
	{
		//UKismetSystemLibrary::PrintString(this, "Current Item Slot: " + FString::FromInt(SSInventoryComponentActive->GetActiveItemSlot().SlotId), true, false);
		//UKismetSystemLibrary::PrintString(this, "Pending Item Slot: " + FString::FromInt(SSInventoryComponentActive->PendingItemSlot), true, false);
	}

	if (GetAbilitySystemComponent())
	{
		for (UAttributeSet* AttributeSet : GetAbilitySystemComponent()->GetSpawnedAttributes())
		{
			//if (UAS_Ammo* AmmoAttributeSet = Cast<UAS_Ammo>(AttributeSet))
			//{
			//	UKismetSystemLibrary::PrintString(this, AmmoAttributeSet->GetBackupAmmoAttribute().GetName() + ": " + FString::SanitizeFloat(AmmoAttributeSet->GetBackupAmmo()), true, false);
			//	UKismetSystemLibrary::PrintString(this, AmmoAttributeSet->ClipAmmo.GetPropertyName().ToString() + ": " + FString::SanitizeFloat(AmmoAttributeSet->ClipAmmo), true, false);
			//}

			//if (UAS_Stamina* FoundStaminaAttributeSet = Cast<UAS_Stamina>(AttributeSet))
			//{
			//	UKismetSystemLibrary::PrintString(this, FoundStaminaAttributeSet->Stamina.GetPropertyName().ToString() + ": " + FString::SanitizeFloat(FoundStaminaAttributeSet->Stamina), true, false);
			//}
		}

	}

	//}

	//	Item history debug
	//UKismetSystemLibrary::PrintString(this, "------------", true, false);
	//if (SSInventoryComponentActive)
	//{
	//	for (FArcInventoryItemSlotReference slotRef : SSInventoryComponentActive->ActiveItemHistory)
	//	{
	//		UKismetSystemLibrary::PrintString(this, UArcItemBPFunctionLibrary::GetItemFromSlot(slotRef)->GetItemDefinition().GetDefaultObject()->GetFName().ToString(), true, false);

	//	}
	//}
	//UKismetSystemLibrary::PrintString(this, "-----------", true, false);


	

	//float frameHorizontalMouseRate = 0;
	//float frameVerticalMouseRate = 0;
	//Cast<APlayerController>(GetController())->GetInputMouseDelta(frameHorizontalMouseRate, frameVerticalMouseRate);
	//

	//// Weapon sway
	//if (POVMesh/* && AbilitySystem && !AbilitySystem->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("WeaponState.ADS")))*/)
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector FrameMouseRate = FVector(0, -frameHorizontalMouseRate, -frameVerticalMouseRate);
	//	FVector NewCameraLocation = CameraSocketLocation - (FrameMouseRate * CameraSwayAmount);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaSeconds, 10));
	//	}

	//	
	//}
	//else
	//{
	//	FVector CameraSocketLocation = POVMesh->GetSocketTransform(TEXT("CameraBoneSocket"), ERelativeTransformSpace::RTS_ParentBoneSpace).GetLocation();
	//	FVector NewCameraLocation = FVector(0, 0, 0);
	//	if (GetCameraBoom())
	//	{
	//		FVector CurrentCameraLocation = FVector(GetCameraBoom()->GetRelativeTransform().GetLocation());

	//		float yaw = CurrentCameraLocation.Y - frameHorizontalMouseRate;
	//		float pitch = CurrentCameraLocation.Z - frameVerticalMouseRate;
	//		FVector Sway = FVector(CurrentCameraLocation.X, yaw, pitch);

	//		FVector ADSCameraSwayAmount = CameraSwayAmount + AddedCameraSwayDuringADS;

	//		NewCameraLocation = CameraSocketLocation - (Sway * ADSCameraSwayAmount);




	//		GetCameraBoom()->SetRelativeLocation(UKismetMathLibrary::VInterpTo(CurrentCameraLocation, NewCameraLocation, DeltaSeconds, 10));
	//	}




	//}
}


void AShooterCharacter::OnInteractPressed()
{
	Interactor->TryInteract();
}

void AShooterCharacter::OnPrimaryFirePressed()
{
	if (GetAbilitySystemComponent())
	{
		TArray<FGameplayAbilitySpec*> Specs; // our found specs
		GetAbilitySystemComponent()->GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTag::RequestGameplayTag(FName("AbilityInput.PrimaryFire")).GetSingleTagContainer(), Specs);

		for (FGameplayAbilitySpec* Spec : Specs)
		{
			// Our spec handle to activate
			FGameplayAbilitySpecHandle Handle = Spec->Handle;

			GetAbilitySystemComponent()->TryActivateAbility(Handle);
		}
	}
}

void AShooterCharacter::OnReloadPressed()
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FGameplayTag::RequestGameplayTag(FName("Ability.Reload")).GetSingleTagContainer());
	}
}

void AShooterCharacter::OnSwitchWeaponPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToLastActiveItemAbilitySpecHandle);
}
void AShooterCharacter::OnItem0Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem0AbilitySpecHandle);
}
void AShooterCharacter::OnItem1Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem1AbilitySpecHandle);
}
void AShooterCharacter::OnItem2Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem2AbilitySpecHandle);
}
void AShooterCharacter::OnItem3Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem3AbilitySpecHandle);
}
void AShooterCharacter::OnItem4Pressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToItem4AbilitySpecHandle);
}
void AShooterCharacter::OnNextItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToNextItemAbilitySpecHandle);
}
void AShooterCharacter::OnPreviousItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToPreviousItemAbilitySpecHandle);
}

void AShooterCharacter::OnPausePressed()
{
	Super::OnPausePressed();
}

void AShooterCharacter::OnScoreSheetPressed()
{
	Super::OnScoreSheetPressed();
}

void AShooterCharacter::OnDropItemPressed()
{
	FArcInventoryItemSlotReference ActiveItem = SSInventoryComponentActive->GetActiveItemSlot();
	if (SSInventoryComponentActive->IsValidActiveItemSlot(ActiveItem.SlotId))
	{
		SSInventoryComponentActive->PendingItemDrop = SSInventoryComponentActive->GetActiveItemSlot();
		GetAbilitySystemComponent()->TryActivateAbility(DropItemAbilitySpecHandle, true);
	}
}


