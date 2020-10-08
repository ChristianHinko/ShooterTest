// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/SSAbilitySystemBlueprintLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSAbilitySystemBlueprintLibrary() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemBlueprintLibrary();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemBlueprintLibrary();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FGATDF_MultiFilterHandle();
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FGATDF_MultiFilter();
// End Cross Module References
	DEFINE_FUNCTION(USSAbilitySystemBlueprintLibrary::execMakeMultiFilterHandle)
	{
		P_GET_STRUCT(FGATDF_MultiFilter,Z_Param_MultiFilter);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FGATDF_MultiFilterHandle*)Z_Param__Result=USSAbilitySystemBlueprintLibrary::MakeMultiFilterHandle(Z_Param_MultiFilter);
		P_NATIVE_END;
	}
	void USSAbilitySystemBlueprintLibrary::StaticRegisterNativesUSSAbilitySystemBlueprintLibrary()
	{
		UClass* Class = USSAbilitySystemBlueprintLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "MakeMultiFilterHandle", &USSAbilitySystemBlueprintLibrary::execMakeMultiFilterHandle },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics
	{
		struct SSAbilitySystemBlueprintLibrary_eventMakeMultiFilterHandle_Parms
		{
			FGATDF_MultiFilter MultiFilter;
			FGATDF_MultiFilterHandle ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MultiFilter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SSAbilitySystemBlueprintLibrary_eventMakeMultiFilterHandle_Parms, ReturnValue), Z_Construct_UScriptStruct_FGATDF_MultiFilterHandle, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::NewProp_MultiFilter = { "MultiFilter", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SSAbilitySystemBlueprintLibrary_eventMakeMultiFilterHandle_Parms, MultiFilter), Z_Construct_UScriptStruct_FGATDF_MultiFilter, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::NewProp_MultiFilter,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::Function_MetaDataParams[] = {
		{ "Category", "Filter" },
		{ "Comment", "/*, AActor* FilterActor*/" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSAbilitySystemBlueprintLibrary.h" },
		{ "ToolTip", ", AActor* FilterActor" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USSAbilitySystemBlueprintLibrary, nullptr, "MakeMultiFilterHandle", nullptr, nullptr, sizeof(SSAbilitySystemBlueprintLibrary_eventMakeMultiFilterHandle_Parms), Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_NoRegister()
	{
		return USSAbilitySystemBlueprintLibrary::StaticClass();
	}
	struct Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAbilitySystemBlueprintLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USSAbilitySystemBlueprintLibrary_MakeMultiFilterHandle, "MakeMultiFilterHandle" }, // 3870279228
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AbilitySystem/SSAbilitySystemBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSAbilitySystemBlueprintLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSAbilitySystemBlueprintLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::ClassParams = {
		&USSAbilitySystemBlueprintLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSAbilitySystemBlueprintLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSAbilitySystemBlueprintLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSAbilitySystemBlueprintLibrary, 2309376133);
	template<> SONICSIEGE_API UClass* StaticClass<USSAbilitySystemBlueprintLibrary>()
	{
		return USSAbilitySystemBlueprintLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSAbilitySystemBlueprintLibrary(Z_Construct_UClass_USSAbilitySystemBlueprintLibrary, &USSAbilitySystemBlueprintLibrary::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSAbilitySystemBlueprintLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSAbilitySystemBlueprintLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
