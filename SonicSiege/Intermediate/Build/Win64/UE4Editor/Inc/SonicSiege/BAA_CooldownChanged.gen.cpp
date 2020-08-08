// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBAA_CooldownChanged() {}
// Cross Module References
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_CooldownChanged_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_CooldownChanged();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTagContainer();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics
	{
		struct _Script_SonicSiege_eventOnCooldownChanged_Parms
		{
			FGameplayTag CooldownTag;
			float TimeRemaining;
			float Duration;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Duration;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeRemaining;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CooldownTag;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnCooldownChanged_Parms, Duration), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_TimeRemaining = { "TimeRemaining", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnCooldownChanged_Parms, TimeRemaining), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_CooldownTag = { "CooldownTag", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnCooldownChanged_Parms, CooldownTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_Duration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_TimeRemaining,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::NewProp_CooldownTag,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "OnCooldownChanged__DelegateSignature", nullptr, nullptr, sizeof(_Script_SonicSiege_eventOnCooldownChanged_Parms), Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UBAA_CooldownChanged::execEndTask)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndTask();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBAA_CooldownChanged::execListenForCooldownChange)
	{
		P_GET_OBJECT(UAbilitySystemComponent,Z_Param_AbilitySystemComponent);
		P_GET_STRUCT(FGameplayTagContainer,Z_Param_CooldownTags);
		P_GET_UBOOL(Z_Param_UseServerCooldown);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBAA_CooldownChanged**)Z_Param__Result=UBAA_CooldownChanged::ListenForCooldownChange(Z_Param_AbilitySystemComponent,Z_Param_CooldownTags,Z_Param_UseServerCooldown);
		P_NATIVE_END;
	}
	void UBAA_CooldownChanged::StaticRegisterNativesUBAA_CooldownChanged()
	{
		UClass* Class = UBAA_CooldownChanged::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EndTask", &UBAA_CooldownChanged::execEndTask },
			{ "ListenForCooldownChange", &UBAA_CooldownChanged::execListenForCooldownChange },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/**\n\x09 * You must call this function manually when you want the AsyncTask to end.\n\x09 * For UMG Widgets, you would call it in the Widget's Destruct event.\n\x09 */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
		{ "ToolTip", "You must call this function manually when you want the AsyncTask to end.\nFor UMG Widgets, you would call it in the Widget's Destruct event." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_CooldownChanged, nullptr, "EndTask", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_CooldownChanged_EndTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_CooldownChanged_EndTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics
	{
		struct BAA_CooldownChanged_eventListenForCooldownChange_Parms
		{
			UAbilitySystemComponent* AbilitySystemComponent;
			FGameplayTagContainer CooldownTags;
			bool UseServerCooldown;
			UBAA_CooldownChanged* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static void NewProp_UseServerCooldown_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_UseServerCooldown;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CooldownTags;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AbilitySystemComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_CooldownChanged_eventListenForCooldownChange_Parms, ReturnValue), Z_Construct_UClass_UBAA_CooldownChanged_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_UseServerCooldown_SetBit(void* Obj)
	{
		((BAA_CooldownChanged_eventListenForCooldownChange_Parms*)Obj)->UseServerCooldown = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_UseServerCooldown = { "UseServerCooldown", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(BAA_CooldownChanged_eventListenForCooldownChange_Parms), &Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_UseServerCooldown_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_CooldownTags = { "CooldownTags", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_CooldownChanged_eventListenForCooldownChange_Parms, CooldownTags), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_AbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_CooldownChanged_eventListenForCooldownChange_Parms, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_AbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_AbilitySystemComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_UseServerCooldown,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_CooldownTags,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::NewProp_AbilitySystemComponent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Comment", "/**\n\x09 * Listens for changes (Begin and End) to cooldown GameplayEffects based on the cooldown tag.\n\x09 * UseServerCooldown determines if the Sever's cooldown is returned in addition to the local predicted cooldown.\n\x09 * If using ServerCooldown, TimeRemaining and Duration will return -1 to signal local predicted cooldown has begun.\n\x09 */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
		{ "ToolTip", "Listens for changes (Begin and End) to cooldown GameplayEffects based on the cooldown tag.\nUseServerCooldown determines if the Sever's cooldown is returned in addition to the local predicted cooldown.\nIf using ServerCooldown, TimeRemaining and Duration will return -1 to signal local predicted cooldown has begun." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_CooldownChanged, nullptr, "ListenForCooldownChange", nullptr, nullptr, sizeof(BAA_CooldownChanged_eventListenForCooldownChange_Parms), Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBAA_CooldownChanged_NoRegister()
	{
		return UBAA_CooldownChanged::StaticClass();
	}
	struct Z_Construct_UClass_UBAA_CooldownChanged_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ASC_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ASC;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCooldownEnd_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCooldownEnd;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnCooldownBegin_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCooldownBegin;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBAA_CooldownChanged_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBAA_CooldownChanged_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBAA_CooldownChanged_EndTask, "EndTask" }, // 1562685180
		{ &Z_Construct_UFunction_UBAA_CooldownChanged_ListenForCooldownChange, "ListenForCooldownChange" }, // 184974706
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_CooldownChanged_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Blueprint node to automatically register a listener for changes (Begin and End) to an array of Cooldown tags.\n * Useful to use in UI.\n */" },
		{ "ExposedAsyncProxy", "AsyncTask" },
		{ "IncludePath", "AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
		{ "ToolTip", "Blueprint node to automatically register a listener for changes (Begin and End) to an array of Cooldown tags.\nUseful to use in UI." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_ASC_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_ASC = { "ASC", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_CooldownChanged, ASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_ASC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_ASC_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownEnd_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownEnd = { "OnCooldownEnd", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_CooldownChanged, OnCooldownEnd), Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownEnd_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownEnd_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownBegin_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_CooldownChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownBegin = { "OnCooldownBegin", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_CooldownChanged, OnCooldownBegin), Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownBegin_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownBegin_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBAA_CooldownChanged_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_ASC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownEnd,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_CooldownChanged_Statics::NewProp_OnCooldownBegin,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBAA_CooldownChanged_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBAA_CooldownChanged>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBAA_CooldownChanged_Statics::ClassParams = {
		&UBAA_CooldownChanged::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBAA_CooldownChanged_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_CooldownChanged_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBAA_CooldownChanged_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_CooldownChanged_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBAA_CooldownChanged()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBAA_CooldownChanged_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBAA_CooldownChanged, 1224156047);
	template<> SONICSIEGE_API UClass* StaticClass<UBAA_CooldownChanged>()
	{
		return UBAA_CooldownChanged::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBAA_CooldownChanged(Z_Construct_UClass_UBAA_CooldownChanged, &UBAA_CooldownChanged::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UBAA_CooldownChanged"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBAA_CooldownChanged);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
