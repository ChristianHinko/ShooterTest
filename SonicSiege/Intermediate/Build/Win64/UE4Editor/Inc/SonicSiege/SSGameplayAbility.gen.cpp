// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/SSGameplayAbility.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSGameplayAbility() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void USSGameplayAbility::StaticRegisterNativesUSSGameplayAbility()
	{
	}
	UClass* Z_Construct_UClass_USSGameplayAbility_NoRegister()
	{
		return USSGameplayAbility::StaticClass();
	}
	struct Z_Construct_UClass_USSGameplayAbility_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSGameplayAbility_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSGameplayAbility_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base gameplay ability class\n */" },
		{ "IncludePath", "AbilitySystem/SSGameplayAbility.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSGameplayAbility.h" },
		{ "ToolTip", "Base gameplay ability class" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSGameplayAbility_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSGameplayAbility>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSGameplayAbility_Statics::ClassParams = {
		&USSGameplayAbility::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USSGameplayAbility_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSGameplayAbility_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSGameplayAbility()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSGameplayAbility_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSGameplayAbility, 457012438);
	template<> SONICSIEGE_API UClass* StaticClass<USSGameplayAbility>()
	{
		return USSGameplayAbility::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSGameplayAbility(Z_Construct_UClass_USSGameplayAbility, &USSGameplayAbility::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSGameplayAbility"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSGameplayAbility);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
