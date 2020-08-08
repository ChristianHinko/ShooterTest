// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/TargetActors/GATA_MultiLineTrace.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGATA_MultiLineTrace() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_MultiLineTrace_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AGATA_MultiLineTrace();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_AGameplayAbilityTargetActor_Trace();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	void AGATA_MultiLineTrace::StaticRegisterNativesAGATA_MultiLineTrace()
	{
	}
	UClass* Z_Construct_UClass_AGATA_MultiLineTrace_NoRegister()
	{
		return AGATA_MultiLineTrace::StaticClass();
	}
	struct Z_Construct_UClass_AGATA_MultiLineTrace_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGATA_MultiLineTrace_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameplayAbilityTargetActor_Trace,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGATA_MultiLineTrace_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * THIS IS CURRENTLY BROKEN!!\n * Maybe dont event inherit from target actor _Trace because I'm having to change so much of it\n * Maybe make a AGATA_Traces or something and make this inherit from that\n * If we ever want to use this again what you need to do is make the for loop in ConfirmTargetingAndContinue not run PerformTrace\n * every iteration. Instead implement the for loop inside of PerformTrace (but PerfromTrace only returns one FHitResult not a TArray) which is why\n * you should not use it and maybe not even inherit from _Trace\n * \n * Right now its not working because the AimWithPlayerController function called in PerformTrace is not meant for multiple traces and each itteration of the\n * for loop in ConfirmTargetingAndContinue the line trace swill flip back and forth because of this\n */" },
		{ "IncludePath", "AbilitySystem/TargetActors/GATA_MultiLineTrace.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/TargetActors/GATA_MultiLineTrace.h" },
		{ "ToolTip", "THIS IS CURRENTLY BROKEN!!\nMaybe dont event inherit from target actor _Trace because I'm having to change so much of it\nMaybe make a AGATA_Traces or something and make this inherit from that\nIf we ever want to use this again what you need to do is make the for loop in ConfirmTargetingAndContinue not run PerformTrace\nevery iteration. Instead implement the for loop inside of PerformTrace (but PerfromTrace only returns one FHitResult not a TArray) which is why\nyou should not use it and maybe not even inherit from _Trace\n\nRight now its not working because the AimWithPlayerController function called in PerformTrace is not meant for multiple traces and each itteration of the\nfor loop in ConfirmTargetingAndContinue the line trace swill flip back and forth because of this" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGATA_MultiLineTrace_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGATA_MultiLineTrace>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGATA_MultiLineTrace_Statics::ClassParams = {
		&AGATA_MultiLineTrace::StaticClass,
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
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGATA_MultiLineTrace_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGATA_MultiLineTrace_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGATA_MultiLineTrace()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGATA_MultiLineTrace_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGATA_MultiLineTrace, 1096083339);
	template<> SONICSIEGE_API UClass* StaticClass<AGATA_MultiLineTrace>()
	{
		return AGATA_MultiLineTrace::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGATA_MultiLineTrace(Z_Construct_UClass_AGATA_MultiLineTrace, &AGATA_MultiLineTrace::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AGATA_MultiLineTrace"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGATA_MultiLineTrace);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
