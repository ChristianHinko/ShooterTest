// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/Item/Weapon/Abilities/GA_Fire.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_Fire() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_Fire_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_Fire();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAbilityTargetDataHandle();
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_BulletTrace_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AWeapon_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UGA_Fire::execOnCancelled)
	{
		P_GET_STRUCT_REF(FGameplayAbilityTargetDataHandle,Z_Param_Out_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnCancelled(Z_Param_Out_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_Fire::execOnValidData)
	{
		P_GET_STRUCT_REF(FGameplayAbilityTargetDataHandle,Z_Param_Out_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnValidData(Z_Param_Out_Data);
		P_NATIVE_END;
	}
	void UGA_Fire::StaticRegisterNativesUGA_Fire()
	{
		UClass* Class = UGA_Fire::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnCancelled", &UGA_Fire::execOnCancelled },
			{ "OnValidData", &UGA_Fire::execOnValidData },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics
	{
		struct GA_Fire_eventOnCancelled_Parms
		{
			FGameplayAbilityTargetDataHandle Data;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_Fire_eventOnCancelled_Parms, Data), Z_Construct_UScriptStruct_FGameplayAbilityTargetDataHandle, METADATA_PARAMS(Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::NewProp_Data_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::NewProp_Data,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_Fire, nullptr, "OnCancelled", nullptr, nullptr, sizeof(GA_Fire_eventOnCancelled_Parms), Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_Fire_OnCancelled()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_Fire_OnCancelled_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_Fire_OnValidData_Statics
	{
		struct GA_Fire_eventOnValidData_Parms
		{
			FGameplayAbilityTargetDataHandle Data;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_Fire_eventOnValidData_Parms, Data), Z_Construct_UScriptStruct_FGameplayAbilityTargetDataHandle, METADATA_PARAMS(Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::NewProp_Data_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::NewProp_Data,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_Fire, nullptr, "OnValidData", nullptr, nullptr, sizeof(GA_Fire_eventOnValidData_Parms), Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_Fire_OnValidData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_Fire_OnValidData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_Fire_NoRegister()
	{
		return UGA_Fire::StaticClass();
	}
	struct Z_Construct_UClass_UGA_Fire_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BulletTraceTargetActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_BulletTraceTargetActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SourceWeapon_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SourceWeapon;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BulletHitEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_BulletHitEffectTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FireEffectTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_FireEffectTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_Fire_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_Fire_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_Fire_OnCancelled, "OnCancelled" }, // 4092021042
		{ &Z_Construct_UFunction_UGA_Fire_OnValidData, "OnValidData" }, // 2362736441
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_Fire_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Actor/Item/Weapon/Abilities/GA_Fire.h" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletTraceTargetActor_MetaData[] = {
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletTraceTargetActor = { "BulletTraceTargetActor", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_Fire, BulletTraceTargetActor), Z_Construct_UClass_AGATA_BulletTrace_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletTraceTargetActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletTraceTargetActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_Fire_Statics::NewProp_SourceWeapon_MetaData[] = {
		{ "Comment", "//END UGameplayAbility Interface\n" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
		{ "ToolTip", "END UGameplayAbility Interface" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGA_Fire_Statics::NewProp_SourceWeapon = { "SourceWeapon", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_Fire, SourceWeapon), Z_Construct_UClass_AWeapon_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UGA_Fire_Statics::NewProp_SourceWeapon_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::NewProp_SourceWeapon_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletHitEffectTSub_MetaData[] = {
		{ "Category", "Effects To Apply" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletHitEffectTSub = { "BulletHitEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_Fire, BulletHitEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletHitEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletHitEffectTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_Fire_Statics::NewProp_FireEffectTSub_MetaData[] = {
		{ "Category", "Effects To Apply" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_Fire.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_UGA_Fire_Statics::NewProp_FireEffectTSub = { "FireEffectTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UGA_Fire, FireEffectTSub), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UGA_Fire_Statics::NewProp_FireEffectTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::NewProp_FireEffectTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGA_Fire_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletTraceTargetActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_Fire_Statics::NewProp_SourceWeapon,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_Fire_Statics::NewProp_BulletHitEffectTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGA_Fire_Statics::NewProp_FireEffectTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_Fire_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_Fire>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_Fire_Statics::ClassParams = {
		&UGA_Fire::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGA_Fire_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGA_Fire_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_Fire_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_Fire()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_Fire_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_Fire, 3927808267);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_Fire>()
	{
		return UGA_Fire::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_Fire(Z_Construct_UClass_UGA_Fire, &UGA_Fire::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_Fire"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_Fire);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
