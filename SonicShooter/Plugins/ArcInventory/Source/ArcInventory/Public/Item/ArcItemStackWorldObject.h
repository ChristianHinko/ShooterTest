// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcInventoryItemTypes.h"
#include "ArcItemStackWorldObject.generated.h"
							
class UArcItemStack;

UCLASS()
class ARCINVENTORY_API AArcItemStackWorldObject : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;
	
public:	
	// Sets default values for this actor's properties
	AArcItemStackWorldObject(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;

	
	UStaticMeshComponent* GetStaticMeshComponent() { return StaticMeshComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item")
	void SetInventoryStack(UArcItemStack* InInventoryStack);
	virtual void SetInventoryStack_Implementation(UArcItemStack* InInventoryStack);

	UFUNCTION(BlueprintPure, Category = "Item")
	virtual UArcItemStack* GetInventoryStack();



	

	UFUNCTION()
	void OnRep_InventoryStack();

	//virtual void OnInteract_Implementation(AActor* Interactor, bool bLongHold) override;

private:
	UPROPERTY(VisibleInstanceOnly, ReplicatedUsing = OnRep_InventoryStack, Category = "Item")
	UArcItemStack* InventoryStack;
};


