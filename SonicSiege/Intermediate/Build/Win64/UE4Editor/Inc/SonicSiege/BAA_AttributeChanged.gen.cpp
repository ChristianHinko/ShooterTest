// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBAA_AttributeChanged() {}
// Cross Module References
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttribute();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_AttributeChanged_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UBAA_AttributeChanged();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintAsyncActionBase();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics
	{
		struct _Script_SonicSiege_eventOnAttributeChanged_Parms
		{
			FGameplayAttribute Attribute;
			float NewValue;
			float OldValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OldValue;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_NewValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Attribute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_OldValue = { "OldValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnAttributeChanged_Parms, OldValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnAttributeChanged_Parms, NewValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_SonicSiege_eventOnAttributeChanged_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_OldValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_NewValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::NewProp_Attribute,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_SonicSiege, nullptr, "OnAttributeChanged__DelegateSignature", nullptr, nullptr, sizeof(_Script_SonicSiege_eventOnAttributeChanged_Parms), Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UBAA_AttributeChanged::execEndTask)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EndTask();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBAA_AttributeChanged::execListenForAttributesChange)
	{
		P_GET_OBJECT(UAbilitySystemComponent,Z_Param_AbilitySystemComponent);
		P_GET_TARRAY(FGameplayAttribute,Z_Param_Attributes);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBAA_AttributeChanged**)Z_Param__Result=UBAA_AttributeChanged::ListenForAttributesChange(Z_Param_AbilitySystemComponent,Z_Param_Attributes);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBAA_AttributeChanged::execListenForAttributeChange)
	{
		P_GET_OBJECT(UAbilitySystemComponent,Z_Param_AbilitySystemComponent);
		P_GET_STRUCT(FGameplayAttribute,Z_Param_Attribute);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBAA_AttributeChanged**)Z_Param__Result=UBAA_AttributeChanged::ListenForAttributeChange(Z_Param_AbilitySystemComponent,Z_Param_Attribute);
		P_NATIVE_END;
	}
	void UBAA_AttributeChanged::StaticRegisterNativesUBAA_AttributeChanged()
	{
		UClass* Class = UBAA_AttributeChanged::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EndTask", &UBAA_AttributeChanged::execEndTask },
			{ "ListenForAttributeChange", &UBAA_AttributeChanged::execListenForAttributeChange },
			{ "ListenForAttributesChange", &UBAA_AttributeChanged::execListenForAttributesChange },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/**\n\x09 * You must call this function manually when you want the AsyncTask to end.\n\x09 * For UMG Widgets, you would call it in the Widget's Destruct event.\n\x09 */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
		{ "ToolTip", "You must call this function manually when you want the AsyncTask to end.\nFor UMG Widgets, you would call it in the Widget's Destruct event." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_AttributeChanged, nullptr, "EndTask", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_AttributeChanged_EndTask()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_AttributeChanged_EndTask_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics
	{
		struct BAA_AttributeChanged_eventListenForAttributeChange_Parms
		{
			UAbilitySystemComponent* AbilitySystemComponent;
			FGameplayAttribute Attribute;
			UBAA_AttributeChanged* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Attribute;
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributeChange_Parms, ReturnValue), Z_Construct_UClass_UBAA_AttributeChanged_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_Attribute = { "Attribute", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributeChange_Parms, Attribute), Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_AbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributeChange_Parms, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_AbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_AbilitySystemComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_Attribute,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::NewProp_AbilitySystemComponent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Comment", "/** Listens for an attribute changing. */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
		{ "ToolTip", "Listens for an attribute changing." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_AttributeChanged, nullptr, "ListenForAttributeChange", nullptr, nullptr, sizeof(BAA_AttributeChanged_eventListenForAttributeChange_Parms), Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics
	{
		struct BAA_AttributeChanged_eventListenForAttributesChange_Parms
		{
			UAbilitySystemComponent* AbilitySystemComponent;
			TArray<FGameplayAttribute> Attributes;
			UBAA_AttributeChanged* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Attributes;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Attributes_Inner;
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributesChange_Parms, ReturnValue), Z_Construct_UClass_UBAA_AttributeChanged_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_Attributes = { "Attributes", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributesChange_Parms, Attributes), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_Attributes_Inner = { "Attributes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FGameplayAttribute, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_AbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_AbilitySystemComponent = { "AbilitySystemComponent", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BAA_AttributeChanged_eventListenForAttributesChange_Parms, AbilitySystemComponent), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_AbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_AbilitySystemComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_Attributes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_Attributes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::NewProp_AbilitySystemComponent,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Comment", "/**\n\x09 * Listens for an attribute changing.\n\x09 * Version that takes in an array of Attributes. Check the Attribute output for which Attribute changed.\n\x09 */" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
		{ "ToolTip", "Listens for an attribute changing.\nVersion that takes in an array of Attributes. Check the Attribute output for which Attribute changed." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBAA_AttributeChanged, nullptr, "ListenForAttributesChange", nullptr, nullptr, sizeof(BAA_AttributeChanged_eventListenForAttributesChange_Parms), Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBAA_AttributeChanged_NoRegister()
	{
		return UBAA_AttributeChanged::StaticClass();
	}
	struct Z_Construct_UClass_UBAA_AttributeChanged_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnAttributeChanged_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAttributeChanged;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBAA_AttributeChanged_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintAsyncActionBase,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBAA_AttributeChanged_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBAA_AttributeChanged_EndTask, "EndTask" }, // 3171604180
		{ &Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributeChange, "ListenForAttributeChange" }, // 1398528409
		{ &Z_Construct_UFunction_UBAA_AttributeChanged_ListenForAttributesChange, "ListenForAttributesChange" }, // 186902225
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_AttributeChanged_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * Blueprint node to automatically register a listener for all attribute changes in an AbilitySystemComponent.\n * Useful to use in UI.\n */" },
		{ "ExposedAsyncProxy", "AsyncTask" },
		{ "IncludePath", "AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
		{ "ToolTip", "Blueprint node to automatically register a listener for all attribute changes in an AbilitySystemComponent.\nUseful to use in UI." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_ASC_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_ASC = { "ASC", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_AttributeChanged, ASC), Z_Construct_UClass_UAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_ASC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_ASC_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_OnAttributeChanged_MetaData[] = {
		{ "ModuleRelativePath", "Public/AbilitySystem/AsyncListeners/BAA_AttributeChanged.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_OnAttributeChanged = { "OnAttributeChanged", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBAA_AttributeChanged, OnAttributeChanged), Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_OnAttributeChanged_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_OnAttributeChanged_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBAA_AttributeChanged_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_ASC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBAA_AttributeChanged_Statics::NewProp_OnAttributeChanged,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBAA_AttributeChanged_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBAA_AttributeChanged>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBAA_AttributeChanged_Statics::ClassParams = {
		&UBAA_AttributeChanged::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBAA_AttributeChanged_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_AttributeChanged_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBAA_AttributeChanged_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBAA_AttributeChanged_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBAA_AttributeChanged()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBAA_AttributeChanged_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBAA_AttributeChanged, 4008747040);
	template<> SONICSIEGE_API UClass* StaticClass<UBAA_AttributeChanged>()
	{
		return UBAA_AttributeChanged::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBAA_AttributeChanged(Z_Construct_UClass_UBAA_AttributeChanged, &UBAA_AttributeChanged::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UBAA_AttributeChanged"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBAA_AttributeChanged);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
