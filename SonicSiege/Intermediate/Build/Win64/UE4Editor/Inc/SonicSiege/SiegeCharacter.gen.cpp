// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/SiegeCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSiegeCharacter() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_ASiegeCharacter_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASiegeCharacter();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(ASiegeCharacter::execOnComponentEndOverlapCharacterCapsule)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnComponentEndOverlapCharacterCapsule(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ASiegeCharacter::execOnComponentBeginOverlapCharacterCapsule)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComp);
		P_GET_OBJECT(AActor,Z_Param_OtherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
		P_GET_UBOOL(Z_Param_bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnComponentBeginOverlapCharacterCapsule(Z_Param_OverlappedComp,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
		P_NATIVE_END;
	}
	void ASiegeCharacter::StaticRegisterNativesASiegeCharacter()
	{
		UClass* Class = ASiegeCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnComponentBeginOverlapCharacterCapsule", &ASiegeCharacter::execOnComponentBeginOverlapCharacterCapsule },
			{ "OnComponentEndOverlapCharacterCapsule", &ASiegeCharacter::execOnComponentEndOverlapCharacterCapsule },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics
	{
		struct SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms
		{
			UPrimitiveComponent* OverlappedComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
			bool bFromSweep;
			FHitResult SweepResult;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SweepResult;
		static void NewProp_bFromSweep_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_SweepResult_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_SweepResult_MetaData)) };
	void Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_bFromSweep_SetBit(void* Obj)
	{
		((SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms*)Obj)->bFromSweep = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms), &Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_SweepResult,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_bFromSweep,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherBodyIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::NewProp_OverlappedComp,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/SiegeCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASiegeCharacter, nullptr, "OnComponentBeginOverlapCharacterCapsule", nullptr, nullptr, sizeof(SiegeCharacter_eventOnComponentBeginOverlapCharacterCapsule_Parms), Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics
	{
		struct SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms
		{
			UPrimitiveComponent* OverlappedComp;
			AActor* OtherActor;
			UPrimitiveComponent* OtherComp;
			int32 OtherBodyIndex;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OverlappedComp_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OverlappedComp;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms, OtherBodyIndex), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherComp_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OverlappedComp = { "OverlappedComp", nullptr, (EPropertyFlags)0x0010000000080080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms, OverlappedComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OverlappedComp_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherBodyIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherComp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OtherActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::NewProp_OverlappedComp,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/SiegeCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASiegeCharacter, nullptr, "OnComponentEndOverlapCharacterCapsule", nullptr, nullptr, sizeof(SiegeCharacter_eventOnComponentEndOverlapCharacterCapsule_Parms), Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ASiegeCharacter_NoRegister()
	{
		return ASiegeCharacter::StaticClass();
	}
	struct Z_Construct_UClass_ASiegeCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractSweepRadius_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_InteractSweepRadius;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractSweepDistance_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_InteractSweepDistance;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASiegeCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAbilitySystemCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ASiegeCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ASiegeCharacter_OnComponentBeginOverlapCharacterCapsule, "OnComponentBeginOverlapCharacterCapsule" }, // 2332639187
		{ &Z_Construct_UFunction_ASiegeCharacter_OnComponentEndOverlapCharacterCapsule, "OnComponentEndOverlapCharacterCapsule" }, // 9630384
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASiegeCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/SiegeCharacter.h" },
		{ "ModuleRelativePath", "Public/Character/SiegeCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepRadius_MetaData[] = {
		{ "Category", "SiegeCharacter" },
		{ "ModuleRelativePath", "Public/Character/SiegeCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepRadius = { "InteractSweepRadius", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASiegeCharacter, InteractSweepRadius), METADATA_PARAMS(Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepRadius_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepRadius_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepDistance_MetaData[] = {
		{ "Category", "SiegeCharacter" },
		{ "Comment", "//END AActor Interface\n" },
		{ "ModuleRelativePath", "Public/Character/SiegeCharacter.h" },
		{ "ToolTip", "END AActor Interface" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepDistance = { "InteractSweepDistance", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASiegeCharacter, InteractSweepDistance), METADATA_PARAMS(Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepDistance_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepDistance_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASiegeCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepRadius,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASiegeCharacter_Statics::NewProp_InteractSweepDistance,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASiegeCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASiegeCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASiegeCharacter_Statics::ClassParams = {
		&ASiegeCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ASiegeCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ASiegeCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ASiegeCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASiegeCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASiegeCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASiegeCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASiegeCharacter, 817518044);
	template<> SONICSIEGE_API UClass* StaticClass<ASiegeCharacter>()
	{
		return ASiegeCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASiegeCharacter(Z_Construct_UClass_ASiegeCharacter, &ASiegeCharacter::StaticClass, TEXT("/Script/SonicSiege"), TEXT("ASiegeCharacter"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASiegeCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
