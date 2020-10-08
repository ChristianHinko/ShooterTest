// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/AS_Health.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAS_Health() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Health_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Health();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
// End Cross Module References
	DEFINE_FUNCTION(UAS_Health::execOnRep_Health)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_Health(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAS_Health::execOnRep_MaxHealth)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_MaxHealth(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	void UAS_Health::StaticRegisterNativesUAS_Health()
	{
		UClass* Class = UAS_Health::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRep_Health", &UAS_Health::execOnRep_Health },
			{ "OnRep_MaxHealth", &UAS_Health::execOnRep_MaxHealth },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics
	{
		struct AS_Health_eventOnRep_Health_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Health_eventOnRep_Health_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Health, nullptr, "OnRep_Health", nullptr, nullptr, sizeof(AS_Health_eventOnRep_Health_Parms), Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Health_OnRep_Health()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Health_OnRep_Health_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics
	{
		struct AS_Health_eventOnRep_MaxHealth_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Health_eventOnRep_MaxHealth_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Health, nullptr, "OnRep_MaxHealth", nullptr, nullptr, sizeof(AS_Health_eventOnRep_MaxHealth_Parms), Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAS_Health_NoRegister()
	{
		return UAS_Health::StaticClass();
	}
	struct Z_Construct_UClass_UAS_Health_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
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
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAS_Health_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAS_Health_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAS_Health_OnRep_Health, "OnRep_Health" }, // 2449570133
		{ &Z_Construct_UFunction_UAS_Health_OnRep_MaxHealth, "OnRep_MaxHealth" }, // 2354529456
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Health_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Actor/AS_Health.h" },
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Health_Statics::NewProp_Healing_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "/** This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient\n" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
		{ "ToolTip", "This Healing attribute is just used for applying positive health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) // You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Health_Statics::NewProp_Healing = { "Healing", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Health, Healing), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Health_Statics::NewProp_Healing_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::NewProp_Healing_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Health_Statics::NewProp_Damage_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "/** This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) */// You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient\n" },
		{ "HideFromLevelInfos", "" },
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
		{ "ToolTip", "This Damage attribute is just used for applying negative health mods. Its not a 'persistent' attribute. It is a 'meta' attribute (gets set back to 0 after it modifies Health) // You can't make a GameplayEffect 'powered' by Damage (Its transient). HideFromLevelInfos makes the attribute transient" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Health_Statics::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Health, Damage), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Health_Statics::NewProp_Damage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::NewProp_Damage_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Health_Statics::NewProp_Health_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it\n" },
		{ "HideFromModifiers", "" },
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
		{ "ToolTip", "HideFromModifiers removes it from the GE dropdown menu so you can't accidently modify it" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Health_Statics::NewProp_Health = { "Health", "OnRep_Health", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Health, Health), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Health_Statics::NewProp_Health_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::NewProp_Health_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Health_Statics::NewProp_MaxHealth_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// Attributes\n" },
		{ "ModuleRelativePath", "Public/Actor/AS_Health.h" },
		{ "ToolTip", "Attributes" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Health_Statics::NewProp_MaxHealth = { "MaxHealth", "OnRep_MaxHealth", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Health, MaxHealth), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Health_Statics::NewProp_MaxHealth_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::NewProp_MaxHealth_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAS_Health_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Health_Statics::NewProp_Healing,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Health_Statics::NewProp_Damage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Health_Statics::NewProp_Health,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Health_Statics::NewProp_MaxHealth,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAS_Health_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAS_Health>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAS_Health_Statics::ClassParams = {
		&UAS_Health::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAS_Health_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::PropPointers),
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAS_Health_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Health_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAS_Health()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAS_Health_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAS_Health, 2114331276);
	template<> SONICSIEGE_API UClass* StaticClass<UAS_Health>()
	{
		return UAS_Health::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAS_Health(Z_Construct_UClass_UAS_Health, &UAS_Health::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAS_Health"), false, nullptr, nullptr, nullptr);

	void UAS_Health::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_MaxHealth(TEXT("MaxHealth"));
		static const FName Name_Health(TEXT("Health"));

		const bool bIsValid = true
			&& Name_MaxHealth == ClassReps[(int32)ENetFields_Private::MaxHealth].Property->GetFName()
			&& Name_Health == ClassReps[(int32)ENetFields_Private::Health].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UAS_Health"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAS_Health);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
