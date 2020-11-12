// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ActorPoolerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/SSActor.h"
#include "Interfaces/Poolable.h"
#include "Kismet/KismetSystemLibrary.h"


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
				UKismetSystemLibrary::PrintString(this, "OnUnpooled pooled actor", true, true, FLinearColor::Yellow);
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
				UKismetSystemLibrary::PrintString(this, "Spawning new actor", true, true, FLinearColor::Yellow);
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
		UKismetSystemLibrary::PrintString(this, "Actor pooled" + FString::FromInt(Pooled.Num()), true, true, FLinearColor::Yellow);
	}
#endif
}
