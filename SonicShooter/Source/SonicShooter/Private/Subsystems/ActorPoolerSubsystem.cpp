// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ActorPoolerSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actor/SSActor.h"


UActorPoolerSubsystem::UActorPoolerSubsystem()
{

}

ASSActor* UActorPoolerSubsystem::GetFromPool(UClass* BulletClass)
{
	UWorld* World = GetWorld();

	
	//find first of correct class;
	bool CleanupRequired = false;

	int32 FoundIndex = Pooled.IndexOfByPredicate(
		[&](auto InItem) {
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
		if (DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, TEXT("Invalid reference in pool, cleaning up"));
		}
#endif
		Pooled.RemoveAll([&](auto InItem) {
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

ASSActor* UActorPoolerSubsystem::SpawnOrReactivate(TSubclassOf<class ASSActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator)
{
	UWorld* World = GetWorld();

	ASSActor* Recycled = GetFromPool(BulletClass);

	if (Recycled)
	{
		ASSActor* Default = Cast<ASSActor>(BulletClass->GetDefaultObject());

		Recycled->SetOwner(BulletOwner);
		Recycled->SetInstigator(BulletInstigator);
		Recycled->SetActorTransform(Transform);
		Recycled->SetActorHiddenInGame(Default->IsHidden());
		Recycled->SetActorTickEnabled(true);
		Recycled->SetLifeSpan(Default->InitialLifeSpan);


		Recycled->OnUnpooled();
		Recycled->StartLogic();
#ifdef WITH_EDITOR
		/*if (Recycled->DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("OnUnpooled pooled actor"));
		}*/
#endif
		return Recycled;
	}
	else
	{
		ASSActor* NewActor;
		NewActor = Cast<ASSActor>(World->SpawnActorDeferred<ASSActor>(BulletClass, Transform, BulletOwner, BulletInstigator));
		UGameplayStatics::FinishSpawningActor(NewActor, Transform);
		NewActor->StartLogic();
#ifdef WITH_EDITOR
		/*if (NewActor->DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Orange, TEXT("Spawning new actor"));
		}*/
#endif
		return NewActor;
	}
}

void UActorPoolerSubsystem::LifeSpanExpired()
{
	//Deactivate();
}

void UActorPoolerSubsystem::DeativateToPool(ASSActor* ActorToDeactivate)
{
	if (!ActorToDeactivate)
	{
		return;
	}

	if (EnablePooling)
	{
		ActorToDeactivate->SetActorHiddenInGame(true);
		ActorToDeactivate->SetActorTickEnabled(false);
		Pooled.Add(ActorToDeactivate);


		ActorToDeactivate->OnPooled();
		ActorToDeactivate->EndLogic();

		if (Pooled.Num() > MaxPoolSize)
		{
			ASSActor* Oldest = (Pooled[0].Get());
			Pooled.RemoveAtSwap(0);
			if (Oldest) { Oldest->Destroy(); }
		}

#ifdef WITH_EDITOR
		if (DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, FString("Actor pooled: ") + FString::FromInt(Pooled.Num()));
		}
#endif
	}
	else
	{
		ActorToDeactivate->EndLogic();
		ActorToDeactivate->Destroy();
	}
}
