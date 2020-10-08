// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Pawn/SSPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSPawn() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPawn_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPawn();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void ASSPawn::StaticRegisterNativesASSPawn()
	{
	}
	UClass* Z_Construct_UClass_ASSPawn_NoRegister()
	{
		return ASSPawn::StaticClass();
	}
	struct Z_Construct_UClass_ASSPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASSPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSPawn_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base pawn class for all pawns to inherit from (besides pawns which inherit from the base pawn)\n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Pawn/SSPawn.h" },
		{ "ModuleRelativePath", "Public/Pawn/SSPawn.h" },
		{ "ToolTip", "Base pawn class for all pawns to inherit from (besides pawns which inherit from the base pawn)" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASSPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASSPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASSPawn_Statics::ClassParams = {
		&ASSPawn::StaticClass,
		"Game",
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
		METADATA_PARAMS(Z_Construct_UClass_ASSPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASSPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASSPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASSPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASSPawn, 3381990973);
	template<> SONICSIEGE_API UClass* StaticClass<ASSPawn>()
	{
		return ASSPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASSPawn(Z_Construct_UClass_ASSPawn, &ASSPawn::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASSPawn"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASSPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
