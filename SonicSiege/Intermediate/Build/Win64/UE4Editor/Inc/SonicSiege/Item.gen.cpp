// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/Item/Item.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeItem() {}
// Cross Module References
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FItemInfo();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_AItem_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AItem();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemActor();
	SONICSIEGE_API UClass* Z_Construct_UClass_UInteractable_NoRegister();
// End Cross Module References
class UScriptStruct* FItemInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SONICSIEGE_API uint32 Get_Z_Construct_UScriptStruct_FItemInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FItemInfo, Z_Construct_UPackage__Script_SonicSiege(), TEXT("ItemInfo"), sizeof(FItemInfo), Get_Z_Construct_UScriptStruct_FItemInfo_Hash());
	}
	return Singleton;
}
template<> SONICSIEGE_API UScriptStruct* StaticStruct<FItemInfo>()
{
	return FItemInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FItemInfo(FItemInfo::StaticStruct, TEXT("/Script/SonicSiege"), TEXT("ItemInfo"), false, nullptr, nullptr);
static struct FScriptStruct_SonicSiege_StaticRegisterNativesFItemInfo
{
	FScriptStruct_SonicSiege_StaticRegisterNativesFItemInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("ItemInfo")),new UScriptStruct::TCppStructOps<FItemInfo>);
	}
} ScriptStruct_SonicSiege_StaticRegisterNativesFItemInfo;
	struct Z_Construct_UScriptStruct_FItemInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FItemInfo_Statics::Struct_MetaDataParams[] = {
		{ "Comment", "/**\n * This should store the info for an Item so we can avoid casting for no reason.\n */" },
		{ "ModuleRelativePath", "Public/Actor/Item/Item.h" },
		{ "ToolTip", "This should store the info for an Item so we can avoid casting for no reason." },
	};
#endif
	void* Z_Construct_UScriptStruct_FItemInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FItemInfo>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FItemInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
		nullptr,
		&NewStructOps,
		"ItemInfo",
		sizeof(FItemInfo),
		alignof(FItemInfo),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FItemInfo_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FItemInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FItemInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FItemInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("ItemInfo"), sizeof(FItemInfo), Get_Z_Construct_UScriptStruct_FItemInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FItemInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FItemInfo_Hash() { return 3959414250U; }
	void AItem::StaticRegisterNativesAItem()
	{
	}
	UClass* Z_Construct_UClass_AItem_NoRegister()
	{
		return AItem::StaticClass();
	}
	struct Z_Construct_UClass_AItem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AItem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAbilitySystemActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AItem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Actor/Item/Item.h" },
		{ "ModuleRelativePath", "Public/Actor/Item/Item.h" },
	};
#endif
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AItem_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UInteractable_NoRegister, (int32)VTABLE_OFFSET(AItem, IInteractable), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AItem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AItem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AItem_Statics::ClassParams = {
		&AItem::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AItem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AItem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AItem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AItem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AItem, 3187262896);
	template<> SONICSIEGE_API UClass* StaticClass<AItem>()
	{
		return AItem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AItem(Z_Construct_UClass_AItem, &AItem::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AItem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AItem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
