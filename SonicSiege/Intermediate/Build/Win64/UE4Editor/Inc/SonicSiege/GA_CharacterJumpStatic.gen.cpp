// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/GA_CharacterJumpStatic.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterJumpStatic() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterJumpStatic_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterJumpStatic();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void UGA_CharacterJumpStatic::StaticRegisterNativesUGA_CharacterJumpStatic()
	{
	}
	UClass* Z_Construct_UClass_UGA_CharacterJumpStatic_NoRegister()
	{
		return UGA_CharacterJumpStatic::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterJumpStatic_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This serves as a good demonstration as to how you should go about making Non-Instanced abilities\n *\n * Non-Instanced Abilities must not change member variables or bind to Delegates during its execution of the Ability.\n * The Ability also cannot replicate variables or handle RPCs. Non-Instanced should be used only for Abilities that require no internal variable storage.\n *\n * Stuff were still not sure of yet:\n *\x09\x09- We sorta made this from Epic's and Dan's Non-Instanced jump ability and added our own spin to it. Something to be aware of is in Dan's project the jumping got corrections for some reason when\n *\x09\x09\x09shooting the machine gun or the shot gun but not with the rocket launcher. Pretty sure it's just something weird with his project but be on the lookout to make sure nothing weird happens.\n *\x09\x09- It seams like EndAbility doesn't need to be called in order to fire it again and again. Thats weird. Just call it on client and server anyways as always because thats what your supposed to do.\n *\x09\x09- Another thing thats weird it that for Non-Instanced abilities, EGameplayAbilityActivationMode inside ActivationInfo is set to Confirmed on both the client and server, even thought Confirmed means your on the client.\n */" },
		{ "IncludePath", "Character/Abilities/GA_CharacterJumpStatic.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterJumpStatic.h" },
		{ "ToolTip", "This serves as a good demonstration as to how you should go about making Non-Instanced abilities\n\nNon-Instanced Abilities must not change member variables or bind to Delegates during its execution of the Ability.\nThe Ability also cannot replicate variables or handle RPCs. Non-Instanced should be used only for Abilities that require no internal variable storage.\n\nStuff were still not sure of yet:\n            - We sorta made this from Epic's and Dan's Non-Instanced jump ability and added our own spin to it. Something to be aware of is in Dan's project the jumping got corrections for some reason when\n                    shooting the machine gun or the shot gun but not with the rocket launcher. Pretty sure it's just something weird with his project but be on the lookout to make sure nothing weird happens.\n            - It seams like EndAbility doesn't need to be called in order to fire it again and again. Thats weird. Just call it on client and server anyways as always because thats what your supposed to do.\n            - Another thing thats weird it that for Non-Instanced abilities, EGameplayAbilityActivationMode inside ActivationInfo is set to Confirmed on both the client and server, even thought Confirmed means your on the client." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterJumpStatic>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::ClassParams = {
		&UGA_CharacterJumpStatic::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterJumpStatic()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterJumpStatic_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterJumpStatic, 569476488);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterJumpStatic>()
	{
		return UGA_CharacterJumpStatic::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterJumpStatic(Z_Construct_UClass_UGA_CharacterJumpStatic, &UGA_CharacterJumpStatic::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterJumpStatic"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterJumpStatic);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
