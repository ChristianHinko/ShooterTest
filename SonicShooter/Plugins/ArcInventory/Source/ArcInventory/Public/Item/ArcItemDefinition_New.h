// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTags.h"
#include "UI/ArcInvUIData.h"
#include "ArcItemDefinition_New.generated.h"

class UArcItemStack;
class UStaticMesh;
class UArcInventoryBaseItemCardWidget;
class AArcItemStackWorldObject;


UCLASS(Blueprintable, Abstract, BlueprintType)
class ARCINVENTORY_API UArcUIData_ItemDefinition : public UArcInvUIData
{
	GENERATED_BODY()
public:
	UArcUIData_ItemDefinition();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<UArcInventoryBaseItemCardWidget> SmallItemCard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		TSubclassOf<UArcInventoryBaseItemCardWidget> ItemTooltip;

};

/** Item Definition
 * Base Class for all item definitions.  Developers subclass this to create new item types.  
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class ARCINVENTORY_API UArcItemDefinition_New : public UObject, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
public:
	UArcItemDefinition_New();

	//Max stack size of this item, if it can stack
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Gameplay")
	int32 MaxStackSize;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Gameplay")
	TSubclassOf<UArcItemStack> DefaultItemStackClass;
	
	//-------------------=@MODIFIED MARKER@=	Not using WorldItemModel. We will use our WorldItemActor instead so we get more functionality. Only reason I didn't comment out WorldItemMoel is because of error hell.
	UPROPERTY(/*BlueprintReadWrite, EditDefaultsOnly, Category = "Display"*/)
		UStaticMesh* WorldItemModel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Display")
		TSubclassOf<AArcItemStackWorldObject> WorldItemActor;
	//-------------------

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadWrite, Category = "UI", Meta = (AssetBundles = "UI"))
	UArcUIData_ItemDefinition* UIData;

	//Tags that describe this team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tags)
	FGameplayTagContainer OwnedTags;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.AppendTags(OwnedTags);
	}

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	

};
