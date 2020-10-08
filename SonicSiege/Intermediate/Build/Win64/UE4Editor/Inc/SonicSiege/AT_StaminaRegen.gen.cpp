// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/AbilityTasks/AT_StaminaRegen.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAT_StaminaRegen() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_StaminaRegen_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_StaminaRegen();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UAT_StaminaRegen::execAT_StaminaRegen)
	{
		P_GET_OBJECT(UGameplayAbility,Z_Param_OwningAbility);
		P_GET_PROPERTY(FNameProperty,Z_Param_TaskInstanceName);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UAT_StaminaRegen**)Z_Param__Result=UAT_StaminaRegen::AT_StaminaRegen(Z_Param_OwningAbility,Z_Param_TaskInstanceName);
		P_NATIVE_END;
	}
	void UAT_StaminaRegen::StaticRegisterNativesUAT_StaminaRegen()
	{
		UClass* Class = UAT_StaminaRegen::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AT_StaminaRegen", &UAT_StaminaRegen::execAT_StaminaRegen },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics
	{
		struct AT_StaminaRegen_eventAT_StaminaRegen_Parms
		{
			UGameplayAbility* OwningAbility;
			FName TaskInstanceName;
			UAT_StaminaRegen* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_TaskInstanceName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwningAbility;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_StaminaRegen_eventAT_StaminaRegen_Parms, ReturnValue), Z_Construct_UClass_UAT_StaminaRegen_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_TaskInstanceName = { "TaskInstanceName", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_StaminaRegen_eventAT_StaminaRegen_Parms, TaskInstanceName), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_OwningAbility = { "OwningAbility", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_StaminaRegen_eventAT_StaminaRegen_Parms, OwningAbility), Z_Construct_UClass_UGameplayAbility_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_TaskInstanceName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::NewProp_OwningAbility,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "TRUE" },
		{ "Category", "Ability|Tasks" },
		{ "DefaultToSelf", "OwningAbility" },
		{ "HidePin", "OwningAbility" },
		{ "ModuleRelativePath", "Public/Character/AbilityTasks/AT_StaminaRegen.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAT_StaminaRegen, nullptr, "AT_StaminaRegen", nullptr, nullptr, sizeof(AT_StaminaRegen_eventAT_StaminaRegen_Parms), Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAT_StaminaRegen_NoRegister()
	{
		return UAT_StaminaRegen::StaticClass();
	}
	struct Z_Construct_UClass_UAT_StaminaRegen_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAT_StaminaRegen_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAbilityTask,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAT_StaminaRegen_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAT_StaminaRegen_AT_StaminaRegen, "AT_StaminaRegen" }, // 1926934084
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_StaminaRegen_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/AbilityTasks/AT_StaminaRegen.h" },
		{ "ModuleRelativePath", "Public/Character/AbilityTasks/AT_StaminaRegen.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAT_StaminaRegen_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAT_StaminaRegen>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAT_StaminaRegen_Statics::ClassParams = {
		&UAT_StaminaRegen::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAT_StaminaRegen_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_StaminaRegen_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAT_StaminaRegen()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAT_StaminaRegen_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAT_StaminaRegen, 4128979003);
	template<> SONICSIEGE_API UClass* StaticClass<UAT_StaminaRegen>()
	{
		return UAT_StaminaRegen::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAT_StaminaRegen(Z_Construct_UClass_UAT_StaminaRegen, &UAT_StaminaRegen::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAT_StaminaRegen"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAT_StaminaRegen);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
