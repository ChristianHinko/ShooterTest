// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/AbilityTasks/AT_DurationInteractCallbacks.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAT_DurationInteractCallbacks() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_DurationInteractCallbacks_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_DurationInteractCallbacks();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASiegeCharacter_NoRegister();
// End Cross Module References
	void UAT_DurationInteractCallbacks::StaticRegisterNativesUAT_DurationInteractCallbacks()
	{
	}
	UClass* Z_Construct_UClass_UAT_DurationInteractCallbacks_NoRegister()
	{
		return UAT_DurationInteractCallbacks::StaticClass();
	}
	struct Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SiegeCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SiegeCharacter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAbilityTask,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/AbilityTasks/AT_DurationInteractCallbacks.h" },
		{ "ModuleRelativePath", "Public/Character/AbilityTasks/AT_DurationInteractCallbacks.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::NewProp_SiegeCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilityTasks/AT_DurationInteractCallbacks.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::NewProp_SiegeCharacter = { "SiegeCharacter", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAT_DurationInteractCallbacks, SiegeCharacter), Z_Construct_UClass_ASiegeCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::NewProp_SiegeCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::NewProp_SiegeCharacter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::NewProp_SiegeCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAT_DurationInteractCallbacks>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::ClassParams = {
		&UAT_DurationInteractCallbacks::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAT_DurationInteractCallbacks()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAT_DurationInteractCallbacks_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAT_DurationInteractCallbacks, 2844965568);
	template<> SONICSIEGE_API UClass* StaticClass<UAT_DurationInteractCallbacks>()
	{
		return UAT_DurationInteractCallbacks::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAT_DurationInteractCallbacks(Z_Construct_UClass_UAT_DurationInteractCallbacks, &UAT_DurationInteractCallbacks::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAT_DurationInteractCallbacks"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAT_DurationInteractCallbacks);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
