// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerState.h"

#include "SSPlayerController.generated.h"


class ASSGameMode;



/**
 * The controller can use this to know when the current Pawn is changed,
 * and recreate or modify its pawn as needed (by calling UpdatePawn())
 */
DECLARE_MULTICAST_DELEGATE(FPawnInfoChange);


/**
 *  This should store the info for a Pawn. A player may switch Pawns by
 *  calling SetPendingPawnInfo(FPawnInfo NewPawnInfo), and then calling UpdatePawn().
 */
USTRUCT(BlueprintType)
struct FPawnInfo // do we actually need this?
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnInfo")
		TSubclassOf<APawn> PawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnInfo")
		FString Name;
};

/**
 * Base player controller (Ability System aware). Holds pending pawn data
 */
UCLASS()
class SONICSIEGE_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	/** Set a new Pawn to be active. Can be called on client */
	UFUNCTION(BlueprintCallable)
		void SetPendingPawnInfo(const FPawnInfo& NewPawnInfo);

	/** On pending pawn info change delegate */
	FPawnInfoChange OnPendingPawnInfoChange;


	const TArray<FPawnInfo> GetPawnInfos() const { return PawnInfos; }

	/** Will be null if no Pawn has been selected yet */
	const FPawnInfo GetPendingPawnInfo() const { return PendingPawnInfo; }

	UFUNCTION(BlueprintCallable)							// blueprint callable for testing =@REVIEW MARKER@=
		APawn* SpawnPawnFromPendingInfo();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnInfo")
		TArray<FPawnInfo> PawnInfos;

	UPROPERTY()
		ASSGameMode* SSGamemode;

	UPROPERTY(Replicated)
		ASSPlayerState* SSPlayerState;


	virtual void BeginPlay() override;

	//BEGIN AController Interface
	virtual void InitPlayerState() override;	// Server only (rare case for client I think)
	virtual void OnRep_PlayerState() override;
	virtual void OnPossess(APawn* P) override;
	//END AController Interface

private:
	FPawnInfo PendingPawnInfo;
};
