//Copyright 2021, Dakota Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FPSTemplate_PartComponent.generated.h"

class AFPSTemplate_PartBase;
class UStaticMeshComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTIMATEFPSTEMPLATE_API UFPSTemplate_PartComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSTemplate_PartComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	TArray<TSubclassOf<AFPSTemplate_PartBase>> PossibleParts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	TSubclassOf<AFPSTemplate_PartBase> DefaultPart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	FText ComponentName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	UStaticMeshComponent* Minimum;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	UStaticMeshComponent* Maximum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPSTemplate")
	UStaticMeshComponent* PreviewMesh;

	UPROPERTY(ReplicatedUsing = OnRep_Part, BlueprintReadOnly, Category = "FPSTemplate")
	AFPSTemplate_PartBase* Part;
	UFUNCTION()
	void OnRep_Part();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AddPart(TSubclassOf<AFPSTemplate_PartBase> PartClass);
	
public:
	// TRY RELATIVE???
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	FTransform GetAttachmentTransform() const;
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	AFPSTemplate_PartBase* GetPart() const { return Part; }

	template <class T>
	T* GetPart() const { return Cast<T>(Part); }

	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Part")
	bool AddPart(TSubclassOf<AFPSTemplate_PartBase> PartClass);
	UFUNCTION(BlueprintPure, Category = "FPSTemplate | Animation")
	bool IsPartCompatible(TSubclassOf<AFPSTemplate_PartBase> PartClass) const;
};
