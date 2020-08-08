// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Characters/Sonic.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSonic() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_ASonic_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASonic();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
// End Cross Module References
	void ASonic::StaticRegisterNativesASonic()
	{
	}
	UClass* Z_Construct_UClass_ASonic_NoRegister()
	{
		return ASonic::StaticClass();
	}
	struct Z_Construct_UClass_ASonic_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FaceMesh_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_FaceMesh;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASonic_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAbilitySystemCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASonic_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/Characters/Sonic.h" },
		{ "ModuleRelativePath", "Public/Character/Characters/Sonic.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASonic_Statics::NewProp_FaceMesh_MetaData[] = {
		{ "Category", "Character" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/Characters/Sonic.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASonic_Statics::NewProp_FaceMesh = { "FaceMesh", nullptr, (EPropertyFlags)0x00200800000a0009, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASonic, FaceMesh), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASonic_Statics::NewProp_FaceMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASonic_Statics::NewProp_FaceMesh_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASonic_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASonic_Statics::NewProp_FaceMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASonic_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASonic>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASonic_Statics::ClassParams = {
		&ASonic::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASonic_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASonic_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASonic_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASonic_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASonic()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASonic_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASonic, 3877453161);
	template<> SONICSIEGE_API UClass* StaticClass<ASonic>()
	{
		return ASonic::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASonic(Z_Construct_UClass_ASonic, &ASonic::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASonic"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASonic);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
