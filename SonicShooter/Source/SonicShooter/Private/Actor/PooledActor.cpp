// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor\PooledActor.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"



// Sets default values
APooledActor::APooledActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APooledActor::Deactivate()
{
	//server only
	if (!HasAuthority()) 
	{ 
		return;
	}
	this->DeativateToPool();	// Doesn't a multicast already call on server as well?
	DeactivationBroadcast();
}

APooledActor* APooledActor::GetFromPool(UWorld* World, UClass* BulletClass)
{
	APooledActor* Pool = Cast<APooledActor>(BulletClass->GetDefaultObject());

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

		TWeakObjectPtr<APooledActor> Found = nullptr;
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

APooledActor* APooledActor::SpawnOrReactivate(UWorld* World, TSubclassOf<class APooledActor> BulletClass, const FTransform& Transform, FVector BulletVelocity, AActor* BulletOwner, APawn* BulletInstigator)
{
	APooledActor* bullet;

	APooledActor* Recycled = GetFromPool(World, BulletClass);

	if (Recycled)
	{
		APooledActor* Default = Cast<APooledActor>(BulletClass->GetDefaultObject());

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
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Recycling pooled bullet"));
		}
#endif
		return Recycled;
	}
	else
	{
		bullet = Cast<APooledActor>(World->SpawnActorDeferred<APooledActor>(BulletClass, Transform, BulletOwner, BulletInstigator));
		UGameplayStatics::FinishSpawningActor(bullet, Transform);
#ifdef WITH_EDITOR
		if (bullet->DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(0, 2, FColor::Orange, TEXT("Spawning new bullet"));
		}
#endif
		return bullet;
	}
}

void APooledActor::ReactivationBroadcast_Implementation(FVector_NetQuantize NewLocation, FVector NewVelocity, AActor* BulletOwner, APawn* BulletInstigator)
{
	if (!HasAuthority())
	{
		APooledActor* Default = Cast<APooledActor>(this->StaticClass()->GetDefaultObject());

		SetOwner(BulletOwner);
		SetInstigator(BulletInstigator);

		SetActorLocation(UGameplayStatics::RebaseZeroOriginOntoLocal(GetWorld(), NewLocation));

		SetActorHiddenInGame(Default->IsHidden());
		SetActorTickEnabled(true);
		BeginPlay();
	}
}

void APooledActor::DeactivationBroadcast_Implementation()
{
	if (!HasAuthority())
	{
		this->DeativateToPool();
	}
}

void APooledActor::LifeSpanExpired()
{
	Deactivate();
}

void APooledActor::DeativateToPool()
{
	APooledActor* Pool = Cast<APooledActor>(GetClass()->GetDefaultObject());

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
			APooledActor* Oldest = (Pool->Pooled[0].Get());
			Pool->Pooled.RemoveAtSwap(0);
			if (Oldest) { Oldest->Destroy(); }
		}

#ifdef WITH_EDITOR
		if (DebugPooling)
		{
			GEngine->AddOnScreenDebugMessage(2, 2, FColor::White, FString("Bullet pooled: ") + FString::FromInt(Pool->Pooled.Num()));
		}
#endif
	}
	else
	{
		Destroy();
	}
}
