// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/AbilityTasks/AT_Ticker.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAT_Ticker() {}
// Cross Module References
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_Ticker_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAT_Ticker();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayAbility_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "DurationEnded__DelegateSignature", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics
	{
		struct _Script_SonicSiege_eventTickDelegate_Parms
		{
			float DeltaTime;
			float CurrentTime;
			float TimeRemaining;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeRemaining;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurrentTime;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_TimeRemaining = { "TimeRemaining", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventTickDelegate_Parms, TimeRemaining), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_CurrentTime = { "CurrentTime", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventTickDelegate_Parms, CurrentTime), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventTickDelegate_Parms, DeltaTime), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_TimeRemaining,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_CurrentTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::NewProp_DeltaTime,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "TickDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_SonicSiege_eventTickDelegate_Parms), Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UAT_Ticker::execTicker)
	{
		P_GET_OBJECT(UGameplayAbility,Z_Param_OwningAbility);
		P_GET_OBJECT(AAbilitySystemCharacter,Z_Param_GASCharactor);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Duration);
		P_GET_PROPERTY(FFloatProperty,Z_Param_Interval);
		P_GET_UBOOL(Z_Param_skipFirstTick);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UAT_Ticker**)Z_Param__Result=UAT_Ticker::Ticker(Z_Param_OwningAbility,Z_Param_GASCharactor,Z_Param_Duration,Z_Param_Interval,Z_Param_skipFirstTick);
		P_NATIVE_END;
	}
	void UAT_Ticker::StaticRegisterNativesUAT_Ticker()
	{
		UClass* Class = UAT_Ticker::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Ticker", &UAT_Ticker::execTicker },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAT_Ticker_Ticker_Statics
	{
		struct AT_Ticker_eventTicker_Parms
		{
			UGameplayAbility* OwningAbility;
			AAbilitySystemCharacter* GASCharactor;
			float Duration;
			float Interval;
			bool skipFirstTick;
			UAT_Ticker* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static void NewProp_skipFirstTick_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_skipFirstTick;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Interval;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Duration;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_GASCharactor;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwningAbility;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_Ticker_eventTicker_Parms, ReturnValue), Z_Construct_UClass_UAT_Ticker_NoRegister, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_skipFirstTick_SetBit(void* Obj)
	{
		((AT_Ticker_eventTicker_Parms*)Obj)->skipFirstTick = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_skipFirstTick = { "skipFirstTick", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AT_Ticker_eventTicker_Parms), &Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_skipFirstTick_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_Interval = { "Interval", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_Ticker_eventTicker_Parms, Interval), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_Ticker_eventTicker_Parms, Duration), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_GASCharactor = { "GASCharactor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_Ticker_eventTicker_Parms, GASCharactor), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_OwningAbility = { "OwningAbility", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AT_Ticker_eventTicker_Parms, OwningAbility), Z_Construct_UClass_UGameplayAbility_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_skipFirstTick,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_Interval,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_Duration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_GASCharactor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::NewProp_OwningAbility,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "TRUE" },
		{ "Category", "Ability|Tasks" },
		{ "Comment", "/** Start a task that repeats an action or set of actions. */" },
		{ "DefaultToSelf", "OwningAbility" },
		{ "DisplayName", "Ticker" },
		{ "HidePin", "OwningAbility" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
		{ "ToolTip", "Start a task that repeats an action or set of actions." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAT_Ticker, nullptr, "Ticker", nullptr, nullptr, sizeof(AT_Ticker_eventTicker_Parms), Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAT_Ticker_Ticker()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAT_Ticker_Ticker_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAT_Ticker_NoRegister()
	{
		return UAT_Ticker::StaticClass();
	}
	struct Z_Construct_UClass_UAT_Ticker_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnInteractCompletedDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnInteractCompletedDelegate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnInteractTickDelegate_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnInteractTickDelegate;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAT_Ticker_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAbilityTask,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAT_Ticker_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAT_Ticker_Ticker, "Ticker" }, // 1509230543
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_Ticker_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AbilitySystem/AbilityTasks/AT_Ticker.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_Ticker_Statics::NewProp_GASCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAT_Ticker_Statics::NewProp_GASCharacter = { "GASCharacter", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAT_Ticker, GASCharacter), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_GASCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_GASCharacter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractCompletedDelegate_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractCompletedDelegate = { "OnInteractCompletedDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAT_Ticker, OnInteractCompletedDelegate), Z_Construct_UDelegateFunction_SonicSiege_DurationEnded__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractCompletedDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractCompletedDelegate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractTickDelegate_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AbilityTasks/AT_Ticker.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractTickDelegate = { "OnInteractTickDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAT_Ticker, OnInteractTickDelegate), Z_Construct_UDelegateFunction_SonicSiege_TickDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractTickDelegate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractTickDelegate_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAT_Ticker_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAT_Ticker_Statics::NewProp_GASCharacter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractCompletedDelegate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAT_Ticker_Statics::NewProp_OnInteractTickDelegate,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAT_Ticker_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAT_Ticker>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAT_Ticker_Statics::ClassParams = {
		&UAT_Ticker::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAT_Ticker_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAT_Ticker_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAT_Ticker_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAT_Ticker_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAT_Ticker()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAT_Ticker_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAT_Ticker, 1531798887);
	template<> SONICSIEGE_API UClass* StaticClass<UAT_Ticker>()
	{
		return UAT_Ticker::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAT_Ticker(Z_Construct_UClass_UAT_Ticker, &UAT_Ticker::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAT_Ticker"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAT_Ticker);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
