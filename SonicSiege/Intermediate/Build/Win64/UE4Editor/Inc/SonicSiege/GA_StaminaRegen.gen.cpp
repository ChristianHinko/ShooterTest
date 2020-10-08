// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/PassiveAbilities/GA_StaminaRegen.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_StaminaRegen() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_StaminaRegen_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_StaminaRegen();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UGA_StaminaRegen::execOnTimerTick)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnTimerTick();
		P_NATIVE_END;
	}
	void UGA_StaminaRegen::StaticRegisterNativesUGA_StaminaRegen()
	{
		UClass* Class = UGA_StaminaRegen::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnTimerTick", &UGA_StaminaRegen::execOnTimerTick },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/PassiveAbilities/GA_StaminaRegen.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_StaminaRegen, nullptr, "OnTimerTick", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_StaminaRegen_NoRegister()
	{
		return UGA_StaminaRegen::StaticClass();
	}
	struct Z_Construct_UClass_UGA_StaminaRegen_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GASCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GASCharacter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StaminaGainEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_StaminaGainEffectTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_StaminaRegen_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_StaminaRegen_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_StaminaRegen_OnTimerTick, "OnTimerTick" }, // 1167640495
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_StaminaRegen_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/PassiveAbilities/GA_StaminaRegen.h" },
		{ "ModuleRelativePath", "Public/Character/PassiveAbilities/GA_StaminaRegen.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_CharacterAttributeSet_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/PassiveAbilities/GA_StaminaRegen.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_CharacterAttributeSet = { "CharacterAttributeSet", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_StaminaRegen, CharacterAttributeSet), Z_Construct_UClass_UAS_Character_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_CharacterAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_CharacterAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_GASCharacter_MetaData[] = {
		{ "Comment", "// asset manager we need you D:\n" },
		{ "ModuleRelativePath", "Public/Character/PassiveAbilities/GA_StaminaRegen.h" },
		{ "ToolTip", "asset manager we need you D:" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_GASCharacter = { "GASCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_StaminaRegen, GASCharacter), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_GASCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_GASCharacter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_StaminaGainEffectTSub_MetaData[] = {
		{ "Category", "GA_StaminaRegen" },
		{ "ModuleRelativePath", "Public/Character/PassiveAbilities/GA_StaminaRegen.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_StaminaGainEffectTSub = { "StaminaGainEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_StaminaRegen, StaminaGainEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_StaminaGainEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_StaminaGainEffectTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_StaminaRegen_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_CharacterAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_GASCharacter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_StaminaRegen_Statics::NewProp_StaminaGainEffectTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_StaminaRegen_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_StaminaRegen>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_StaminaRegen_Statics::ClassParams = {
		&UGA_StaminaRegen::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGA_StaminaRegen_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_StaminaRegen_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_StaminaRegen_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_StaminaRegen_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_StaminaRegen()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_StaminaRegen_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_StaminaRegen, 2491375009);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_StaminaRegen>()
	{
		return UGA_StaminaRegen::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_StaminaRegen(Z_Construct_UClass_UGA_StaminaRegen, &UGA_StaminaRegen::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_StaminaRegen"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_StaminaRegen);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
