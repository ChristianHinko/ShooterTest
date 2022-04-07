// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystems/ActorPoolerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/SSActor.h"
#include "Interfaces/PoolableInterface.h"
#include "Utilities/LogCategories.h"
#include "Kismet/KismetSystemLibrary.h"


UActorPoolerSubsystem::UActorPoolerSubsystem()
{
	maxPoolSize = 2;
	bDebugPooling = false;
}

ASSActor* UActorPoolerSubsystem::GetFromPool()
{
	UWorld* World = GetWorld();


	//find first of correct class;
	bool CleanupRequired = false;

	int32 FoundIndex = Pooled.IndexOfByPredicate(
		[&](auto InItem) 
		{
			if (InItem.IsValid() && InItem->GetWorld() == World)
			{
				return true;
			}
			else
			{
				CleanupRequired = true;
				return false;
			}
		});

	TWeakObjectPtr<ASSActor> Found = nullptr;
	if (FoundIndex != INDEX_NONE)
	{
		Found = Pooled[FoundIndex];
		Pooled.RemoveAtSwap(FoundIndex);
	}

	if (CleanupRequired)
	{
#ifdef WITH_EDITOR
		UKismetSystemLibrary::PrintString(this, "Invalid reference in pool, cleaning up", true, true, FLinearColor::Yellow);
#endif
		Pooled.RemoveAll([&](auto InItem) 
		{
			if (InItem.IsValid() && InItem->GetWorld() == World)
			{
				return false;
			}
			else
			{
				return true;
			}
		});
	}

	return(Found.Get());
}

ASSActor* UActorPoolerSubsystem::SpawnOrReactivate(TSubclassOf<ASSActor> ActorClass, AActor* ActorOwner, APawn* ActorInstigator, const FTransform& Transform)
{
	UWorld* World = GetWorld();

	ASSActor* Recycled = GetFromPool();

	if (Recycled)
	{
		ASSActor* Default = Cast<ASSActor>(ActorClass->GetDefaultObject());

		Recycled->SetOwner(ActorOwner);
		Recycled->SetInstigator(ActorInstigator);
		Recycled->SetActorTransform(Transform);
		Recycled->SetActorHiddenInGame(Default->IsHidden());
		Recycled->SetActorTickEnabled(true);
		Recycled->SetActorEnableCollision(true);
		Recycled->SetLifeSpan(Default->InitialLifeSpan);



		if (IPoolableInterface* Poolable = Cast<IPoolableInterface>(Recycled))
		{
			Poolable->OnUnpooled();
			Poolable->StartLogic();
#ifdef WITH_EDITOR
			if (bDebugPooling)
			{
				UKismetSystemLibrary::PrintString(this, "OnUnpooled pooled actor: " + Recycled->GetActorLabel(), true, true, FLinearColor::Yellow);
			}
#endif
		}

		return Recycled;
	}
	else
	{
		if (!Cast<IPoolableInterface>(ActorClass.GetDefaultObject()))
		{
			UE_LOG(LogPooling, Error, TEXT("%s() Caller passed in actor that doesn't implement IPoolableInterface... Returning nullptr"), ANSI_TO_TCHAR(__FUNCTION__));
			return nullptr;
		}

		ASSActor* NewActor;
		NewActor = Cast<ASSActor>(World->SpawnActorDeferred<ASSActor>(ActorClass, Transform, ActorOwner, ActorInstigator));
		UGameplayStatics::FinishSpawningActor(NewActor, Transform);
		if (IPoolableInterface* Poolable = Cast<IPoolableInterface>(NewActor))
		{
			Poolable->StartLogic();

#ifdef WITH_EDITOR
			if (bDebugPooling)
			{
				UKismetSystemLibrary::PrintString(this, "Spawned new actor: " + NewActor->GetActorLabel(), true, true, FLinearColor::Yellow);
			}
#endif
		}

		return NewActor;
	}
}

void UActorPoolerSubsystem::DeativateToPool(ASSActor* ActorToDeactivate)
{
	if (!ActorToDeactivate)
	{
		return;
	}
	IPoolableInterface* Poolable = Cast<IPoolableInterface>(ActorToDeactivate);
	if (!Poolable)
	{
		return;
	}
	if (Poolable->bIsCurentlyInPool)
	{
		UE_LOG(LogPooling, Error, TEXT("%s() Tried to deactivate to pool but already is in pool"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}


	ActorToDeactivate->SetActorHiddenInGame(true);
	ActorToDeactivate->SetActorTickEnabled(false);
	ActorToDeactivate->SetActorEnableCollision(false);
	Pooled.Add(ActorToDeactivate);


	Poolable->OnPooled();
	Poolable->EndLogic();

	if (Pooled.Num() > maxPoolSize)
	{
		ASSActor* Oldest = (Pooled[0].Get());
		Pooled.RemoveAtSwap(0);
		if (Oldest) 
		{ 
			Oldest->Destroy();
#ifdef WITH_EDITOR
			if (bDebugPooling)
			{
				UKismetSystemLibrary::PrintString(this, "Destroyed oldest object in pool to create more pool space: Pooled.Num() = " + FString::FromInt(Pooled.Num()), true, true, FLinearColor::Gray);
			}
#endif
		}
	}

#ifdef WITH_EDITOR
	if (bDebugPooling)
	{
		UKismetSystemLibrary::PrintString(this, "Actor: " + ActorToDeactivate->GetActorLabel() + " pooled: Pooled.Num() = " + FString::FromInt(Pooled.Num()), true, true, FLinearColor::Yellow);
	}
#endif
}








int32 UActorPoolerSubsystem::GetCurrentPoolSize()
{
	return Pooled.Num();
}

bool UActorPoolerSubsystem::IsPoolFull()
{
	return (Pooled.Num() / maxPoolSize) == 1;
}
