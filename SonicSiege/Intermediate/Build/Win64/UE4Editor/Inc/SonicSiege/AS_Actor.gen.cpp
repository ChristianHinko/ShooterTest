// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/AS_Actor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAS_Actor() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Actor_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Actor();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
// End Cross Module References
	DEFINE_FUNCTION(UAS_Actor::execOnRep_MyActorAttribute)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_MyActorAttribute(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	void UAS_Actor::StaticRegisterNativesUAS_Actor()
	{
		UClass* Class = UAS_Actor::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRep_MyActorAttribute", &UAS_Actor::execOnRep_MyActorAttribute },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics
	{
		struct AS_Actor_eventOnRep_MyActorAttribute_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_Actor_eventOnRep_MyActorAttribute_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::Function_MetaDataParams[] = {
		{ "Comment", "//These OnReps exist to make sure the GAS internal representations are synchronized properly during replication\n" },
		{ "ModuleRelativePath", "Public/Actor/AS_Actor.h" },
		{ "ToolTip", "These OnReps exist to make sure the GAS internal representations are synchronized properly during replication" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_Actor, nullptr, "OnRep_MyActorAttribute", nullptr, nullptr, sizeof(AS_Actor_eventOnRep_MyActorAttribute_Parms), Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAS_Actor_NoRegister()
	{
		return UAS_Actor::StaticClass();
	}
	struct Z_Construct_UClass_UAS_Actor_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MyActorAttribute_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MyActorAttribute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAS_Actor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAS_Actor_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAS_Actor_OnRep_MyActorAttribute, "OnRep_MyActorAttribute" }, // 1538606193
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Actor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * This attribute set will be on every actor that uses the ability system (using AbilitySystemActor) add universal actor attributes here\n */" },
		{ "IncludePath", "Actor/AS_Actor.h" },
		{ "ModuleRelativePath", "Public/Actor/AS_Actor.h" },
		{ "ToolTip", "This attribute set will be on every actor that uses the ability system (using AbilitySystemActor) add universal actor attributes here" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_Actor_Statics::NewProp_MyActorAttribute_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// Attributes\n" },
		{ "ModuleRelativePath", "Public/Actor/AS_Actor.h" },
		{ "ToolTip", "Attributes" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_Actor_Statics::NewProp_MyActorAttribute = { "MyActorAttribute", "OnRep_MyActorAttribute", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_Actor, MyActorAttribute), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_Actor_Statics::NewProp_MyActorAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Actor_Statics::NewProp_MyActorAttribute_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAS_Actor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_Actor_Statics::NewProp_MyActorAttribute,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAS_Actor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAS_Actor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAS_Actor_Statics::ClassParams = {
		&UAS_Actor::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAS_Actor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Actor_Statics::PropPointers),
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAS_Actor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_Actor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAS_Actor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAS_Actor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAS_Actor, 2642154775);
	template<> SONICSIEGE_API UClass* StaticClass<UAS_Actor>()
	{
		return UAS_Actor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAS_Actor(Z_Construct_UClass_UAS_Actor, &UAS_Actor::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAS_Actor"), false, nullptr, nullptr, nullptr);

	void UAS_Actor::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_MyActorAttribute(TEXT("MyActorAttribute"));

		const bool bIsValid = true
			&& Name_MyActorAttribute == ClassReps[(int32)ENetFields_Private::MyActorAttribute].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UAS_Actor"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAS_Actor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
