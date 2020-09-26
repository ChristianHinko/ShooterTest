// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Characters/Sonic.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

//#include "GameFramework/CharacterMovementComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Actor/AS_Health.h"
#include "ActorComponents/InventoryComponent.h"
#include "Actor/Weapon/Weapon.h"
#include "Net/UnrealNetwork.h"



ASonic::ASonic(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetMesh()->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(52.0f);

	//Bump up all meshes so it gets within the capsule
	GetMesh()->SetRelativeLocation(FVector(GetMesh()->GetRelativeLocation().X, GetMesh()->GetRelativeLocation().Y, GetMesh()->GetRelativeLocation().Z + 44.f));
	GetPOVMesh()->SetRelativeLocation(FVector(GetPOVMesh()->GetRelativeLocation().X, GetPOVMesh()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 44.f));

	GetCameraBoom()->SetRelativeLocation(FVector(GetCameraBoom()->GetRelativeLocation().X, GetCameraBoom()->GetRelativeLocation().Y, GetPOVMesh()->GetRelativeLocation().Z + 28.f));
	

	//// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;
	//// Rotate the character in the movement direction
	//GetCharacterMovement()->bOrientRotationToMovement = true;


	//// Third person, so let player see mesh
	//GetMesh()->SetOwnerNoSee(false);

	//// Configure CameraBoom arm length for third person
	//GetCameraBoom()->TargetArmLength = 300.f;
}


void ASonic::BeginPlay()
{
	Super::BeginPlay();


	TestWeapon = GetWorld()->SpawnActor<AWeapon>(MyTestWeapon);
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ASonic::MyTimerCallback, 10.f, false);
}

void ASonic::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (GetHealthAttributeSet() && GetHealthAttributeSet()->GetHealth())
	//{
	//	UKismetSystemLibrary::PrintString(this, GetName() + ": " + FString::SanitizeFloat(GetHealthAttributeSet()->GetHealth()), true, false);
	//}
}


void ASonic::MyTimerCallback()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		Inventory->AddWeaponToInventory(TestWeapon);
	}
}
