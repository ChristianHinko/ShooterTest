// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcInventoryItemTypes.h"
#include "GameplayTags.h"
#include "ArcItemGenerator.generated.h"

class UArcItemDefinition_New;
class UArcItemRarity;
class UArcInvUIData;

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class ARCINVENTORY_API UArcItemGenerator : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	UArcItemGenerator(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	TSubclassOf<UArcItemStack> ItemStackClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default")
	FGameplayTagContainer OwnedTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.AppendTags(OwnedTags);
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "UI", Meta = (AssetBundles = "UI"))
	UArcInvUIData* UIData;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Generator")
	UArcItemStack* GenerateItemStack(const FArcItemGeneratorContext& Context);
	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context);
		
protected:
	virtual UArcItemStack* CreateNewItemStack(TSubclassOf<UArcItemDefinition_New> ItemDefinition, UArcItemRarity* ItemRarity);

};

UCLASS()
class ARCINVENTORY_API UArcItemGenerator_Static : public UArcItemGenerator
{
	GENERATED_BODY()
public:
	UArcItemGenerator_Static(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator")
	TSubclassOf<UArcItemGenerator> StaticGenerator;

	virtual UArcItemStack* GenerateItemStack_Implementation(const FArcItemGeneratorContext& Context) override;
};