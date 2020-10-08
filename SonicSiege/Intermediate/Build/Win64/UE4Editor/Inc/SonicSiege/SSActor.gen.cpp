// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/SSActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSActor() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSActor_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void ASSActor::StaticRegisterNativesASSActor()
	{
	}
	UClass* Z_Construct_UClass_ASSActor_NoRegister()
	{
		return ASSActor::StaticClass();
	}
	struct Z_Construct_UClass_ASSActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASSActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base actor class (without GAS implemeted)\n */" },
		{ "IncludePath", "Actor/SSActor.h" },
		{ "ModuleRelativePath", "Public/Actor/SSActor.h" },
		{ "ToolTip", "Base actor class (without GAS implemeted)" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASSActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASSActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASSActor_Statics::ClassParams = {
		&ASSActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASSActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASSActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASSActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASSActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASSActor, 3628270736);
	template<> SONICSIEGE_API UClass* StaticClass<ASSActor>()
	{
		return ASSActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASSActor(Z_Construct_UClass_ASSActor, &ASSActor::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASSActor"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASSActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
