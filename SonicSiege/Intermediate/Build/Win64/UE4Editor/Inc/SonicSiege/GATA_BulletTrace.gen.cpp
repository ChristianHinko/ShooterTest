// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGATA_BulletTrace() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_BulletTrace_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_BulletTrace();
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_Trace();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void AGATA_BulletTrace::StaticRegisterNativesAGATA_BulletTrace()
	{
	}
	UClass* Z_Construct_UClass_AGATA_BulletTrace_NoRegister()
	{
		return AGATA_BulletTrace::StaticClass();
	}
	struct Z_Construct_UClass_AGATA_BulletTrace_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bulletSpread_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_bulletSpread;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_numberOfBullets_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_numberOfBullets;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGATA_BulletTrace_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGATA_Trace,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_BulletTrace_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_bulletSpread_MetaData[] = {
		{ "Category", "Bullet Config" },
		{ "Comment", "/** Radius of cone which bullets can spread. In degrees (90 degs will make a right angle cone) */" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h" },
		{ "ToolTip", "Radius of cone which bullets can spread. In degrees (90 degs will make a right angle cone)" },
		{ "UIMax", "360" },
		{ "UIMin", "0" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_bulletSpread = { "bulletSpread", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGATA_BulletTrace, bulletSpread), METADATA_PARAMS(Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_bulletSpread_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_bulletSpread_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_numberOfBullets_MetaData[] = {
		{ "Category", "Bullet Config" },
		{ "Comment", "/** Number of line traces to perform, above 1 would be considered a shotgun */" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_BulletTrace.h" },
		{ "ToolTip", "Number of line traces to perform, above 1 would be considered a shotgun" },
		{ "UIMin", "1" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_numberOfBullets = { "numberOfBullets", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGATA_BulletTrace, numberOfBullets), nullptr, METADATA_PARAMS(Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_numberOfBullets_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_numberOfBullets_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGATA_BulletTrace_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_bulletSpread,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_BulletTrace_Statics::NewProp_numberOfBullets,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGATA_BulletTrace_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGATA_BulletTrace>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGATA_BulletTrace_Statics::ClassParams = {
		&AGATA_BulletTrace::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGATA_BulletTrace_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_BulletTrace_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGATA_BulletTrace_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_BulletTrace_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGATA_BulletTrace()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGATA_BulletTrace_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGATA_BulletTrace, 1527540333);
	template<> SONICSIEGE_API UClass* StaticClass<AGATA_BulletTrace>()
	{
		return AGATA_BulletTrace::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGATA_BulletTrace(Z_Construct_UClass_AGATA_BulletTrace, &AGATA_BulletTrace::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AGATA_BulletTrace"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGATA_BulletTrace);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
