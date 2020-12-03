// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_PlayMontageWaitCust.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

UAT_PlayMontageWaitCust::UAT_PlayMontageWaitCust(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Rate = 1.f;
	bStopWhenAbilityEnds = true;
}

void UAT_PlayMontageWaitCust::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (Ability && Ability->GetCurrentMontage() == MontageToPlay)
	{
		if (Montage == MontageToPlay)
		{
			AbilitySystemComponent->ClearAnimatingAbility(Ability);

			// Reset AnimRootMotionTranslationScale
			ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
			if (Character && (Character->GetLocalRole() == ROLE_Authority ||
				(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
			{
				Character->SetAnimRootMotionTranslationScale(1.f);
			}

		}
	}

	if (bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast();
		}
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnBlendOut.Broadcast();
		}
	}
}

void UAT_PlayMontageWaitCust::OnMontageInterrupted()
{
	if (StopPlayingMontage())
	{
		// Let the BP handle the interrupt as well
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast();
		}
	}
}

void UAT_PlayMontageWaitCust::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast();
		}
	}

	EndTask();
}

UAT_PlayMontageWaitCust* UAT_PlayMontageWaitCust::CreatePlayMontageAndWaitProxy(UGameplayAbility* OwningAbility,
	FName TaskInstanceName, UAnimMontage* MontageToPlay, USkeletalMeshComponent* UseAlternateSKMC, float Rate, FName StartSection,
	bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, FName AnimNotifyName)
{

	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	UAT_PlayMontageWaitCust* MyObj = NewAbilityTask<UAT_PlayMontageWaitCust>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->UseAlternateSKMC = UseAlternateSKMC;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->WaitForAnimNotifyName = AnimNotifyName;
	return MyObj;
}

void UAT_PlayMontageWaitCust::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (AbilitySystemComponent)
	{
		if (UseAlternateSKMC)
		{
			UAnimInstance* AnimInstance;
			AnimInstance = UseAlternateSKMC->GetAnimInstance();

			float Duration = AnimInstance->Montage_Play(MontageToPlay, Rate);
			if (Duration > 0)
			{
				bPlayedMontage = true;
			}
		}
		else
		{
			const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
			UAnimInstance* AnimInstance;
			AnimInstance = ActorInfo->GetAnimInstance();

			if (AnimInstance != nullptr)
			{
				if (AbilitySystemComponent->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection) > 0.f)
				{
					// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
					if (ShouldBroadcastAbilityTaskDelegates() == false)
					{
						return;
					}

					InterruptedHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UAT_PlayMontageWaitCust::OnMontageInterrupted);

					BlendingOutDelegate.BindUObject(this, &UAT_PlayMontageWaitCust::OnMontageBlendingOut);
					AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

					MontageEndedDelegate.BindUObject(this, &UAT_PlayMontageWaitCust::OnMontageEnded);
					AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

					if (WaitForAnimNotifyName != NAME_None)
					{
						AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UAT_PlayMontageWaitCust::OnNotifyBeginReceived);
					}

					ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
					if (Character && (Character->GetLocalRole() == ROLE_Authority ||
						(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
					{
						Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
					}

					bPlayedMontage = true;
				}
			}
			else
			{
				ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait call to PlayMontage failed!"));
			}
		}
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait called on invalid AbilitySystemComponent"));
	}

	if (!bPlayedMontage)
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWait called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay), *InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast();
		}
	}

	SetWaitingOnAvatar();
}

void UAT_PlayMontageWaitCust::ExternalCancel()
{
	check(AbilitySystemComponent);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCancelled.Broadcast();
	}
	Super::ExternalCancel();
}

void UAT_PlayMontageWaitCust::OnDestroy(bool AbilityEnded)
{
	// Note: Clearing montage end delegate isn't necessary since its not a multicast and will be cleared when the next montage plays.
	// (If we are destroyed, it will detect this and not do anything)

	// This delegate, however, should be cleared as it is a multicast
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(InterruptedHandle);
		if (AbilityEnded && bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
		}
	}

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo)
	{
		Super::OnDestroy(AbilityEnded);
		return;
	}

	UAnimInstance* AnimInstance;
	if (UseAlternateSKMC)
	{
		AnimInstance = UseAlternateSKMC->GetAnimInstance();
	}
	else
	{
		AnimInstance = ActorInfo->GetAnimInstance();
	}

	if (AnimInstance != nullptr)
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UAT_PlayMontageWaitCust::OnNotifyBeginReceived);
	}

	Super::OnDestroy(AbilityEnded);
}


void UAT_PlayMontageWaitCust::OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == WaitForAnimNotifyName)
	{
		OnAnimNotify.Broadcast();
	}
}

bool UAT_PlayMontageWaitCust::StopPlayingMontage()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo)
	{
		return false;
	}

	UAnimInstance* AnimInstance;
	if (UseAlternateSKMC)
	{
		AnimInstance = UseAlternateSKMC->GetAnimInstance();
	}
	else
	{
		AnimInstance = ActorInfo->GetAnimInstance();
	}

	if (AnimInstance == nullptr)
	{
		return false;
	}

	// Check if the montage is still playing
	// The ability would have been interrupted, in which case we should automatically stop the montage
	if (AbilitySystemComponent && Ability)
	{
		if (AbilitySystemComponent->GetAnimatingAbility() == Ability
			&& AbilitySystemComponent->GetCurrentMontage() == MontageToPlay)
		{
			// Unbind delegates so they don't get called as well
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			AbilitySystemComponent->CurrentMontageStop();
			return true;
		}
	}

	return false;
}

FString UAT_PlayMontageWaitCust::GetDebugString() const
{
	UAnimMontage* PlayingMontage = nullptr;
	if (Ability)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();

		UAnimInstance* AnimInstance;
		if (UseAlternateSKMC)
		{
			AnimInstance = UseAlternateSKMC->GetAnimInstance();
		}
		else
		{
			AnimInstance = ActorInfo->GetAnimInstance();
		}

		if (AnimInstance != nullptr)
		{
			PlayingMontage = AnimInstance->Montage_IsActive(MontageToPlay) ? MontageToPlay : AnimInstance->GetCurrentActiveMontage();
		}
	}

	return FString::Printf(TEXT("PlayMontageAndWait. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay), *GetNameSafe(PlayingMontage));
}