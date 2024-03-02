// Fill out your copyright notice in the Description page of Project Settings.


#include "Subobjects/ActorComponents/STActorComponent_Interactor.h"

#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"
#include "Character/STCharacter_Shooter.h"
#include "Interfaces/STInteractableInterface.h"
#include "Utilities/STCollisionChannels.h"
#include "Camera/CameraComponent.h"

#include "Kismet/KismetSystemLibrary.h"

USTActorComponent_Interactor::USTActorComponent_Interactor()
{
    bWantsInitializeComponent = true;
    PrimaryComponentTick.bCanEverTick = true;

    InteractSweepDistance = 150.f;
    CurrentPrioritizedInteractable = nullptr;
    LastPrioritizedInteractable = nullptr;

    SetTickGroup(ETickingGroup::TG_PrePhysics);    // Already pre physics by default but kep this here for now
}


void USTActorComponent_Interactor::InitializeComponent()
{
    Super::InitializeComponent();

    OwningShooterCharacter = Cast<ASTCharacter_Shooter>(GetOwner());
    OwningShooterCharacter->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &USTActorComponent_Interactor::OnComponentBeginOverlapCharacterCapsule);
    OwningShooterCharacter->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &USTActorComponent_Interactor::OnComponentEndOverlapCharacterCapsule);
}

void USTActorComponent_Interactor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!OwningShooterCharacter.IsValid())
    {
        return;
    }
    if (OwningShooterCharacter->HasAuthority() || OwningShooterCharacter->IsLocallyControlled())    // Don't run for simulated proxies
    {
        CurrentPrioritizedInteractable = ScanForCurrentPrioritizedInteractable(InteractSweepHitResult);
        if (CurrentPrioritizedInteractable)
        {
            if (CurrentPrioritizedInteractable != LastPrioritizedInteractable)
            {

                if (CurrentPrioritizedInteractable->GetShouldFireDetectionEvents())
                    CurrentPrioritizedInteractable->OnInitialDetect(OwningShooterCharacter.Get());

                if (LastPrioritizedInteractable)
                {
                    if (LastPrioritizedInteractable->GetShouldFireDetectionEvents())
                        LastPrioritizedInteractable->OnEndDetect(OwningShooterCharacter.Get());
                }

                // Automatic interact activation might be nice here
            }
            else
            {
                if (CurrentPrioritizedInteractable->GetShouldFireDetectionEvents())
                    CurrentPrioritizedInteractable->OnConsecutiveDetect(OwningShooterCharacter.Get());
            }





            LastPrioritizedInteractable = CurrentPrioritizedInteractable;
        }
        else
        {
            if (LastPrioritizedInteractable != nullptr)    // If the last frame had something to interact with
            {
                if (LastPrioritizedInteractable->GetShouldFireDetectionEvents())
                    LastPrioritizedInteractable->OnEndDetect(OwningShooterCharacter.Get());
                LastPrioritizedInteractable = nullptr;
            }
        }
    }
}


void USTActorComponent_Interactor::OnComponentBeginOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (ISTInteractableInterface* Interactable = Cast<ISTInteractableInterface>(OtherActor))
    {
        // If we knew at this point weather this interactable is the current one, we would be able to fire off a more helpful event in the interface.
        Interactable->InjectDetectType(ESTDetectType::DETECTTYPE_Overlapped);
        CurrentOverlapInteractablesStack.Push(Interactable);
    }
}
void USTActorComponent_Interactor::OnComponentEndOverlapCharacterCapsule(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ISTInteractableInterface* Interactable = Cast<ISTInteractableInterface>(OtherActor))
    {
        if (CurrentOverlapInteractablesStack.Num() > 0)
        {
            CurrentOverlapInteractablesStack.RemoveSingle(Interactable);    // Not using pop because there is a chance a character might be interacting with an overlap that isn't the current detected one (meaning it's not at the top of the stack)
            OnElementRemovedFromFrameOverlapInteractablesStack.Broadcast(Interactable);
            Interactable->InjectDetectType(ESTDetectType::DETECTTYPE_NotDetected);        // Give a value of not detected just in case
        }
    }
}









ISTInteractableInterface* USTActorComponent_Interactor::ScanForCurrentPrioritizedInteractable(FHitResult& OutHit)
{
    // Check if sphere sweep detects blocking hit as an interactable (a blocking hit doesn't necessarily mean the object is collidable. It's can just be collidable to the Interact trace channel).
    if (GetWorld() && OwningShooterCharacter->GetFollowCamera())
    {
        FVector StartLocation = OwningShooterCharacter->GetFollowCamera()->GetComponentLocation();
        FVector EndLocation = StartLocation + (OwningShooterCharacter->GetFollowCamera()->GetForwardVector() * InteractSweepDistance);

        const bool bBlockingHit = GetWorld()->SweepSingleByChannel(OutHit, StartLocation, EndLocation, FQuat::Identity, COLLISIONCHANNEL_INTERACT, FCollisionShape::MakeSphere(InteractSweepRadius), FCollisionQueryParams());
        if (bBlockingHit)
        {
            if (ISTInteractableInterface* BlockingHitInteractable = Cast<ISTInteractableInterface>(OutHit.GetActor()))
            {
                if (BlockingHitInteractable->GetCanCurrentlyBeInteractedWith())
                {
                    BlockingHitInteractable->InjectDetectType(ESTDetectType::DETECTTYPE_Sweeped);
                    return BlockingHitInteractable;
                }
            }
        }
    }


    // Try to return an interactable that is overlapping with the capsule component. It chooses the most recent one you overlap with (top of the stack).
    if (CurrentOverlapInteractablesStack.Num() > 0)
    {
        for (int32 i = CurrentOverlapInteractablesStack.Num() - 1; i >= 0; --i)
        {
            if (CurrentOverlapInteractablesStack.IsValidIndex(i))
            {
                if (CurrentOverlapInteractablesStack[i])
                {
                    if (CurrentOverlapInteractablesStack[i]->GetCanCurrentlyBeInteractedWith())
                    {
                        //UKismetSystemLibrary::PrintString(this, "Using = " + FString::SanitizeFloat(i), true, false, FLinearColor::Green);
                        return CurrentOverlapInteractablesStack[i];
                    }
                }
                else
                {
                    CurrentOverlapInteractablesStack.RemoveAt(i);    // (edge case) just remove the useless element
                }
            }
        }
    }





    // If no blocking or overlap interactables found return NULL
    return nullptr;
}

void USTActorComponent_Interactor::TryInteract()
{
    if (CurrentPrioritizedInteractable)
    {
        if (CurrentPrioritizedInteractable->GetIsManualInstantInteract())
        {
            OwningShooterCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(STNativeGameplayTags::Ability_Interact_InstantInteract.GetTag().GetSingleTagContainer());
        }
        if (CurrentPrioritizedInteractable->GetIsManualDurationInteract())
        {
            OwningShooterCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(STNativeGameplayTags::Ability_Interact_DurationInteract.GetTag().GetSingleTagContainer());
        }

    }
}
