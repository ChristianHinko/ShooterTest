// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/AbilityTasks/AT_RepeatAction.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAT_RepeatAction() {}
// Cross Module References
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_RepeatAction_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_RepeatAction();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_RepeatAction.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "RepeatActionDelegate__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UAT_RepeatAction::execRepeatAction)
	{
		P_GET_OBJECT(UGameplayAbility,Z_Param_OwningAbility);
		P_GET_PROPERTY(FFloatProperty,Z_Param_DelayBetweenRepeats);
		P_GET_UBOOL(Z_Param_ShouldLoop);
		P_GET_PROPERTY(FFloatProperty,Z_Param_FirstDelay);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UAT_RepeatAction**)Z_Param__Result=UAT_RepeatAction::RepeatAction(Z_Param_OwningAbility,Z_Param_DelayBetweenRepeats,Z_Param_ShouldLoop,Z_Param_FirstDelay);
		P_NATIVE_END;
	}
	void UAT_RepeatAction::StaticRegisterNativesUAT_RepeatAction()
	{
		UClass* Class = UAT_RepeatAction::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "RepeatAction", &UAT_RepeatAction::execRepeatAction },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics
	{
		struct AT_RepeatAction_eventRepeatAction_Parms
		{
			UGameplayAbility* OwningAbility;
			float DelayBetweenRepeats;
			bool ShouldLoop;
			float FirstDelay;
			UAT_RepeatAction* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_FirstDelay;
		static void NewProp_ShouldLoop_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ShouldLoop;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DelayBetweenRepeats;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwningAbility;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_RepeatAction_eventRepeatAction_Parms, ReturnValue), Z_Construct_UClass_UAT_RepeatAction_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_FirstDelay = { "FirstDelay", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_RepeatAction_eventRepeatAction_Parms, FirstDelay), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ShouldLoop_SetBit(void* Obj)
	{
		((AT_RepeatAction_eventRepeatAction_Parms*)Obj)->ShouldLoop = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ShouldLoop = { "ShouldLoop", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AT_RepeatAction_eventRepeatAction_Parms), &Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ShouldLoop_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_DelayBetweenRepeats = { "DelayBetweenRepeats", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_RepeatAction_eventRepeatAction_Parms, DelayBetweenRepeats), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_OwningAbility = { "OwningAbility", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_RepeatAction_eventRepeatAction_Parms, OwningAbility), Z_Construct_UClass_UGameplayAbility_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_FirstDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_ShouldLoop,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_DelayBetweenRepeats,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::NewProp_OwningAbility,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "TRUE" },
		{ "Category", "Ability|Tasks" },
		{ "Comment", "/** Start a task that repeats an action or set of actions. */" },
		{ "CPP_Default_FirstDelay", "0.000000" },
		{ "DefaultToSelf", "OwningAbility" },
		{ "DisplayName", "Repeat Action (Timer)" },
		{ "HidePin", "OwningAbility" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_RepeatAction.h" },
		{ "ToolTip", "Start a task that repeats an action or set of actions." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAT_RepeatAction, nullptr, "RepeatAction", nullptr, nullptr, sizeof(AT_RepeatAction_eventRepeatAction_Parms), Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAT_RepeatAction_RepeatAction()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAT_RepeatAction_RepeatAction_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAT_RepeatAction_NoRegister()
	{
		return UAT_RepeatAction::StaticClass();
	}
	struct Z_Construct_UClass_UAT_RepeatAction_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnPerformAction_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnPerformAction;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAT_RepeatAction_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAbilityTask,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAT_RepeatAction_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAT_RepeatAction_RepeatAction, "RepeatAction" }, // 3796763144
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_RepeatAction_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AbilitySystem/AbilityTasks/AT_RepeatAction.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_RepeatAction.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_RepeatAction_Statics::NewProp_OnPerformAction_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_RepeatAction.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAT_RepeatAction_Statics::NewProp_OnPerformAction = { "OnPerformAction", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAT_RepeatAction, OnPerformAction), Z_Construct_UDelegateFunction_SonicSiege_RepeatActionDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAT_RepeatAction_Statics::NewProp_OnPerformAction_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_RepeatAction_Statics::NewProp_OnPerformAction_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAT_RepeatAction_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAT_RepeatAction_Statics::NewProp_OnPerformAction,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAT_RepeatAction_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAT_RepeatAction>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAT_RepeatAction_Statics::ClassParams = {
		&UAT_RepeatAction::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAT_RepeatAction_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAT_RepeatAction_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAT_RepeatAction_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_RepeatAction_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAT_RepeatAction()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAT_RepeatAction_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAT_RepeatAction, 3858285543);
	template<> SONICSIEGE_API UClass* StaticClass<UAT_RepeatAction>()
	{
		return UAT_RepeatAction::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAT_RepeatAction(Z_Construct_UClass_UAT_RepeatAction, &UAT_RepeatAction::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAT_RepeatAction"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAT_RepeatAction);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
