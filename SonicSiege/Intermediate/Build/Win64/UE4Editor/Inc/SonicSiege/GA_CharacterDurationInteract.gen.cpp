// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGA_CharacterDurationInteract() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterDurationInteract_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterDurationInteract();
	SONICSIEGE_API UClass* Z_Construct_UClass_UGA_CharacterInteract();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
// End Cross Module References
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnSuccessfullInteract)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnSuccessfullInteract(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnNewInteractionPriority)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnNewInteractionPriority(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnCharacterLeftInteractionOverlap)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnCharacterLeftInteractionOverlap(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnInteractionSweepMiss)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInteractionSweepMiss(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnRelease)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRelease(Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGA_CharacterDurationInteract::execOnInteractTick)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
		P_GET_PROPERTY(FFloatProperty,Z_Param_TimeHeld);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnInteractTick(Z_Param_DeltaTime,Z_Param_TimeHeld);
		P_NATIVE_END;
	}
	void UGA_CharacterDurationInteract::StaticRegisterNativesUGA_CharacterDurationInteract()
	{
		UClass* Class = UGA_CharacterDurationInteract::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnCharacterLeftInteractionOverlap", &UGA_CharacterDurationInteract::execOnCharacterLeftInteractionOverlap },
			{ "OnInteractionSweepMiss", &UGA_CharacterDurationInteract::execOnInteractionSweepMiss },
			{ "OnInteractTick", &UGA_CharacterDurationInteract::execOnInteractTick },
			{ "OnNewInteractionPriority", &UGA_CharacterDurationInteract::execOnNewInteractionPriority },
			{ "OnRelease", &UGA_CharacterDurationInteract::execOnRelease },
			{ "OnSuccessfullInteract", &UGA_CharacterDurationInteract::execOnSuccessfullInteract },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics
	{
		struct GA_CharacterDurationInteract_eventOnCharacterLeftInteractionOverlap_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnCharacterLeftInteractionOverlap_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnCharacterLeftInteractionOverlap", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnCharacterLeftInteractionOverlap_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics
	{
		struct GA_CharacterDurationInteract_eventOnInteractionSweepMiss_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnInteractionSweepMiss_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnInteractionSweepMiss", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnInteractionSweepMiss_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics
	{
		struct GA_CharacterDurationInteract_eventOnInteractTick_Parms
		{
			float DeltaTime;
			float TimeHeld;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TimeHeld;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnInteractTick_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnInteractTick_Parms, DeltaTime), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::NewProp_TimeHeld,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::NewProp_DeltaTime,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnInteractTick", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnInteractTick_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics
	{
		struct GA_CharacterDurationInteract_eventOnNewInteractionPriority_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnNewInteractionPriority_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnNewInteractionPriority", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnNewInteractionPriority_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics
	{
		struct GA_CharacterDurationInteract_eventOnRelease_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnRelease_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnRelease", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnRelease_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics
	{
		struct GA_CharacterDurationInteract_eventOnSuccessfullInteract_Parms
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
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::NewProp_TimeHeld = { "TimeHeld", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(GA_CharacterDurationInteract_eventOnSuccessfullInteract_Parms, TimeHeld), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::NewProp_TimeHeld,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGA_CharacterDurationInteract, nullptr, "OnSuccessfullInteract", nullptr, nullptr, sizeof(GA_CharacterDurationInteract_eventOnSuccessfullInteract_Parms), Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UGA_CharacterDurationInteract_NoRegister()
	{
		return UGA_CharacterDurationInteract::StaticClass();
	}
	struct Z_Construct_UClass_UGA_CharacterDurationInteract_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGA_CharacterInteract,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnCharacterLeftInteractionOverlap, "OnCharacterLeftInteractionOverlap" }, // 559191013
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractionSweepMiss, "OnInteractionSweepMiss" }, // 3194918279
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnInteractTick, "OnInteractTick" }, // 2947047837
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnNewInteractionPriority, "OnNewInteractionPriority" }, // 2075912441
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnRelease, "OnRelease" }, // 3372565649
		{ &Z_Construct_UFunction_UGA_CharacterDurationInteract_OnSuccessfullInteract, "OnSuccessfullInteract" }, // 3962397195
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\x09TODO: Currently the abilty only does a check if both client and server have an interactable. If one of them don't, it doesn't activate.\n *  But another check is needed for this system to be fully stable. We need to make another check to see if the client and server have the\n *  same object as theinteractable.\n */" },
		{ "IncludePath", "Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
		{ "ModuleRelativePath", "Public/Character/Abilities/Interact/GA_CharacterDurationInteract.h" },
		{ "ToolTip", "TODO: Currently the abilty only does a check if both client and server have an interactable. If one of them don't, it doesn't activate.\nBut another check is needed for this system to be fully stable. We need to make another check to see if the client and server have the\nsame object as theinteractable." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGA_CharacterDurationInteract>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::ClassParams = {
		&UGA_CharacterDurationInteract::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGA_CharacterDurationInteract()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UGA_CharacterDurationInteract_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UGA_CharacterDurationInteract, 2001361722);
	template<> SONICSIEGE_API UClass* StaticClass<UGA_CharacterDurationInteract>()
	{
		return UGA_CharacterDurationInteract::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UGA_CharacterDurationInteract(Z_Construct_UClass_UGA_CharacterDurationInteract, &UGA_CharacterDurationInteract::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UGA_CharacterDurationInteract"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGA_CharacterDurationInteract);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
