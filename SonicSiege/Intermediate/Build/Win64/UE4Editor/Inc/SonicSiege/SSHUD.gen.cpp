// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/UI/SSHUD.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSHUD() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSHUD_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSHUD();
	ENGINE_API UClass* Z_Construct_UClass_AHUD();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void ASSHUD::StaticRegisterNativesASSHUD()
	{
	}
	UClass* Z_Construct_UClass_ASSHUD_NoRegister()
	{
		return ASSHUD::StaticClass();
	}
	struct Z_Construct_UClass_ASSHUD_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASSHUD_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AHUD,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSHUD_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This class is being treated as a place to manage UUserWidgets (creating or adding and removing them from viewport)\n */" },
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "UI/SSHUD.h" },
		{ "ModuleRelativePath", "Public/UI/SSHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
		{ "ToolTip", "This class is being treated as a place to manage UUserWidgets (creating or adding and removing them from viewport)" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASSHUD_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASSHUD>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASSHUD_Statics::ClassParams = {
		&ASSHUD::StaticClass,
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
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASSHUD_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASSHUD_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASSHUD()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASSHUD_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASSHUD, 1752976497);
	template<> SONICSIEGE_API UClass* StaticClass<ASSHUD>()
	{
		return ASSHUD::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASSHUD(Z_Construct_UClass_ASSHUD, &ASSHUD::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASSHUD"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASSHUD);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
