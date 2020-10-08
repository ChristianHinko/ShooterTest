// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGATA_Trace() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_Trace_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_Trace();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_AGameplayAbilityTargetActor();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FGATDF_MultiFilter();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
// End Cross Module References
	void AGATA_Trace::StaticRegisterNativesAGATA_Trace()
	{
	}
	UClass* Z_Construct_UClass_AGATA_Trace_NoRegister()
	{
		return AGATA_Trace::StaticClass();
	}
	struct Z_Construct_UClass_AGATA_Trace_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MultiFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MultiFilter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bTraceAffectsAimPitch_MetaData[];
#endif
		static void NewProp_bTraceAffectsAimPitch_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bTraceAffectsAimPitch;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TraceChannel_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_TraceChannel;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxRange_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxRange;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGATA_Trace_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameplayAbilityTargetActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_Trace_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MultiFilter_MetaData[] = {
		{ "Category", "Trace" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MultiFilter = { "MultiFilter", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGATA_Trace, MultiFilter), Z_Construct_UScriptStruct_FGATDF_MultiFilter, METADATA_PARAMS(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MultiFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MultiFilter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch_MetaData[] = {
		{ "Category", "Trace" },
		{ "Comment", "/** Does the trace affect the aiming pitch */" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
		{ "ToolTip", "Does the trace affect the aiming pitch" },
	};
#endif
	void Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch_SetBit(void* Obj)
	{
		((AGATA_Trace*)Obj)->bTraceAffectsAimPitch = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch = { "bTraceAffectsAimPitch", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AGATA_Trace), &Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch_SetBit, METADATA_PARAMS(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_Trace_Statics::NewProp_TraceChannel_MetaData[] = {
		{ "Category", "Trace" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AGATA_Trace_Statics::NewProp_TraceChannel = { "TraceChannel", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGATA_Trace, TraceChannel), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_TraceChannel_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_TraceChannel_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MaxRange_MetaData[] = {
		{ "Category", "Trace" },
		{ "ExposeOnSpawn", "TRUE" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActor/TargetActors/GATA_Trace.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MaxRange = { "MaxRange", nullptr, (EPropertyFlags)0x0011000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGATA_Trace, MaxRange), METADATA_PARAMS(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MaxRange_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MaxRange_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGATA_Trace_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MultiFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_Trace_Statics::NewProp_bTraceAffectsAimPitch,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_Trace_Statics::NewProp_TraceChannel,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGATA_Trace_Statics::NewProp_MaxRange,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGATA_Trace_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGATA_Trace>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGATA_Trace_Statics::ClassParams = {
		&AGATA_Trace::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGATA_Trace_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGATA_Trace_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_Trace_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGATA_Trace()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGATA_Trace_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGATA_Trace, 330954477);
	template<> SONICSIEGE_API UClass* StaticClass<AGATA_Trace>()
	{
		return AGATA_Trace::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGATA_Trace(Z_Construct_UClass_AGATA_Trace, &AGATA_Trace::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AGATA_Trace"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGATA_Trace);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
