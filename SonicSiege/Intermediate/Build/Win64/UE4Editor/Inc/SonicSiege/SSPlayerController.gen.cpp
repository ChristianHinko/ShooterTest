// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Player/SSPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSPlayerController() {}
// Cross Module References
	SONICSIEGE_API UScriptStruct* Z_Construct_UScriptStruct_FPawnInfo();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_APawn_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPlayerController_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPlayerState_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSGameMode_NoRegister();
// End Cross Module References
class UScriptStruct* FPawnInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern SONICSIEGE_API uint32 Get_Z_Construct_UScriptStruct_FPawnInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FPawnInfo, Z_Construct_UPackage__Script_SonicSiege(), TEXT("PawnInfo"), sizeof(FPawnInfo), Get_Z_Construct_UScriptStruct_FPawnInfo_Hash());
	}
	return Singleton;
}
template<> SONICSIEGE_API UScriptStruct* StaticStruct<FPawnInfo>()
{
	return FPawnInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FPawnInfo(FPawnInfo::StaticStruct, TEXT("/Script/SonicSiege"), TEXT("PawnInfo"), false, nullptr, nullptr);
static struct FScriptStruct_SonicSiege_StaticRegisterNativesFPawnInfo
{
	FScriptStruct_SonicSiege_StaticRegisterNativesFPawnInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("PawnInfo")),new UScriptStruct::TCppStructOps<FPawnInfo>);
	}
} ScriptStruct_SonicSiege_StaticRegisterNativesFPawnInfo;
	struct Z_Construct_UScriptStruct_FPawnInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PawnClass_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_PawnClass;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPawnInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n *  This should store the info for a Pawn. A player may switch Pawns by\n *  calling SetPendingPawnInfo(FPawnInfo NewPawnInfo), and then calling UpdatePawn().\n */// do we actually need this?\n" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
		{ "ToolTip", "This should store the info for a Pawn. A player may switch Pawns by\ncalling SetPendingPawnInfo(FPawnInfo NewPawnInfo), and then calling UpdatePawn().\n// do we actually need this?" },
	};
#endif
	void* Z_Construct_UScriptStruct_FPawnInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPawnInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "PawnInfo" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPawnInfo, Name), METADATA_PARAMS(Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_PawnClass_MetaData[] = {
		{ "Category", "PawnInfo" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_PawnClass = { "PawnClass", nullptr, (EPropertyFlags)0x0014000000000005, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPawnInfo, PawnClass), Z_Construct_UClass_APawn_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_PawnClass_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_PawnClass_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPawnInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_Name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPawnInfo_Statics::NewProp_PawnClass,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPawnInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
		nullptr,
		&NewStructOps,
		"PawnInfo",
		sizeof(FPawnInfo),
		alignof(FPawnInfo),
		Z_Construct_UScriptStruct_FPawnInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnInfo_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FPawnInfo_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FPawnInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FPawnInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FPawnInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("PawnInfo"), sizeof(FPawnInfo), Get_Z_Construct_UScriptStruct_FPawnInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FPawnInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FPawnInfo_Hash() { return 3808103276U; }
	DEFINE_FUNCTION(ASSPlayerController::execSpawnPawnFromPendingInfo)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(APawn**)Z_Param__Result=P_THIS->SpawnPawnFromPendingInfo();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ASSPlayerController::execSetPendingPawnInfo)
	{
		P_GET_STRUCT_REF(FPawnInfo,Z_Param_Out_NewPawnInfo);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetPendingPawnInfo(Z_Param_Out_NewPawnInfo);
		P_NATIVE_END;
	}
	void ASSPlayerController::StaticRegisterNativesASSPlayerController()
	{
		UClass* Class = ASSPlayerController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetPendingPawnInfo", &ASSPlayerController::execSetPendingPawnInfo },
			{ "SpawnPawnFromPendingInfo", &ASSPlayerController::execSpawnPawnFromPendingInfo },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics
	{
		struct SSPlayerController_eventSetPendingPawnInfo_Parms
		{
			FPawnInfo NewPawnInfo;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NewPawnInfo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NewPawnInfo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::NewProp_NewPawnInfo_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::NewProp_NewPawnInfo = { "NewPawnInfo", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SSPlayerController_eventSetPendingPawnInfo_Parms, NewPawnInfo), Z_Construct_UScriptStruct_FPawnInfo, METADATA_PARAMS(Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::NewProp_NewPawnInfo_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::NewProp_NewPawnInfo_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::NewProp_NewPawnInfo,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Set a new Pawn to be active. Can be called on client */" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
		{ "ToolTip", "Set a new Pawn to be active. Can be called on client" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASSPlayerController, nullptr, "SetPendingPawnInfo", nullptr, nullptr, sizeof(SSPlayerController_eventSetPendingPawnInfo_Parms), Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics
	{
		struct SSPlayerController_eventSpawnPawnFromPendingInfo_Parms
		{
			APawn* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SSPlayerController_eventSpawnPawnFromPendingInfo_Parms, ReturnValue), Z_Construct_UClass_APawn_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// blueprint callable for testing =@REVIEW MARKER@=\n" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
		{ "ToolTip", "blueprint callable for testing =@REVIEW MARKER@=" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASSPlayerController, nullptr, "SpawnPawnFromPendingInfo", nullptr, nullptr, sizeof(SSPlayerController_eventSpawnPawnFromPendingInfo_Parms), Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ASSPlayerController_NoRegister()
	{
		return ASSPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ASSPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SSPlayerState_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SSPlayerState;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SSGamemode_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SSGamemode;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PawnInfos_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_PawnInfos;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PawnInfos_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASSPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ASSPlayerController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ASSPlayerController_SetPendingPawnInfo, "SetPendingPawnInfo" }, // 3291784252
		{ &Z_Construct_UFunction_ASSPlayerController_SpawnPawnFromPendingInfo, "SpawnPawnFromPendingInfo" }, // 1536809389
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Base player controller (Ability System aware). Holds pending pawn data\n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "Player/SSPlayerController.h" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
		{ "ToolTip", "Base player controller (Ability System aware). Holds pending pawn data" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSPlayerState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSPlayerState = { "SSPlayerState", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSPlayerController, SSPlayerState), Z_Construct_UClass_ASSPlayerState_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSPlayerState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSPlayerState_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSGamemode_MetaData[] = {
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSGamemode = { "SSGamemode", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSPlayerController, SSGamemode), Z_Construct_UClass_ASSGameMode_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSGamemode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSGamemode_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos_MetaData[] = {
		{ "Category", "PawnInfo" },
		{ "ModuleRelativePath", "Public/Player/SSPlayerController.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos = { "PawnInfos", nullptr, (EPropertyFlags)0x0020080000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASSPlayerController, PawnInfos), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos_Inner = { "PawnInfos", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FPawnInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASSPlayerController_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSPlayerState,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSPlayerController_Statics::NewProp_SSGamemode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASSPlayerController_Statics::NewProp_PawnInfos_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASSPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASSPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASSPlayerController_Statics::ClassParams = {
		&ASSPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ASSPlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ASSPlayerController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASSPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASSPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASSPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASSPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASSPlayerController, 1135160238);
	template<> SONICSIEGE_API UClass* StaticClass<ASSPlayerController>()
	{
		return ASSPlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASSPlayerController(Z_Construct_UClass_ASSPlayerController, &ASSPlayerController::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASSPlayerController"), false, nullptr, nullptr, nullptr);

	void ASSPlayerController::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_SSPlayerState(TEXT("SSPlayerState"));

		const bool bIsValid = true
			&& Name_SSPlayerState == ClassReps[(int32)ENetFields_Private::SSPlayerState].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in ASSPlayerController"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASSPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
