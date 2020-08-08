// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Engine/SSEngineSubsystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSEngineSubsystem() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_USSEngineSubsystem_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSEngineSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_UEngineSubsystem();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void USSEngineSubsystem::StaticRegisterNativesUSSEngineSubsystem()
	{
	}
	UClass* Z_Construct_UClass_USSEngineSubsystem_NoRegister()
	{
		return USSEngineSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_USSEngineSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSEngineSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEngineSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSEngineSubsystem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Engine/SSEngineSubsystem.h" },
		{ "ModuleRelativePath", "Public/Engine/SSEngineSubsystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSEngineSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSEngineSubsystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSEngineSubsystem_Statics::ClassParams = {
		&USSEngineSubsystem::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_USSEngineSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSEngineSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSEngineSubsystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSEngineSubsystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSEngineSubsystem, 2617547797);
	template<> SONICSIEGE_API UClass* StaticClass<USSEngineSubsystem>()
	{
		return USSEngineSubsystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSEngineSubsystem(Z_Construct_UClass_USSEngineSubsystem, &USSEngineSubsystem::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSEngineSubsystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSEngineSubsystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
