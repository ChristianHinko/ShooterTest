// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ActorPoolerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/SSActor.h"
#include "Interfaces/Poolable.h"


UActorPoolerSubsystem::UActorPoolerSubsystem()
{

}

ASSActor* UActorPoolerSubsystem::GetFromPool(UClass* ActorClass)
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
		GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, TEXT("Invalid reference in pool, cleaning up"));
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

	ASSActor* Recycled = GetFromPool(ActorClass);

	if (Recycled)
	{
		ASSActor* Default = Cast<ASSActor>(ActorClass->GetDefaultObject());

		Recycled->SetOwner(ActorOwner);
		Recycled->SetInstigator(ActorInstigator);
		Recycled->SetActorTransform(Transform);
		Recycled->SetActorHiddenInGame(Default->IsHidden());
		Recycled->SetActorTickEnabled(true);
		Recycled->SetLifeSpan(Default->InitialLifeSpan);



		if (IPoolable* Poolable = Cast<IPoolable>(Recycled))
		{
			Poolable->OnUnpooled();
			Poolable->StartLogic();
#ifdef WITH_EDITOR
			if (Poolable->bDebugPooling)
			{
				GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("OnUnpooled pooled actor"));
			}
#endif
		}

		return Recycled;
	}
	else
	{
		ASSActor* NewActor;
		NewActor = Cast<ASSActor>(World->SpawnActorDeferred<ASSActor>(ActorClass, Transform, ActorOwner, ActorInstigator));
		UGameplayStatics::FinishSpawningActor(NewActor, Transform);
		if (IPoolable* Poolable = Cast<IPoolable>(NewActor))
		{
			Poolable->StartLogic();

#ifdef WITH_EDITOR
			if (Poolable->bDebugPooling)
			{
				GEngine->AddOnScreenDebugMessage(0, 2, FColor::Orange, TEXT("Spawning new actor"));
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
	IPoolable* Poolable = Cast<IPoolable>(ActorToDeactivate);
	if (!Poolable)
	{
		return;
	}


	ActorToDeactivate->SetActorHiddenInGame(true);
	ActorToDeactivate->SetActorTickEnabled(false);
	Pooled.Add(ActorToDeactivate);


	Poolable->OnPooled();
	Poolable->EndLogic();

	if (Pooled.Num() > MaxPoolSize)
	{
		ASSActor* Oldest = (Pooled[0].Get());
		Pooled.RemoveAtSwap(0);
		if (Oldest) 
		{ 
			Oldest->Destroy(); 
		}
	}

#ifdef WITH_EDITOR
	if (Poolable->bDebugPooling)
	{
		GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, FString("Actor pooled: ") + FString::FromInt(Pooled.Num()));
	}
#endif
}
