// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/Item/Weapon/Abilities/GA_ADS.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_ADS() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_ADS_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_ADS();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	DEFINE_FUNCTION(UGA_ADS::execOnRelease)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRelease(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	void UGA_ADS::StaticRegisterNativesUGA_ADS()
	{
		UClass* Class = UGA_ADS::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRelease", &UGA_ADS::execOnRelease },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_ADS_OnRelease_Statics
	{
		struct GA_ADS_eventOnRelease_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_ADS_eventOnRelease_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//END UGameplayAbility Interface\n" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_ADS.h" },
		{ "ToolTip", "END UGameplayAbility Interface" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_ADS, nullptr, "OnRelease", nullptr, nullptr, sizeof(GA_ADS_eventOnRelease_Parms), Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_ADS_OnRelease()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_ADS_OnRelease_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_ADS_NoRegister()
	{
		return UGA_ADS::StaticClass();
	}
	struct Z_Construct_UClass_UGA_ADS_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_ADS_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSGameplayAbility,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_ADS_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_ADS_OnRelease, "OnRelease" }, // 3615437529
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_ADS_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Actor/Item/Weapon/Abilities/GA_ADS.h" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/Abilities/GA_ADS.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_ADS_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_ADS>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_ADS_Statics::ClassParams = {
		&UGA_ADS::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGA_ADS_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_ADS_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_ADS()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_ADS_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_ADS, 2817784106);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_ADS>()
	{
		return UGA_ADS::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_ADS(Z_Construct_UClass_UGA_ADS, &UGA_ADS::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_ADS"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_ADS);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
