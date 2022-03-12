// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShooterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Utilities/LogCategories.h"
#include "Utilities/SSNativeGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Subobjects/ActorComponents/InteractorComponent.h"
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
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToFirstItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToSecondItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToThirdItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToFourthItemAbilitySpecHandle, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AShooterCharacter, SwapToFifthItemAbilitySpecHandle, COND_OwnerOnly);

	DOREPLIFETIME_CONDITION(AShooterCharacter, DropItemAbilitySpecHandle, COND_OwnerOnly);
}

const FName AShooterCharacter::InventoryComponentName = TEXT("InventoryComponent");

AShooterCharacter::AShooterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USSArcInventoryComponent_Active>(InventoryComponentName))
{
	// Default to first person
	bFirstPerson = true;
	bUseControllerRotationYaw = true; // let the camera rotation determine our yaw
	GetCharacterMovement()->bOrientRotationToMovement = false; // don't rotate theCharacter in the movement direction



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
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() %s was already valid when trying to create the attribute set; did nothing"), ANSI_TO_TCHAR(__FUNCTION__), *HealthAttributeSet->GetName());
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
		UE_CLOG((GetLocalRole() == ROLE_Authority), LogSSAbilitySystemSetup, Warning, TEXT("%s() HealthAttributeSet was either NULL or already added to the character's ASC. Character: %s"), ANSI_TO_TCHAR(__FUNCTION__), *GetName());
	}
}
void AShooterCharacter::GiveStartingAbilities()
{
	Super::GiveStartingAbilities();

	InteractInstantAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(InteractInstantAbilityTSub, /*GetLevel()*/1, -1, this));
	InteractDurationAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(InteractDurationAbilityTSub, /*GetLevel()*/1, -1, this));

	SwapToLastActiveItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToLastActiveItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToNextItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToNextItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToPreviousItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToPreviousItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFirstItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFirstItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToSecondItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToSecondItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToThirdItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToThirdItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFourthItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFourthItemAbilityTSub, /*GetLevel()*/1, -1, this));
	SwapToFifthItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SwapToFifthItemAbilityTSub, /*GetLevel()*/1, -1, this));

	DropItemAbilitySpecHandle = GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(DropItemAbilityTSub, /*GetLevel()*/1, -1, this));
}

#include "Kismet/KismetSystemLibrary.h"
#include "AttributeSets/AS_Health.h"
#include "Inventory/Item/AS_Ammo.h"
#include "Subobjects/O_ClipAmmo.h"
#include "Subobjects/O_BulletSpread.h"
#include "Subobjects/O_Stamina.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Item\ArcItemDefinition_New.h"
#include "Inventory/Item/Gun/ArcItemStack_Gun.h"
#include "Character/SSCharacterMovementComponent.h"
#include "AbilitySystem/AbilitySystemComponents/ASC_Shooter.h"
#include "AbilitySystem/ASSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/AS_Stamina.h"
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

	if (IsValid(SSInventoryComponentActive))
	{
		const UArcItemStack* ActiveItemStack = SSInventoryComponentActive->GetActiveItemStack();
		if (IsValid(ActiveItemStack))
		{
			const UArcItemStack_Gun* GunStack = Cast<UArcItemStack_Gun>(ActiveItemStack);
			if (IsValid(GunStack))
			{
				//const FFloatPropertyWrapper& ClipAmmo = GunStack->GetClipAmmoSubobject()->ClipAmmo;
				//UKismetSystemLibrary::PrintString(this, ClipAmmo.GetPropertyName().ToString() + TEXT(": ") + FString::SanitizeFloat(ClipAmmo), true, false);

				//const FFloatPropertyWrapper& CurrentBulletSpread = GunStack->GetBulletSpreadSubobject()->CurrentBulletSpread;
				//UKismetSystemLibrary::PrintString(this, CurrentBulletSpread.GetPropertyName().ToString() + TEXT(": ") + FString::SanitizeFloat(CurrentBulletSpread), true, false);
			}
		}


	}

	if (IsValid(SSCharacterMovementComponent))
	{
		//if (IsValid(SSCharacterMovementComponent->StaminaSubobject))
		//{
		//	const FFloatPropertyWrapper& Stamina = SSCharacterMovementComponent->StaminaSubobject->Stamina;
		//	UKismetSystemLibrary::PrintString(this, Stamina.GetPropertyName().ToString() + TEXT(": ") + FString::SanitizeFloat(Stamina), true, false);

		//}
	}
	if (IsValid(GetAbilitySystemComponent()))
	{
		//const float MaxStamina = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetMaxStaminaAttribute());
		//const float StaminaDrain = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaDrainAttribute());
		//const float StaminaGain = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaGainAttribute());
		//const float StaminaRegenPause = GetAbilitySystemComponent()->GetNumericAttribute(UAS_Stamina::GetStaminaRegenPauseAttribute());

		//UKismetSystemLibrary::PrintString(this, TEXT("MaxStamina: ") + FString::SanitizeFloat(MaxStamina), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaDrain: ") + FString::SanitizeFloat(StaminaDrain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaGain: ") + FString::SanitizeFloat(StaminaGain), true, false);
		//UKismetSystemLibrary::PrintString(this, TEXT("StaminaRegenPause: ") + FString::SanitizeFloat(StaminaRegenPause), true, false);
	}

	if (GetAbilitySystemComponent())
	{
		for (UAttributeSet* AttributeSet : GetAbilitySystemComponent()->GetSpawnedAttributes())
		{
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
		GetAbilitySystemComponent()->GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag_AbilityInputPrimaryFire.GetTag().GetSingleTagContainer(), Specs);

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
		GetAbilitySystemComponent()->TryActivateAbilitiesByTag(Tag_ReloadAbility.GetTag().GetSingleTagContainer());
	}
}

void AShooterCharacter::OnSwitchWeaponPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToLastActiveItemAbilitySpecHandle);
}
void AShooterCharacter::OnFirstItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFirstItemAbilitySpecHandle);
}
void AShooterCharacter::OnSecondItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToSecondItemAbilitySpecHandle);
}
void AShooterCharacter::OnThirdItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToThirdItemAbilitySpecHandle);
}
void AShooterCharacter::OnFourthItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFourthItemAbilitySpecHandle);
}
void AShooterCharacter::OnFifthItemPressed()
{
	GetAbilitySystemComponent()->TryActivateAbility(SwapToFifthItemAbilitySpecHandle);
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


