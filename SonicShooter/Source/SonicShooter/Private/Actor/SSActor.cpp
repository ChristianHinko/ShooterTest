// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SSActor.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ASSActor::ASSActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASSActor::Deactivate()
{
	//server only
	if (!HasAuthority())
	{
		return;
	}
	this->DeativateToPool();
	DeactivationBroadcast();
}

ASSActor* ASSActor::GetFromPool(UWorld* World, UClass* BulletClass)
{
	ASSActor* Pool = Cast<ASSActor>(BulletClass->GetDefaultObject());

	if (Pool)
	{
		//find first of correct class;
		bool CleanupRequired = false;

		int32 FoundIndex = Pool->Pooled.IndexOfByPredicate(
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
			Found = Pool->Pooled[FoundIndex];
			Pool->Pooled.RemoveAtSwap(FoundIndex);
		}

		if (CleanupRequired)
		{
#ifdef WITH_EDITOR
			if (Pool->DebugPooling)
			{
				GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, TEXT("Invalid reference in pool, cleaning up"));
			}
#endif
			Pool->Pooled.RemoveAll([&](auto InItem) {
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
	else
	{
		return nullptr;
	}
}

ASSActor* ASSActor::SpawnOrReactivate(UWorld* World, TSubclassOf<class ASSActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator)
{
	ASSActor* bullet;

	ASSActor* Recycled = GetFromPool(World, BulletClass);

	if (Recycled)
	{
		ASSActor* Default = Cast<ASSActor>(BulletClass->GetDefaultObject());

		Recycled->SetOwner(BulletOwner);
		Recycled->SetInstigator(BulletInstigator);
		Recycled->SetActorTransform(Transform);
		Recycled->SetActorHiddenInGame(Default->IsHidden());
		Recycled->SetActorTickEnabled(true);
		Recycled->SetLifeSpan(Default->InitialLifeSpan);
		if (!Recycled->HasActorBegunPlay())
		{
			Recycled->BeginPlay();
		}
		Recycled->ReactivationBroadcast(UGameplayStatics::RebaseLocalOriginOntoZero(Recycled->GetWorld(), Transform.GetLocation()), BulletVelocity, BulletOwner, BulletInstigator);
#ifdef WITH_EDITOR
		if (Recycled->DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Recycling pooled actor"));
		}
#endif
		return Recycled;
	}
	else
	{
		bullet = Cast<ASSActor>(World->SpawnActorDeferred<ASSActor>(BulletClass, Transform, BulletOwner, BulletInstigator));
		UGameplayStatics::FinishSpawningActor(bullet, Transform);
#ifdef WITH_EDITOR
		if (bullet->DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Orange, TEXT("Spawning new actor"));
		}
#endif
		return bullet;
	}
}

void ASSActor::ReactivationBroadcast_Implementation(FVector_NetQuantize NewLocation, FVector NewVelocity, AActor* BulletOwner, APawn* BulletInstigator)
{
	if (!HasAuthority())
	{
		ASSActor* Default = Cast<ASSActor>(this->StaticClass()->GetDefaultObject());

		SetOwner(BulletOwner);
		SetInstigator(BulletInstigator);

		SetActorLocation(UGameplayStatics::RebaseZeroOriginOntoLocal(GetWorld(), NewLocation));

		SetActorHiddenInGame(Default->IsHidden());
		SetActorTickEnabled(true);
		BeginPlay();
	}
}

void ASSActor::DeactivationBroadcast_Implementation()
{
	if (!HasAuthority())
	{
		this->DeativateToPool();
	}
}

void ASSActor::LifeSpanExpired()
{
	Deactivate();
}

void ASSActor::DeativateToPool()
{
	ASSActor* Pool = Cast<ASSActor>(GetClass()->GetDefaultObject());

	if (Pool && EnablePooling)
	{
		SetActorHiddenInGame(true);
		SetActorTickEnabled(false);
		Pool->Pooled.Add(this);
		if (HasActorBegunPlay())
		{
			EndPlay(EEndPlayReason::RemovedFromWorld);
		}

		if (Pool->Pooled.Num() > MaxPoolSize)
		{
			ASSActor* Oldest = (Pool->Pooled[0].Get());
			Pool->Pooled.RemoveAtSwap(0);
			if (Oldest) { Oldest->Destroy(); }
		}

#ifdef WITH_EDITOR
		if (DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, FString("Actor pooled: ") + FString::FromInt(Pool->Pooled.Num()));
		}
#endif
	}
	else
	{
		Destroy();
	}
}