// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/SSAbilityTask.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSAbilityTask() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilityTask();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilityTask();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void USSAbilityTask::StaticRegisterNativesUSSAbilityTask()
	{
	}
	UClass* Z_Construct_UClass_USSAbilityTask_NoRegister()
	{
		return USSAbilityTask::StaticClass();
	}
	struct Z_Construct_UClass_USSAbilityTask_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSAbilityTask_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAbilityTask,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSAbilityTask_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base ability task class\n */" },
		{ "IncludePath", "AbilitySystem/SSAbilityTask.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSAbilityTask.h" },
		{ "ToolTip", "Base ability task class" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSAbilityTask_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSAbilityTask>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSAbilityTask_Statics::ClassParams = {
		&USSAbilityTask::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_USSAbilityTask_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSAbilityTask_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSAbilityTask()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSAbilityTask_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSAbilityTask, 4029839933);
	template<> SONICSIEGE_API UClass* StaticClass<USSAbilityTask>()
	{
		return USSAbilityTask::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSAbilityTask(Z_Construct_UClass_USSAbilityTask, &USSAbilityTask::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSAbilityTask"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSAbilityTask);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
