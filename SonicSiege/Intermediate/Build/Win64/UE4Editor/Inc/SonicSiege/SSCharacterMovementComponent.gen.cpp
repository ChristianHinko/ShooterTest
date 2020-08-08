// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/SSCharacterMovementComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSCharacterMovementComponent() {}
// Cross Module References
	SONICSIEGE_API UEnum* Z_Construct_UEnum_SonicSiege_ECustomMovementMode();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSCharacterMovementComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSCharacterMovementComponent();
	ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
// End Cross Module References
	static UEnum* ECustomMovementMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SonicSiege_ECustomMovementMode, Z_Construct_UPackage__Script_SonicSiege(), TEXT("ECustomMovementMode"));
		}
		return Singleton;
	}
	template<> SONICSIEGE_API UEnum* StaticEnum<ECustomMovementMode>()
	{
		return ECustomMovementMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECustomMovementMode(ECustomMovementMode_StaticEnum, TEXT("/Script/SonicSiege"), TEXT("ECustomMovementMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SonicSiege_ECustomMovementMode_Hash() { return 1783398762U; }
	UEnum* Z_Construct_UEnum_SonicSiege_ECustomMovementMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECustomMovementMode"), 0, Get_Z_Construct_UEnum_SonicSiege_ECustomMovementMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CMOVE_None", (int64)CMOVE_None },
				{ "CMOVE_InfiniteAngleWalking", (int64)CMOVE_InfiniteAngleWalking },
				{ "CMOVE_MAX", (int64)CMOVE_MAX },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CMOVE_InfiniteAngleWalking.Comment", "/** Walking on a surface with the ability to walk up any slope angle */" },
				{ "CMOVE_InfiniteAngleWalking.DisplayName", "InfiniteAngleWalking" },
				{ "CMOVE_InfiniteAngleWalking.Name", "CMOVE_InfiniteAngleWalking" },
				{ "CMOVE_InfiniteAngleWalking.ToolTip", "Walking on a surface with the ability to walk up any slope angle" },
				{ "CMOVE_MAX.Hidden", "" },
				{ "CMOVE_MAX.Name", "CMOVE_MAX" },
				{ "CMOVE_None.Comment", "/** None (custom movement is disabled). */" },
				{ "CMOVE_None.DisplayName", "None" },
				{ "CMOVE_None.Name", "CMOVE_None" },
				{ "CMOVE_None.ToolTip", "None (custom movement is disabled)." },
				{ "Comment", "/**\n * Custom movement modes. used when MovementMode == MOVE_Custom\n */// should we make this an enum class?\n" },
				{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
				{ "ToolTip", "Custom movement modes. used when MovementMode == MOVE_Custom\n // should we make this an enum class?" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SonicSiege,
				nullptr,
				"ECustomMovementMode",
				"ECustomMovementMode",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	DEFINE_FUNCTION(USSCharacterMovementComponent::execOnOwningCharacterSetupWithAbilitySystemFinished)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOwningCharacterSetupWithAbilitySystemFinished();
		P_NATIVE_END;
	}
	void USSCharacterMovementComponent::StaticRegisterNativesUSSCharacterMovementComponent()
	{
		UClass* Class = USSCharacterMovementComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnOwningCharacterSetupWithAbilitySystemFinished", &USSCharacterMovementComponent::execOnOwningCharacterSetupWithAbilitySystemFinished },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USSCharacterMovementComponent, nullptr, "OnOwningCharacterSetupWithAbilitySystemFinished", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USSCharacterMovementComponent_NoRegister()
	{
		return USSCharacterMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_USSCharacterMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OwnerSSASC_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwnerSSASC;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OwnerAbilitySystemCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwnerAbilitySystemCharacter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSCharacterMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USSCharacterMovementComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished, "OnOwningCharacterSetupWithAbilitySystemFinished" }, // 628393321
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Our custom base implementation of the CMC\n */" },
		{ "IncludePath", "Character/SSCharacterMovementComponent.h" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
		{ "ToolTip", "Our custom base implementation of the CMC" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet = { "CharacterAttributeSet", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, CharacterAttributeSet), Z_Construct_UClass_UAS_Character_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC = { "OwnerSSASC", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, OwnerSSASC), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter = { "OwnerAbilitySystemCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, OwnerAbilitySystemCharacter), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSCharacterMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSCharacterMovementComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::ClassParams = {
		&USSCharacterMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSCharacterMovementComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSCharacterMovementComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSCharacterMovementComponent, 369263381);
	template<> SONICSIEGE_API UClass* StaticClass<USSCharacterMovementComponent>()
	{
		return USSCharacterMovementComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSCharacterMovementComponent(Z_Construct_UClass_USSCharacterMovementComponent, &USSCharacterMovementComponent::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSCharacterMovementComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSCharacterMovementComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
