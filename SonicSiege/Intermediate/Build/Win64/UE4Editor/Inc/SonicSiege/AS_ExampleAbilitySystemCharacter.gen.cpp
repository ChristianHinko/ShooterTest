// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAS_ExampleAbilitySystemCharacter() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAttributeSet();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAttributeData();
// End Cross Module References
	DEFINE_FUNCTION(UAS_ExampleAbilitySystemCharacter::execOnRep_ExampleAttribute)
	{
		P_GET_STRUCT_REF(FGameplayAttributeData,Z_Param_Out_ServerBaseValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnRep_ExampleAttribute(Z_Param_Out_ServerBaseValue);
		P_NATIVE_END;
	}
	void UAS_ExampleAbilitySystemCharacter::StaticRegisterNativesUAS_ExampleAbilitySystemCharacter()
	{
		UClass* Class = UAS_ExampleAbilitySystemCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnRep_ExampleAttribute", &UAS_ExampleAbilitySystemCharacter::execOnRep_ExampleAttribute },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics
	{
		struct AS_ExampleAbilitySystemCharacter_eventOnRep_ExampleAttribute_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::NewProp_ServerBaseValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::NewProp_ServerBaseValue = { "ServerBaseValue", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AS_ExampleAbilitySystemCharacter_eventOnRep_ExampleAttribute_Parms, ServerBaseValue), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::NewProp_ServerBaseValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::NewProp_ServerBaseValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::NewProp_ServerBaseValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter, nullptr, "OnRep_ExampleAttribute", nullptr, nullptr, sizeof(AS_ExampleAbilitySystemCharacter_eventOnRep_ExampleAttribute_Parms), Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_NoRegister()
	{
		return UAS_ExampleAbilitySystemCharacter::StaticClass();
	}
	struct Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExampleAttribute_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ExampleAttribute;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USSAttributeSet,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAS_ExampleAbilitySystemCharacter_OnRep_ExampleAttribute, "OnRep_ExampleAttribute" }, // 647336711
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h" },
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::NewProp_ExampleAttribute_MetaData[] = {
		{ "Category", "Attributes" },
		{ "Comment", "// Attributes\n" },
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/AS_ExampleAbilitySystemCharacter.h" },
		{ "ToolTip", "Attributes" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::NewProp_ExampleAttribute = { "ExampleAttribute", "OnRep_ExampleAttribute", (EPropertyFlags)0x0010000100000034, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAS_ExampleAbilitySystemCharacter, ExampleAttribute), Z_Construct_UScriptStruct_FGameplayAttributeData, METADATA_PARAMS(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::NewProp_ExampleAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::NewProp_ExampleAttribute_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::NewProp_ExampleAttribute,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAS_ExampleAbilitySystemCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::ClassParams = {
		&UAS_ExampleAbilitySystemCharacter::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::PropPointers),
		0,
		0x003000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAS_ExampleAbilitySystemCharacter, 2673705232);
	template<> SONICSIEGE_API UClass* StaticClass<UAS_ExampleAbilitySystemCharacter>()
	{
		return UAS_ExampleAbilitySystemCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAS_ExampleAbilitySystemCharacter(Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter, &UAS_ExampleAbilitySystemCharacter::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UAS_ExampleAbilitySystemCharacter"), false, nullptr, nullptr, nullptr);

	void UAS_ExampleAbilitySystemCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_ExampleAttribute(TEXT("ExampleAttribute"));

		const bool bIsValid = true
			&& Name_ExampleAttribute == ClassReps[(int32)ENetFields_Private::ExampleAttribute].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in UAS_ExampleAbilitySystemCharacter"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAS_ExampleAbilitySystemCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
