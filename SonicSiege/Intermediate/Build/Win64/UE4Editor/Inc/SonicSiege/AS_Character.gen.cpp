// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/AS_Character.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAS_Character() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
// End Cross Module References
	DEFINE_FUNCTION(UAS_Character::execOnRep_Stamina)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_Stamina(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_MaxStamina)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_MaxStamina(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_Health)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_Health(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_MaxHealth)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_MaxHealth(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_RunAccelaration)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_RunAccelaration(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_RunSpeed)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_RunSpeed(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_WalkAcceleration)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_WalkAcceleration(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Character::execOnRep_WalkSpeed)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_WalkSpeed(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	void UAS_Character::StaticRegisterNativesUAS_Character()
	{
		UClass* Class = UAS_Character::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRep_Health", &UAS_Character::execOnRep_Health },
			{ "OnRep_MaxHealth", &UAS_Character::execOnRep_MaxHealth },
			{ "OnRep_MaxStamina", &UAS_Character::execOnRep_MaxStamina },
			{ "OnRep_RunAccelaration", &UAS_Character::execOnRep_RunAccelaration },
			{ "OnRep_RunSpeed", &UAS_Character::execOnRep_RunSpeed },
			{ "OnRep_Stamina", &UAS_Character::execOnRep_Stamina },
			{ "OnRep_WalkAcceleration", &UAS_Character::execOnRep_WalkAcceleration },
			{ "OnRep_WalkSpeed", &UAS_Character::execOnRep_WalkSpeed },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics
	{
		struct AS_Character_eventOnRep_Health_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_Health_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_Health", nullptr, nullptr, sizeof(AS_Character_eventOnRep_Health_Parms), Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_Health()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_Health_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics
	{
		struct AS_Character_eventOnRep_MaxHealth_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_MaxHealth_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_MaxHealth", nullptr, nullptr, sizeof(AS_Character_eventOnRep_MaxHealth_Parms), Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics
	{
		struct AS_Character_eventOnRep_MaxStamina_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_MaxStamina_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_MaxStamina", nullptr, nullptr, sizeof(AS_Character_eventOnRep_MaxStamina_Parms), Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics
	{
		struct AS_Character_eventOnRep_RunAccelaration_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_RunAccelaration_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_RunAccelaration", nullptr, nullptr, sizeof(AS_Character_eventOnRep_RunAccelaration_Parms), Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics
	{
		struct AS_Character_eventOnRep_RunSpeed_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_RunSpeed_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_RunSpeed", nullptr, nullptr, sizeof(AS_Character_eventOnRep_RunSpeed_Parms), Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics
	{
		struct AS_Character_eventOnRep_Stamina_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_Stamina_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_Stamina", nullptr, nullptr, sizeof(AS_Character_eventOnRep_Stamina_Parms), Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_Stamina()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_Stamina_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics
	{
		struct AS_Character_eventOnRep_WalkAcceleration_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_WalkAcceleration_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_WalkAcceleration", nullptr, nullptr, sizeof(AS_Character_eventOnRep_WalkAcceleration_Parms), Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics
	{
		struct AS_Character_eventOnRep_WalkSpeed_Parms
		{
			FGameplayAttributeData ServerBaseValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ServerBaseValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ServerBaseValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Character_eventOnRep_WalkSpeed_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication\n" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
		{ "ToolTip", "These OnReps exist to make sure the GAS internal representations are synchronized properly during replication" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Character, nullptr, "OnRep_WalkSpeed", nullptr, nullptr, sizeof(AS_Character_eventOnRep_WalkSpeed_Parms), Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAS_Character_NoRegister()
	{
		return UAS_Character::StaticClass();
	}
	struct Z_Construct_UClass_UAS_Character_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StaminaGain_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StaminaGain;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StaminaDrain_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StaminaDrain;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Stamina_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Stamina;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxStamina_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MaxStamina;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Healing_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Healing;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Damage_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Damage;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Health_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Health;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxHealth_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MaxHealth;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RunAccelaration_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RunAccelaration;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RunSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RunSpeed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WalkAcceleration_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WalkAcceleration;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WalkSpeed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WalkSpeed;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAS_Character_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAS_Character_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAS_Character_OnRep_Health, "OnRep_Health" }, // 2792423855
		{ &Z_Construct_UFunction_UAS_Character_OnRep_MaxHealth, "OnRep_MaxHealth" }, // 2313229851
		{ &Z_Construct_UFunction_UAS_Character_OnRep_MaxStamina, "OnRep_MaxStamina" }, // 502694095
		{ &Z_Construct_UFunction_UAS_Character_OnRep_RunAccelaration, "OnRep_RunAccelaration" }, // 1136541200
		{ &Z_Construct_UFunction_UAS_Character_OnRep_RunSpeed, "OnRep_RunSpeed" }, // 606458188
		{ &Z_Construct_UFunction_UAS_Character_OnRep_Stamina, "OnRep_Stamina" }, // 3705740574
		{ &Z_Construct_UFunction_UAS_Character_OnRep_WalkAcceleration, "OnRep_WalkAcceleration" }, // 4218194381
		{ &Z_Construct_UFunction_UAS_Character_OnRep_WalkSpeed, "OnRep_WalkSpeed" }, // 1444832055
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This attribute set will be on every character that uses the ability system (using AbilitySystemCharacter)\n * add universal character attributes here.\n */" },
		{ "IncludePath", "Character/AS_Character.h" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
		{ "ToolTip", "This attribute set will be on every character that uses the ability system (using AbilitySystemCharacter)\nadd universal character attributes here." },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaGain_MetaData[] = {
		{ "Category", "Attributes" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaGain = { "StaminaGain", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, StaminaGain), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaGain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaGain_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaDrain_MetaData[] = {
		{ "Category", "Attributes" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaDrain = { "StaminaDrain", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, StaminaDrain), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaDrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaDrain_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_Stamina_MetaData[] = {
		{ "Category", "Attributes" },
		{ "HideFromModifiers", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_Stamina = { "Stamina", "OnRep_Stamina", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, Stamina), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_Stamina_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_Stamina_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxStamina_MetaData[] = {
		{ "Category", "Attributes" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxStamina = { "MaxStamina", "OnRep_MaxStamina", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, MaxStamina), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxStamina_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxStamina_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_Healing_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "/** This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient\n" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
		{ "ToolTip", "This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) // You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_Healing = { "Healing", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, Healing), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_Healing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_Healing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_Damage_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "/** This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient\n" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
		{ "ToolTip", "This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) // You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, Damage), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_Damage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_Damage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_Health_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it\n" },
		{ "HideFromModifiers", "" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
		{ "ToolTip", "HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_Health = { "Health", "OnRep_Health", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, Health), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_Health_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_Health_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Attributes" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxHealth = { "MaxHealth", "OnRep_MaxHealth", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, MaxHealth), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxHealth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxHealth_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_RunAccelaration_MetaData[] = {
		{ "Category", "Attributes|Movement" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_RunAccelaration = { "RunAccelaration", "OnRep_RunAccelaration", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, RunAccelaration), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_RunAccelaration_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_RunAccelaration_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_RunSpeed_MetaData[] = {
		{ "Category", "Attributes|Movement" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_RunSpeed = { "RunSpeed", "OnRep_RunSpeed", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, RunSpeed), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_RunSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_RunSpeed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkAcceleration_MetaData[] = {
		{ "Category", "Attributes|Movement" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkAcceleration = { "WalkAcceleration", "OnRep_WalkAcceleration", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, WalkAcceleration), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkAcceleration_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkAcceleration_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkSpeed_MetaData[] = {
		{ "Category", "Attributes|Movement" },
		{ "ModuleRelativePath", "Public/Character/AS_Character.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkSpeed = { "WalkSpeed", "OnRep_WalkSpeed", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Character, WalkSpeed), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkSpeed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkSpeed_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAS_Character_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaGain,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_StaminaDrain,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_Stamina,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxStamina,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_Healing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_Damage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_Health,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_MaxHealth,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_RunAccelaration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_RunSpeed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkAcceleration,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Character_Statics::NewProp_WalkSpeed,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAS_Character_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAS_Character>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAS_Character_Statics::ClassParams = {
		&UAS_Character::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAS_Character_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::PropPointers),
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAS_Character_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Character_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAS_Character()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAS_Character_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAS_Character, 2795914403);
	template<> SONICSIEGE_API UClass* StaticClass<UAS_Character>()
	{
		return UAS_Character::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAS_Character(Z_Construct_UClass_UAS_Character, &UAS_Character::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAS_Character"), false, nullptr, nullptr, nullptr);

	void UAS_Character::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_WalkSpeed(TEXT("WalkSpeed"));
		static const FName Name_WalkAcceleration(TEXT("WalkAcceleration"));
		static const FName Name_RunSpeed(TEXT("RunSpeed"));
		static const FName Name_RunAccelaration(TEXT("RunAccelaration"));
		static const FName Name_MaxHealth(TEXT("MaxHealth"));
		static const FName Name_Health(TEXT("Health"));
		static const FName Name_MaxStamina(TEXT("MaxStamina"));
		static const FName Name_Stamina(TEXT("Stamina"));

		const bool bIsValid = true
			&& Name_WalkSpeed == ClassReps[(int32)ENetFields_Private::WalkSpeed].Property->GetFName()
			&& Name_WalkAcceleration == ClassReps[(int32)ENetFields_Private::WalkAcceleration].Property->GetFName()
			&& Name_RunSpeed == ClassReps[(int32)ENetFields_Private::RunSpeed].Property->GetFName()
			&& Name_RunAccelaration == ClassReps[(int32)ENetFields_Private::RunAccelaration].Property->GetFName()
			&& Name_MaxHealth == ClassReps[(int32)ENetFields_Private::MaxHealth].Property->GetFName()
			&& Name_Health == ClassReps[(int32)ENetFields_Private::Health].Property->GetFName()
			&& Name_MaxStamina == ClassReps[(int32)ENetFields_Private::MaxStamina].Property->GetFName()
			&& Name_Stamina == ClassReps[(int32)ENetFields_Private::Stamina].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UAS_Character"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAS_Character);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
