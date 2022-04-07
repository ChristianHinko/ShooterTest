// Copyright 2017-2020 Puny Human, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "Engine/NetSerialization.h"
#include "ArcInventoryDeveloperSettings.h"
#include "Perks/ArcItemPerkTypes.h"
#include "ArcInventoryItemTypes.generated.h"

ARCINVENTORY_API extern const int32 NAMED_ITEM_SLOT;

class UArcOLDItemDefition;
class UArcItemRarity;		
class UArcInventoryComponent;
class UArcItemStack;
class UGameplayAbility;
class UGameplayEffect;
class UArcInvInputBinder;

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcStartingItemEntry
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", Instanced)
	class UArcItemGenerator* ItemGenerator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FGameplayTagQuery SlotQuery;
};

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcItemActiveAbilityEntry
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UGameplayAbility> ActiveAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Item")
	UArcInvInputBinder* InputBinder;

};


USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcItemDefinition_AbilityInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FArcItemDefinition_AbilityInfo()
	{

	}

	//Granted Tags when this item is made active
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
		FGameplayTagContainer GrantedTags;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	TArray<FArcItemActiveAbilityEntry> ActiveAbilityEntries;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
		TArray<TSubclassOf<UGameplayAbility>> ExtraAbilities;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
		TArray<TSubclassOf<UGameplayEffect>> AddedGameplayEffects;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	TMap<FGameplayAttribute, float> AttributeInitalizers;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Item")
	TArray<TSubclassOf<UAttributeSet>> AttributeSetsToAdd;	
};

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcItemGeneratorContext
{
	GENERATED_USTRUCT_BODY();
public:
	FArcItemGeneratorContext()
	{
		Quality = 0;
		UserObject = nullptr;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generator Context")
		int32 Quality;

	//An Object set by the user	for use as a reference elsewhere
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generator Context")
		UObject* UserObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generator Context")
		TArray<AActor*> TrackingActors;
};	 


USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcInventoryItemSlotFilter
{
	GENERATED_USTRUCT_BODY()
public:
	FArcInventoryItemSlotFilter()
	{
		ForceSingleStack = false;
	}

	FArcInventoryItemSlotFilter(const FArcInventoryItemSlotFilter& Other)
		: FilterQuery(Other.FilterQuery),
		ForceSingleStack(Other.ForceSingleStack)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter)
	FGameplayTagQuery FilterQuery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Filter)
	bool ForceSingleStack;

	bool AcceptsItem(UArcItemStack* ItemStack) const;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FArcInventoryItemSlotFilter> : public TStructOpsTypeTraitsBase2<FArcInventoryItemSlotFilter>
{
	enum
	{
		WithNetSerializer = true,
	};
};

USTRUCT()
struct ARCINVENTORY_API FArcInventoryItemSlotFilterHandle
{
	GENERATED_USTRUCT_BODY()
public:
	FArcInventoryItemSlotFilterHandle()
		: Data(nullptr)
	{

	}

	FArcInventoryItemSlotFilterHandle(FArcInventoryItemSlotFilter* Filter)
		: Data(Filter)
	{

	}	

	bool IsValid() const
	{
		return Data.IsValid();
	}

	bool AcceptsItem(UArcItemStack* ItemStack)	const
	{
		if (!IsValid())
		{
			return false;
		}
		return Data->AcceptsItem(ItemStack);
	}

	TSharedPtr<FArcInventoryItemSlotFilter> Data;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template<>
struct TStructOpsTypeTraits<FArcInventoryItemSlotFilterHandle> : public TStructOpsTypeTraitsBase2<FArcInventoryItemSlotFilterHandle>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true,
	};
};

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcInventoryItemSlot : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()
public:
	FArcInventoryItemSlot()
		:FFastArraySerializerItem(),
		ItemStack(nullptr),
		SlotId(NAMED_ITEM_SLOT),
		SlotTags(),
		OldItemStack(nullptr)
	{
		
	}

	FArcInventoryItemSlot(const FArcInventoryItemSlot& Copy)
		: FFastArraySerializerItem(Copy),
		ItemStack(Copy.ItemStack),
		ItemSlotFilter(Copy.ItemSlotFilter),
		SlotId(Copy.SlotId),
		SlotTags(Copy.SlotTags),
		OldItemStack(nullptr)
	{

	}
		   			 
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = Inventory)
	UArcItemStack* ItemStack;

	UPROPERTY()
	FArcInventoryItemSlotFilterHandle ItemSlotFilter;	
	
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = Inventory)
	int32 SlotId;	  
	
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = Inventory)
	FGameplayTagContainer SlotTags;

	TWeakObjectPtr<UArcItemStack> OldItemStack;


	static FArcInventoryItemSlot Invalid;

	void ToDebugStrings(TArray<FString>& OutStrings, bool Detailed) const;
	/** Comparison operator */
	bool operator==(FArcInventoryItemSlot const& Other) const
	{
		return SlotId == Other.SlotId && ItemStack == Other.ItemStack;
	}

	/** Comparison operator */
	bool operator!=(FArcInventoryItemSlot const& Other) const
	{
		return !(FArcInventoryItemSlot::operator==(Other));
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	void PreReplicatedRemove(const struct FArcInventoryItemSlotArray& InArraySerializer);
	void PostReplicatedAdd(const struct FArcInventoryItemSlotArray& InArraySerializer);
	void PostReplicatedChange(const struct FArcInventoryItemSlotArray& InArraySerializer);

private:
	UArcInventoryComponent* Owner;

	friend class UArcInventoryComponent;
};


template<>
struct TStructOpsTypeTraits<FArcInventoryItemSlot> : public TStructOpsTypeTraitsBase2<FArcInventoryItemSlot>
{
	enum
	{
		WithNetSerializer = true,
		WithIdenticalViaEquality = true,
	};
};



USTRUCT()
struct FArcInventoryItemSlotArray : public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY()
	TArray< FArcInventoryItemSlot> Slots;

	UPROPERTY()
	UArcInventoryComponent* Owner;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FArcInventoryItemSlot, FArcInventoryItemSlotArray>(Slots, DeltaParms, *this);
	}

};

template<>
struct TStructOpsTypeTraits< FArcInventoryItemSlotArray > : public TStructOpsTypeTraitsBase2< FArcInventoryItemSlotArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcInventoryItemSlotReference
{
	GENERATED_USTRUCT_BODY()
public:

	FArcInventoryItemSlotReference()
		: SlotId(NAMED_ITEM_SLOT)
		, SlotTags()
		, ParentInventory(nullptr)
	{
		
	}
		
	FArcInventoryItemSlotReference(const FArcInventoryItemSlotReference& Copy)
		: SlotId(Copy.SlotId),
		SlotTags(Copy.SlotTags),
		ParentInventory(Copy.ParentInventory)
	{

	}

	FArcInventoryItemSlotReference(const FArcInventoryItemSlot& FromSlot, UArcInventoryComponent* InParentInventory)
		: SlotId(FromSlot.SlotId)
		, SlotTags(FromSlot.SlotTags)
		, ParentInventory(InParentInventory)
	{

	}

	FArcInventoryItemSlotReference(FGameplayTag InTag, UArcInventoryComponent* InParentInventory)
		: SlotId(NAMED_ITEM_SLOT)
		, SlotTags(InTag.GetSingleTagContainer())
		, ParentInventory(InParentInventory)
	{

	}

	FArcInventoryItemSlotReference(int32 InSlotId, UArcInventoryComponent* InParentInventory)
		: SlotId(InSlotId)
		, SlotTags()
		, ParentInventory(InParentInventory)
	{

	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
		int32 SlotId;	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Inventory)
	FGameplayTagContainer SlotTags;


	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Category = Inventory)
	class UArcInventoryComponent* ParentInventory;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	FString ToString() const;

	static FArcInventoryItemSlotReference Invalid;

	/** Comparison operator */
	bool operator==(const FArcInventoryItemSlotReference& Other) const
	{
		const bool bIdsMatch = SlotId == Other.SlotId;
		const bool bParentsMatch = ParentInventory == Other.ParentInventory;
		const bool TagsMatch = SlotTags.HasAllExact(Other.SlotTags);

		return bParentsMatch && bIdsMatch && TagsMatch;
	}

	/** Comparison operator */
	bool operator!=(const FArcInventoryItemSlotReference& Other) const
	{
		return !(FArcInventoryItemSlotReference::operator==(Other));
	}

	bool operator==(const FArcInventoryItemSlot& Other) const
	{
		const bool bIdsMatch = SlotId == Other.SlotId;
		const bool TagsMatch = SlotTags.HasAllExact(Other.SlotTags);

		return bIdsMatch && TagsMatch;
	}

	bool operator!=(const FArcInventoryItemSlot& Other) const
	{
		return !(FArcInventoryItemSlotReference::operator==(Other));
	}
};

template<>
struct TStructOpsTypeTraits<FArcInventoryItemSlotReference> : public TStructOpsTypeTraitsBase2<FArcInventoryItemSlotReference>
{
	enum
	{
		WithNetSerializer = true,
	};
};


USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcInventoryQuery
{
	GENERATED_USTRUCT_BODY()
public:
	FArcInventoryQuery()
	{

	}
	  		 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Filter")
	FGameplayTagQuery ItemTypeQuery;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Filter")
	FGameplayTagQuery SlotTypeQuery;

	bool MatchesSlot(const FArcInventoryItemSlot& ItemSlot) const;

	static FArcInventoryQuery QuerySlotMatchingTag(FGameplayTag Tag);
	static FArcInventoryQuery QueryForMatchingItemTag(FGameplayTag Tag);
	
	static FArcInventoryQuery QueryForSlot(const FGameplayTagQuery& SlotQuery);
	static FArcInventoryQuery QueryForItemType(const FGameplayTagQuery& ItemQuery);

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct ARCINVENTORY_API FArcEquippedItemInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FArcEquippedItemInfo()
	{

	}

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AddedAbilities;
	UPROPERTY()
	TArray<UAttributeSet*> InstancedAttributeSets;
	UPROPERTY()
	TArray< FActiveGameplayEffectHandle> AddedGameplayEffects;

};


//---------------------------------------

ARCINVENTORY_API inline bool IsValid(const FArcInventoryItemSlotFilterHandle& Handle)
{
	return Handle.IsValid();
}

ARCINVENTORY_API bool IsValid(const FArcInventoryItemSlotReference& ItemRef);

