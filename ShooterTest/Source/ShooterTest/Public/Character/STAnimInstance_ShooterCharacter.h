// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/STAnimInstance.h"

#include "STAnimInstance_ShooterCharacter.generated.h"


class ACharacter;
class ASTCharacter;
class ASTCharacter_Shooter;



/**
 * 
 */
UCLASS()
class SHOOTERTEST_API USTAnimInstance_ShooterCharacter : public USTAnimInstance
{
    GENERATED_BODY()

public:
    USTAnimInstance_ShooterCharacter(const FObjectInitializer& ObjectInitializer);


protected:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaTimeX) override;


    UPROPERTY()
        TWeakObjectPtr<const ASTCharacter_Shooter> OwningShooterCharacter;


    /**
     * The rotation of our owning Actor.
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        FRotator ActorRotation;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        FRotator MeshRotation;

    /** Current velocity of the owning Actor */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        FVector Velocity;
    /** Current speed of the owning Actor */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float Speed;

    /** Current relative forward speed of the owning Actor */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float ForwardSpeed;
    /** Current relative right speed of the owning Actor */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float RightSpeed;
    /** Current relative up speed of the owning Actor */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float UpSpeed;
    /** The combined ForwardSpeed and RightSpeed */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float HorizontalSpeed;

    /** Current yaw rotation of our velocity (from -180 degs to 180 degs) */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Actor")
        float Direction;



    /**
     * The rotation that we are looking (the Control Rotation).
     * NOTE: this will be choppy when replicated and we don't automatically smooth it,
     * ensure you make use of interpolation when using this value for animation.
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        FRotator AimRotation;

    /**
     * Amount of Pitch that our Control Rotation differs from our Actor Rotation.
     * NOTE: this will be choppy when replicated and we don't automatically smooth it,
     * ensure you make use of interpolation when using this value for animation.
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        float AimOffsetPitch;
    /**
     * Amount of Yaw that our Control Rotation differs from our Actor Rotation.
     * NOTE: this will be choppy when replicated and we don't automatically smooth it,
     * ensure you make use of interpolation when using this value for animation.
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        float AimOffsetYaw;


    /** Whether we should even do TIP */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        uint8 bTurnInPlaceEnabled : 1;
    bool IsTurnInPlaceEnabled() const;
    /** Whether TIP logic should be considered in our current state */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        uint8 bTurnInPlaceAvailable : 1;
    bool IsTurnInPlaceAvailable() const;

    /**
     * Our Yaw rotation when TIP logic became available (when bTurnInPlaceAvailable became true)
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        float TurnInPlaceStartingYaw;
    /**
     * TIP's offset of the root's Yaw rotation.
     * Meant to negate with the Actor's rotation by doing a RotateRootBone in the Anim Graph
     * and plugging this in for the Yaw.
     */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        float TurnInPlaceYawOffset;
    /** When we are currently performing the turn for TIP */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Pawn")
        uint8 bIsTurningInPlace : 1;



    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 bGrounded : 1;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 bInAir : 1;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 bIsFlying : 1;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 bIsSwimming : 1;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
        uint8 bIsCrouching : 1;



    void TurnInPlace(float DeltaTimeX);




    //  BEGIN HeadTurning
    UPROPERTY(BlueprintReadOnly)
        FRotator headLookAtRot;
    UPROPERTY(BlueprintReadWrite)
        float headLookAtAlpha;
    UPROPERTY(BlueprintReadWrite)
        float headLookSpeed;
    UPROPERTY(BlueprintReadWrite)
        float headMaxRollRot;
    UPROPERTY(BlueprintReadWrite)
        float headMaxPitchRot;
    UPROPERTY(BlueprintReadWrite)
        float headMaxYawRot;
    //  END HeadTurning


    FRotator GetHeadLookAtTargetRot(AActor* Target, float deltaTime);
    static APawn* GetNearestPawn(const AActor* InActor);

private:
    FRotator PreviousActorRotation;

};
