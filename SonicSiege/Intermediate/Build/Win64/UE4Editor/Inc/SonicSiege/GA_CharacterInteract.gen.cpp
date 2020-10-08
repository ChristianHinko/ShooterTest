// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/Interact/GA_CharacterInteract.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterInteract() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterInteract_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterInteract();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASiegeCharacter_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
// End Cross Module References
	void UGA_CharacterInteract::StaticRegisterNativesUGA_CharacterInteract()
	{
	}
	UClass* Z_Construct_UClass_UGA_CharacterInteract_NoRegister()
	{
		return UGA_CharacterInteract::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterInteract_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SiegeCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SiegeCharacter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_InteractEffectTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_CharacterInteract_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterInteract_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/Abilities/Interact/GA_CharacterInteract.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterInteract.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_SiegeCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_SiegeCharacter = { "SiegeCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterInteract, SiegeCharacter), Z_Construct_UClass_ASiegeCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_SiegeCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_SiegeCharacter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_InteractEffectTSub_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_InteractEffectTSub = { "InteractEffectTSub", nullptr, (EPropertyFlags)0x0024080000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterInteract, InteractEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_InteractEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_InteractEffectTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_CharacterInteract_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_SiegeCharacter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterInteract_Statics::NewProp_InteractEffectTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterInteract_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterInteract>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterInteract_Statics::ClassParams = {
		&UGA_CharacterInteract::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGA_CharacterInteract_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterInteract_Statics::PropPointers),
		0,
		0x001000A1u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterInteract_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterInteract_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterInteract()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterInteract_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterInteract, 3683274280);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterInteract>()
	{
		return UGA_CharacterInteract::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterInteract(Z_Construct_UClass_UGA_CharacterInteract, &UGA_CharacterInteract::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterInteract"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterInteract);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
