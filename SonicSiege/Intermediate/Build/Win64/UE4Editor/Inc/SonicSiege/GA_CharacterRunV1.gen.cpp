// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/GA_CharacterRunV1.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterRunV1() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterRunV1_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterRunV1();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UGA_CharacterRunV1::execOnRelease)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRelease(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterRunV1::execOnTimerTick)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnTimerTick();
		P_NATIVE_END;
	}
	void UGA_CharacterRunV1::StaticRegisterNativesUGA_CharacterRunV1()
	{
		UClass* Class = UGA_CharacterRunV1::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRelease", &UGA_CharacterRunV1::execOnRelease },
			{ "OnTimerTick", &UGA_CharacterRunV1::execOnTimerTick },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics
	{
		struct GA_CharacterRunV1_eventOnRelease_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterRunV1_eventOnRelease_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterRunV1, nullptr, "OnRelease", nullptr, nullptr, sizeof(GA_CharacterRunV1_eventOnRelease_Parms), Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterRunV1, nullptr, "OnTimerTick", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_CharacterRunV1_NoRegister()
	{
		return UGA_CharacterRunV1::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterRunV1_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GASCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GASCharacter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RunningEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_RunningEffectTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DrainStaminaFromRunEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_DrainStaminaFromRunEffectTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_CharacterRunV1_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_CharacterRunV1_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_CharacterRunV1_OnRelease, "OnRelease" }, // 931338089
		{ &Z_Construct_UFunction_UGA_CharacterRunV1_OnTimerTick, "OnTimerTick" }, // 884128164
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterRunV1_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This serves as a good demonstration as to how you should go about making Instanced-per-Actor abilities. Or any kind really\n * Client and server must both call EndAbility(). NOTE: If you want to use bReplicateEndAbility in EndAbility() the client's \n * ability must already be confirmed by the server. This means replicating EndAbility() to the server could fail (and often does).\n * This is a nice minimal implementation of the CMC running into the ability system.\n */" },
		{ "IncludePath", "Character/Abilities/GA_CharacterRunV1.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
		{ "ToolTip", "This serves as a good demonstration as to how you should go about making Instanced-per-Actor abilities. Or any kind really\nClient and server must both call EndAbility(). NOTE: If you want to use bReplicateEndAbility in EndAbility() the client's\nability must already be confirmed by the server. This means replicating EndAbility() to the server could fail (and often does).\nThis is a nice minimal implementation of the CMC running into the ability system." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_GASCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_GASCharacter = { "GASCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterRunV1, GASCharacter), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_GASCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_GASCharacter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_RunningEffectTSub_MetaData[] = {
		{ "Category", "GA_CharacterRunV1" },
		{ "Comment", "// asset manager we need you D:\n" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
		{ "ToolTip", "asset manager we need you D:" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_RunningEffectTSub = { "RunningEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterRunV1, RunningEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_RunningEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_RunningEffectTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_DrainStaminaFromRunEffectTSub_MetaData[] = {
		{ "Category", "GA_CharacterRunV1" },
		{ "ModuleRelativePath", "Public/Character/Abilities/GA_CharacterRunV1.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_DrainStaminaFromRunEffectTSub = { "DrainStaminaFromRunEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_CharacterRunV1, DrainStaminaFromRunEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_DrainStaminaFromRunEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_DrainStaminaFromRunEffectTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_CharacterRunV1_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_GASCharacter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_RunningEffectTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_CharacterRunV1_Statics::NewProp_DrainStaminaFromRunEffectTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterRunV1_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterRunV1>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterRunV1_Statics::ClassParams = {
		&UGA_CharacterRunV1::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGA_CharacterRunV1_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterRunV1_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterRunV1_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterRunV1_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterRunV1()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterRunV1_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterRunV1, 3992160606);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterRunV1>()
	{
		return UGA_CharacterRunV1::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterRunV1(Z_Construct_UClass_UGA_CharacterRunV1, &UGA_CharacterRunV1::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterRunV1"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterRunV1);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
