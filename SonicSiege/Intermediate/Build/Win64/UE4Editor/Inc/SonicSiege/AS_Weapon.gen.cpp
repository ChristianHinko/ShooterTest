// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/Item/Weapon/AS_Weapon.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAS_Weapon() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Weapon_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Weapon();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
// End Cross Module References
	DEFINE_FUNCTION(UAS_Weapon::execOnRep_CurrentAmmo)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_CurrentAmmo(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	void UAS_Weapon::StaticRegisterNativesUAS_Weapon()
	{
		UClass* Class = UAS_Weapon::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRep_CurrentAmmo", &UAS_Weapon::execOnRep_CurrentAmmo },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics
	{
		struct AS_Weapon_eventOnRep_CurrentAmmo_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Weapon_eventOnRep_CurrentAmmo_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/AS_Weapon.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Weapon, nullptr, "OnRep_CurrentAmmo", nullptr, nullptr, sizeof(AS_Weapon_eventOnRep_CurrentAmmo_Parms), Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAS_Weapon_NoRegister()
	{
		return UAS_Weapon::StaticClass();
	}
	struct Z_Construct_UClass_UAS_Weapon_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentAmmo_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CurrentAmmo;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAS_Weapon_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAS_Weapon_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAS_Weapon_OnRep_CurrentAmmo, "OnRep_CurrentAmmo" }, // 1043832597
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Weapon_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Actor/Item/Weapon/AS_Weapon.h" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/AS_Weapon.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Weapon_Statics::NewProp_CurrentAmmo_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// Attributes\n" },
		{ "ModuleRelativePath", "Public/Actor/Item/Weapon/AS_Weapon.h" },
		{ "ToolTip", "Attributes" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Weapon_Statics::NewProp_CurrentAmmo = { "CurrentAmmo", "OnRep_CurrentAmmo", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Weapon, CurrentAmmo), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Weapon_Statics::NewProp_CurrentAmmo_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Weapon_Statics::NewProp_CurrentAmmo_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAS_Weapon_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Weapon_Statics::NewProp_CurrentAmmo,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAS_Weapon_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAS_Weapon>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAS_Weapon_Statics::ClassParams = {
		&UAS_Weapon::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAS_Weapon_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Weapon_Statics::PropPointers),
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAS_Weapon_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Weapon_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAS_Weapon()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAS_Weapon_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAS_Weapon, 861588);
	template<> SONICSIEGE_API UClass* StaticClass<UAS_Weapon>()
	{
		return UAS_Weapon::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAS_Weapon(Z_Construct_UClass_UAS_Weapon, &UAS_Weapon::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAS_Weapon"), false, nullptr, nullptr, nullptr);

	void UAS_Weapon::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_CurrentAmmo(TEXT("CurrentAmmo"));

		const bool bIsValid = true
			&& Name_CurrentAmmo == ClassReps[(int32)ENetFields_Private::CurrentAmmo].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UAS_Weapon"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAS_Weapon);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
