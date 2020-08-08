// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/SSCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSCharacter() {}
// Cross Module References
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FItemInfo();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSCharacter_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSCharacter();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSCharacterMovementComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AItem_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
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
		{ "Comment", "/**\n *  This should store the info for an Item so we can avoid casting for no reason.\n */" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
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
	uint32 Get_Z_Construct_UScriptStruct_FItemInfo_Hash() { return 2925174799U; }
	void ASSCharacter::StaticRegisterNativesASSCharacter()
	{
	}
	UClass* Z_Construct_UClass_ASSCharacter_NoRegister()
	{
		return ASSCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ASSCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SSCharacterMovementComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SSCharacterMovementComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PreviousItem_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PreviousItem;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentItem_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CurrentItem;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Inventory_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Inventory;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Inventory_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_POVMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_POVMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASSCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base character class (without GAS implementation)\n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/SSCharacter.h" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "Base character class (without GAS implementation)" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_SSCharacterMovementComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_SSCharacterMovementComponent = { "SSCharacterMovementComponent", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, SSCharacterMovementComponent), Z_Construct_UClass_USSCharacterMovementComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_SSCharacterMovementComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_SSCharacterMovementComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_PreviousItem_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_PreviousItem = { "PreviousItem", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, PreviousItem), Z_Construct_UClass_AItem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_PreviousItem_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_PreviousItem_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_CurrentItem_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_CurrentItem = { "CurrentItem", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, CurrentItem), Z_Construct_UClass_AItem_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_CurrentItem_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_CurrentItem_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory = { "Inventory", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, Inventory), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory_Inner = { "Inventory", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AItem_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_CameraBoom_MetaData[] = {
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00200800000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_CameraBoom_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_CameraBoom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_FollowCamera_MetaData[] = {
		{ "Category", "Camera" },
		{ "Comment", "// should this exist on every character (including AI)?\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
		{ "ToolTip", "should this exist on every character (including AI)?" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00200800000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_FollowCamera_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_FollowCamera_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSCharacter_Statics::NewProp_POVMesh_MetaData[] = {
		{ "Category", "Character" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSCharacter_Statics::NewProp_POVMesh = { "POVMesh", nullptr, (EPropertyFlags)0x00200800000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSCharacter, POVMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::NewProp_POVMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::NewProp_POVMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASSCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_SSCharacterMovementComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_PreviousItem,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_CurrentItem,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_Inventory_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_CameraBoom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_FollowCamera,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSCharacter_Statics::NewProp_POVMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASSCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASSCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASSCharacter_Statics::ClassParams = {
		&ASSCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASSCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASSCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASSCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASSCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASSCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASSCharacter, 438629985);
	template<> SONICSIEGE_API UClass* StaticClass<ASSCharacter>()
	{
		return ASSCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASSCharacter(Z_Construct_UClass_ASSCharacter, &ASSCharacter::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASSCharacter"), false, nullptr, nullptr, nullptr);

	void ASSCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_Inventory(TEXT("Inventory"));
		static const FName Name_CurrentItem(TEXT("CurrentItem"));
		static const FName Name_PreviousItem(TEXT("PreviousItem"));

		const bool bIsValid = true
			&& Name_Inventory == ClassReps[(int32)ENetFields_Private::Inventory].Property->GetFName()
			&& Name_CurrentItem == ClassReps[(int32)ENetFields_Private::CurrentItem].Property->GetFName()
			&& Name_PreviousItem == ClassReps[(int32)ENetFields_Private::PreviousItem].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ASSCharacter"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASSCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
