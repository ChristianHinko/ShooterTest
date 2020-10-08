// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/Interact/GA_CharacterAutoInteract.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterAutoInteract() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterAutoInteract_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterAutoInteract();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASiegeCharacter_NoRegister();
// End Cross Module References
	void UGA_CharacterAutoInteract::StaticRegisterNativesUGA_CharacterAutoInteract()
	{
	}
	UClass* Z_Construct_UClass_UGA_CharacterAutoInteract_NoRegister()
	{
		return UGA_CharacterAutoInteract::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterAutoInteract_Statics
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
	UObject* (*const Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/Abilities/Interact/GA_CharacterAutoInteract.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterAutoInteract.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::NewProp_SiegeCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterAutoInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::NewProp_SiegeCharacter = { "SiegeCharacter", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterAutoInteract, SiegeCharacter), Z_Construct_UClass_ASiegeCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::NewProp_SiegeCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::NewProp_SiegeCharacter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::NewProp_SiegeCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterAutoInteract>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::ClassParams = {
		&UGA_CharacterAutoInteract::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterAutoInteract()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterAutoInteract_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterAutoInteract, 2269359516);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterAutoInteract>()
	{
		return UGA_CharacterAutoInteract::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterAutoInteract(Z_Construct_UClass_UGA_CharacterAutoInteract, &UGA_CharacterAutoInteract::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterAutoInteract"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterAutoInteract);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
