// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBAA_GameplayTagAddedRemoved() {}
// Cross Module References
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_GameplayTagAddedRemoved();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTagContainer();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics
	{
		struct _Script_SonicSiege_eventOnGameplayTagAddedRemoved_Parms
		{
			FGameplayTag Tag;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Tag;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::NewProp_Tag = { "Tag", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnGameplayTagAddedRemoved_Parms, Tag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::NewProp_Tag,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "OnGameplayTagAddedRemoved__DelegateSignature", nullptr, nullptr, sizeof(_Script_SonicSiege_eventOnGameplayTagAddedRemoved_Parms), Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UBAA_GameplayTagAddedRemoved::execEndTask)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndTask();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBAA_GameplayTagAddedRemoved::execListenForGameplayTagAddedOrRemoved)
	{
		P_GET_OBJECT(UAbilitySystemComponent,Z_Param_AbilitySystemComponent);
		P_GET_STRUCT(FGameplayTagContainer,Z_Param_Tags);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBAA_GameplayTagAddedRemoved**)Z_Param__Result=UBAA_GameplayTagAddedRemoved::ListenForGameplayTagAddedOrRemoved(Z_Param_AbilitySystemComponent,Z_Param_Tags);
		P_NATIVE_END;
	}
	void UBAA_GameplayTagAddedRemoved::StaticRegisterNativesUBAA_GameplayTagAddedRemoved()
	{
		UClass* Class = UBAA_GameplayTagAddedRemoved::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EndTask", &UBAA_GameplayTagAddedRemoved::execEndTask },
			{ "ListenForGameplayTagAddedOrRemoved", &UBAA_GameplayTagAddedRemoved::execListenForGameplayTagAddedOrRemoved },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/**\n\x09 * You must call this function manually when you want the AsyncTask to end.\n\x09 * For UMG Widgets, you would call it in the Widget's Destruct event.\n\x09 */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
		{ "ToolTip", "You must call this function manually when you want the AsyncTask to end.\nFor UMG Widgets, you would call it in the Widget's Destruct event." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_GameplayTagAddedRemoved, nullptr, "EndTask", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics
	{
		struct BAA_GameplayTagAddedRemoved_eventListenForGameplayTagAddedOrRemoved_Parms
		{
			UAbilitySystemComponent* AbilitySystemComponent;
			FGameplayTagContainer Tags;
			UBAA_GameplayTagAddedRemoved* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Tags;
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_GameplayTagAddedRemoved_eventListenForGameplayTagAddedOrRemoved_Parms, ReturnValue), Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_Tags = { "Tags", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_GameplayTagAddedRemoved_eventListenForGameplayTagAddedOrRemoved_Parms, Tags), Z_Construct_UScriptStruct_FGameplayTagContainer, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_AbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_GameplayTagAddedRemoved_eventListenForGameplayTagAddedOrRemoved_Parms, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_AbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_AbilitySystemComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_Tags,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::NewProp_AbilitySystemComponent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Comment", "/** Listens for FGameplayTags added and removed. */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
		{ "ToolTip", "Listens for FGameplayTags added and removed." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_GameplayTagAddedRemoved, nullptr, "ListenForGameplayTagAddedOrRemoved", nullptr, nullptr, sizeof(BAA_GameplayTagAddedRemoved_eventListenForGameplayTagAddedOrRemoved_Parms), Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_NoRegister()
	{
		return UBAA_GameplayTagAddedRemoved::StaticClass();
	}
	struct Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnTagRemoved_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTagRemoved;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnTagAdded_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnTagAdded;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_EndTask, "EndTask" }, // 49637761
		{ &Z_Construct_UFunction_UBAA_GameplayTagAddedRemoved_ListenForGameplayTagAddedOrRemoved, "ListenForGameplayTagAddedOrRemoved" }, // 2682534156
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Blueprint node to automatically register a listener for FGameplayTags added and removed.\n * Useful to use in Blueprint/UMG.\n */" },
		{ "ExposedAsyncProxy", "AsyncTask" },
		{ "IncludePath", "AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
		{ "ToolTip", "Blueprint node to automatically register a listener for FGameplayTags added and removed.\nUseful to use in Blueprint/UMG." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_ASC_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_ASC = { "ASC", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_GameplayTagAddedRemoved, ASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_ASC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_ASC_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagRemoved_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagRemoved = { "OnTagRemoved", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_GameplayTagAddedRemoved, OnTagRemoved), Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagRemoved_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagRemoved_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagAdded_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_GameplayTagAddedRemoved.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagAdded = { "OnTagAdded", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_GameplayTagAddedRemoved, OnTagAdded), Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagAdded_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagAdded_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_ASC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagRemoved,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::NewProp_OnTagAdded,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBAA_GameplayTagAddedRemoved>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::ClassParams = {
		&UBAA_GameplayTagAddedRemoved::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBAA_GameplayTagAddedRemoved()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBAA_GameplayTagAddedRemoved, 2043058447);
	template<> SONICSIEGE_API UClass* StaticClass<UBAA_GameplayTagAddedRemoved>()
	{
		return UBAA_GameplayTagAddedRemoved::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBAA_GameplayTagAddedRemoved(Z_Construct_UClass_UBAA_GameplayTagAddedRemoved, &UBAA_GameplayTagAddedRemoved::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UBAA_GameplayTagAddedRemoved"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBAA_GameplayTagAddedRemoved);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
