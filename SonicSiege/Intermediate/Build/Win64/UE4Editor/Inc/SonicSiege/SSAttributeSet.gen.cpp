// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/SSAttributeSet.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSAttributeSet() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void USSAttributeSet::StaticRegisterNativesUSSAttributeSet()
	{
	}
	UClass* Z_Construct_UClass_USSAttributeSet_NoRegister()
	{
		return USSAttributeSet::StaticClass();
	}
	struct Z_Construct_UClass_USSAttributeSet_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSAttributeSet_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSAttributeSet_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * All Attribute Sets in this project inherit from this\n */" },
		{ "IncludePath", "AbilitySystem/SSAttributeSet.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSAttributeSet.h" },
		{ "ToolTip", "All Attribute Sets in this project inherit from this" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSAttributeSet_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSAttributeSet>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSAttributeSet_Statics::ClassParams = {
		&USSAttributeSet::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USSAttributeSet_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSAttributeSet_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSAttributeSet()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSAttributeSet_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSAttributeSet, 378493840);
	template<> SONICSIEGE_API UClass* StaticClass<USSAttributeSet>()
	{
		return USSAttributeSet::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSAttributeSet(Z_Construct_UClass_USSAttributeSet, &USSAttributeSet::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSAttributeSet"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSAttributeSet);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
