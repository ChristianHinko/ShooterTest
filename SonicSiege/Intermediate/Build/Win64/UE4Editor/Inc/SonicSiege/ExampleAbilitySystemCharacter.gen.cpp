// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExampleAbilitySystemCharacter() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AExampleAbilitySystemCharacter_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AExampleAbilitySystemCharacter();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_NoRegister();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility_NoRegister();
// End Cross Module References
	void AExampleAbilitySystemCharacter::StaticRegisterNativesAExampleAbilitySystemCharacter()
	{
	}
	UClass* Z_Construct_UClass_AExampleAbilitySystemCharacter_NoRegister()
	{
		return AExampleAbilitySystemCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExampleAbilitySystemCharacterAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ExampleAbilitySystemCharacterAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExampleAbilitySpecHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ExampleAbilitySpecHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ExampleAbilityTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_ExampleAbilityTSub;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AAbilitySystemCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h" },
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySystemCharacterAttributeSet_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySystemCharacterAttributeSet = { "ExampleAbilitySystemCharacterAttributeSet", nullptr, (EPropertyFlags)0x0020080000080028, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilitySystemCharacterAttributeSet), Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySystemCharacterAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySystemCharacterAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySpecHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySpecHandle = { "ExampleAbilitySpecHandle", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilitySpecHandle), Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle, METADATA_PARAMS(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySpecHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySpecHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilityTSub_MetaData[] = {
		{ "Category", "AbilitySystem|Abilities" },
		{ "ModuleRelativePath", "Public/Character/Characters/ExampleAbilitySystemCharacter/ExampleAbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilityTSub = { "ExampleAbilityTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilityTSub), Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilityTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilityTSub_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySystemCharacterAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilitySpecHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::NewProp_ExampleAbilityTSub,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AExampleAbilitySystemCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::ClassParams = {
		&AExampleAbilitySystemCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AExampleAbilitySystemCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AExampleAbilitySystemCharacter, 84003826);
	template<> SONICSIEGE_API UClass* StaticClass<AExampleAbilitySystemCharacter>()
	{
		return AExampleAbilitySystemCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AExampleAbilitySystemCharacter(Z_Construct_UClass_AExampleAbilitySystemCharacter, &AExampleAbilitySystemCharacter::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AExampleAbilitySystemCharacter"), false, nullptr, nullptr, nullptr);

	void AExampleAbilitySystemCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_ExampleAbilitySpecHandle(TEXT("ExampleAbilitySpecHandle"));
		static const FName Name_ExampleAbilitySystemCharacterAttributeSet(TEXT("ExampleAbilitySystemCharacterAttributeSet"));

		const bool bIsValid = true
			&& Name_ExampleAbilitySpecHandle == ClassReps[(int32)ENetFields_Private::ExampleAbilitySpecHandle].Property->GetFName()
			&& Name_ExampleAbilitySystemCharacterAttributeSet == ClassReps[(int32)ENetFields_Private::ExampleAbilitySystemCharacterAttributeSet].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AExampleAbilitySystemCharacter"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AExampleAbilitySystemCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
