// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/GA_CharacterJump.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterJump() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterJump_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterJump();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UGA_CharacterJump::execOnRelease)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRelease(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	void UGA_CharacterJump::StaticRegisterNativesUGA_CharacterJump()
	{
		UClass* Class = UGA_CharacterJump::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRelease", &UGA_CharacterJump::execOnRelease },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics
	{
		struct GA_CharacterJump_eventOnRelease_Parms
		{
			float TimeHeld;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeHeld;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterJump_eventOnRelease_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//END UGameplayAbility Interface\n" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterJump.h" },
		{ "ToolTip", "END UGameplayAbility Interface" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterJump, nullptr, "OnRelease", nullptr, nullptr, sizeof(GA_CharacterJump_eventOnRelease_Parms), Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterJump_OnRelease()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterJump_OnRelease_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_CharacterJump_NoRegister()
	{
		return UGA_CharacterJump::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterJump_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_JumpEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_JumpEffectTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_CharacterJump_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_CharacterJump_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_CharacterJump_OnRelease, "OnRelease" }, // 1568405910
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterJump_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This is a nice minimal implementation of the CMC jumping into the ability system\n */" },
		{ "IncludePath", "Character/Abilities/GA_CharacterJump.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterJump.h" },
		{ "ToolTip", "This is a nice minimal implementation of the CMC jumping into the ability system" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterJump_Statics::NewProp_JumpEffectTSub_MetaData[] = {
		{ "Category", "GA_CharacterJump" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterJump.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_CharacterJump_Statics::NewProp_JumpEffectTSub = { "JumpEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterJump, JumpEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterJump_Statics::NewProp_JumpEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterJump_Statics::NewProp_JumpEffectTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_CharacterJump_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterJump_Statics::NewProp_JumpEffectTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterJump_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterJump>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterJump_Statics::ClassParams = {
		&UGA_CharacterJump::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGA_CharacterJump_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterJump_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterJump_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterJump_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterJump()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterJump_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterJump, 2537035566);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterJump>()
	{
		return UGA_CharacterJump::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterJump(Z_Construct_UClass_UGA_CharacterJump, &UGA_CharacterJump::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterJump"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterJump);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
