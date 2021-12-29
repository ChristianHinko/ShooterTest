// Copyright 2017-2020 Puny Human, All Rights Reserved.

#include "Item/ArcItemStackWorldObject.h"
#include "ArcInventoryItemTypes.h"

#include "ArcInventory.h"
#include "Engine/ActorChannel.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AArcItemStackWorldObject::AArcItemStackWorldObject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Default Mesh"));
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;	

	RootComponent = StaticMeshComponent;
	
	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicateMovement(true);

	InventoryStack = nullptr;
}

void AArcItemStackWorldObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	
	DOREPLIFETIME_CONDITION_NOTIFY(AArcItemStackWorldObject, InventoryStack, COND_None, REPNOTIFY_Always);

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool AArcItemStackWorldObject::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool WroteSomething = false;

	if (IsValid(InventoryStack))
	{
		WroteSomething |= Channel->ReplicateSubobject(InventoryStack, *Bunch, *RepFlags);
		WroteSomething |= InventoryStack->ReplicateSubobjects(Channel, Bunch, RepFlags);
	}

	WroteSomething |= Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	
	return WroteSomething;
}

// Called when the game starts or when spawned
void AArcItemStackWorldObject::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(InventoryStack))
	{
		SetInventoryStack(InventoryStack);
	}
	
}

// Called every frame
void AArcItemStackWorldObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArcItemStackWorldObject::SetInventoryStack_Implementation(UArcItemStack* InInventoryStack)
{
	InventoryStack = InInventoryStack;

	// Modified plugin code:
	//------------=@MODIFIED MARKER@= Comment out this block. No longer are using WorldItemModel. This class should now be spawned from a BP child class with a predefined static mesh or skeletal mesh if you want
	//if (IsValid(InventoryStack)
	//	&& InventoryStack->HasValidItemData()
	//	&& IsValid(InventoryStack->GetItemDefinition().GetDefaultObject()->WorldItemModel))
	//{
	//	StaticMeshComponent->SetStaticMesh(InventoryStack->GetItemDefinition().GetDefaultObject()->WorldItemModel);
	//}
	//-------------
	
	// Normal plugin code:
	if (IsValid(InventoryStack)
		&& InventoryStack->HasValidItemData()
		&& IsValid(InventoryStack->GetItemDefinition().GetDefaultObject()->WorldItemModel))
	{
		StaticMeshComponent->SetStaticMesh(InventoryStack->GetItemDefinition().GetDefaultObject()->WorldItemModel);
	}


	if (GetLocalRole() == ROLE_Authority)
	{
		if (IsValid(InventoryStack))
		{
			UArcItemStack::TransferStackOwnership(InventoryStack, this);
		}
		this->ForceNetUpdate();
	}
}

UArcItemStack* AArcItemStackWorldObject::GetInventoryStack()
{
	return InventoryStack;
}

void AArcItemStackWorldObject::OnRep_InventoryStack()
{
	SetInventoryStack(InventoryStack);
}

/*
void AArcItemStackWorldObject::OnInteract_Implementation(AActor* Interactor, bool bLongHold)
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (UArcInventoryComponent* Inventory = UArcItemBPFunctionLibrary::GetInventoryComponent(Interactor))
	{
		if (Inventory->LootItem(InventoryStack))
		{
			
			SetLifeSpan(0.1);
		}
	}
}
*/
