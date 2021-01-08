// 2017-2018 Puny Human Games

#include "Abilities/Tasks/ArcAbilityTask_SimpleTarget.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"


UArcInvAbilityTask_SimpleTarget::UArcInvAbilityTask_SimpleTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

FGameplayAbilityTargetDataHandle UArcInvAbilityTask_SimpleTarget::GenerateTargetHandle()
{
	return FGameplayAbilityTargetDataHandle();
}

void UArcInvAbilityTask_SimpleTarget::HandleTargetData(const FGameplayAbilityTargetDataHandle& Data)
{
	
}

void UArcInvAbilityTask_SimpleTarget::HandleCancelled()
{

}

void UArcInvAbilityTask_SimpleTarget::Activate()
{
	//Create a network sync point here, as the server must wait for the predicting client to send us a prediction key for this event
	FScopedPredictionWindow ScopedWindow(AbilitySystemComponent, IsPredictingClient());

	FGameplayAbilityTargetDataHandle TargetDataHandle = GenerateTargetHandle();

	if (IsPredictingClient())
	{
		//Replicate up the client's targeting struct


		FGameplayTag ActivationTag;
		AbilitySystemComponent->CallServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(),
			TargetDataHandle, ActivationTag, AbilitySystemComponent->ScopedPredictionKey);

		HandleTargetData(TargetDataHandle);
	}
	else
	{
		const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

		//Hold onto the server target data, that way when the client data comes in we have this to compare against
		ServerTargetData = TargetDataHandle;

		//If we aren't a predicting client, but we are locally controlled, that means we are running in singleplayer or as the host of a listen server
		if (!IsLocallyControlled())
		{

			AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey())
				.AddUObject(this, &UArcInvAbilityTask_SimpleTarget::OnTargetDataCallback);
			AbilitySystemComponent->AbilityTargetDataCancelledDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey())
				.AddUObject(this, &UArcInvAbilityTask_SimpleTarget::OnTargetDataCancelled);

			AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());

			SetWaitingOnRemotePlayerData();
		}
		else
		{
			FGameplayTag ActivationTag;
			OnTargetDataCallback(TargetDataHandle, ActivationTag);
			EndTask();
		}

	}
}

void UArcInvAbilityTask_SimpleTarget::OnTargetDataCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	HandleTargetData(Data);

	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
  	
	EndTask();
}

void UArcInvAbilityTask_SimpleTarget::OnTargetDataCancelled()
{
	HandleCancelled();

	EndTask();
}
