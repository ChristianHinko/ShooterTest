// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "Engine/DataAsset.h"
#include "ArcItemRarity.generated.h"


UCLASS(Blueprintable, BlueprintType, EditInlineNew, Abstract)
class ARCINVENTORY_API UArcItemRarity_UserData : public UObject
{
	GENERATED_BODY()
public:

};

/**
 * 
 */
UCLASS(BlueprintType)
class ARCINVENTORY_API UArcItemRarity : public UPrimaryDataAsset, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:

	UArcItemRarity(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity")
	FGameplayTagContainer RarityTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity")
	FGameplayTagContainer TagsGrantedToItem;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity")
	FText RarityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity")
	FLinearColor RarityColor;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category= "Rarity")
	UArcItemRarity_UserData* UserData;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.AppendTags(RarityTags);
	}
	
};
