// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Interfaces/Interactable.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeInteractable() {}
// Cross Module References
	SONICSIEGE_API UEnum* Z_Construct_UEnum_SonicSiege_EDurationInteractEndReason();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UEnum* Z_Construct_UEnum_SonicSiege_EDetectType();
	SONICSIEGE_API UClass* Z_Construct_UClass_UInteractable_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UInteractable();
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
// End Cross Module References
	static UEnum* EDurationInteractEndReason_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SonicSiege_EDurationInteractEndReason, Z_Construct_UPackage__Script_SonicSiege(), TEXT("EDurationInteractEndReason"));
		}
		return Singleton;
	}
	template<> SONICSIEGE_API UEnum* StaticEnum<EDurationInteractEndReason>()
	{
		return EDurationInteractEndReason_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EDurationInteractEndReason(EDurationInteractEndReason_StaticEnum, TEXT("/Script/SonicSiege"), TEXT("EDurationInteractEndReason"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SonicSiege_EDurationInteractEndReason_Hash() { return 280104246U; }
	UEnum* Z_Construct_UEnum_SonicSiege_EDurationInteractEndReason()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EDurationInteractEndReason"), 0, Get_Z_Construct_UEnum_SonicSiege_EDurationInteractEndReason_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EDurationInteractEndReason::REASON_Unknown", (int64)EDurationInteractEndReason::REASON_Unknown },
				{ "EDurationInteractEndReason::REASON_InputRelease", (int64)EDurationInteractEndReason::REASON_InputRelease },
				{ "EDurationInteractEndReason::REASON_SweepMiss", (int64)EDurationInteractEndReason::REASON_SweepMiss },
				{ "EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap", (int64)EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap },
				{ "EDurationInteractEndReason::REASON_NewInteractionOverlapPriority", (int64)EDurationInteractEndReason::REASON_NewInteractionOverlapPriority },
				{ "EDurationInteractEndReason::REASON_AbilityCanceled", (int64)EDurationInteractEndReason::REASON_AbilityCanceled },
				{ "EDurationInteractEndReason::REASON_SuccessfulInteract", (int64)EDurationInteractEndReason::REASON_SuccessfulInteract },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/** Describes the reason the interact ended (Called from EndAbility()) */" },
				{ "ModuleRelativePath", "Public/Interfaces/Interactable.h" },
				{ "REASON_AbilityCanceled.Comment", "// Not currently being used. May add this feature in the future\n" },
				{ "REASON_AbilityCanceled.Name", "EDurationInteractEndReason::REASON_AbilityCanceled" },
				{ "REASON_AbilityCanceled.ToolTip", "Not currently being used. May add this feature in the future" },
				{ "REASON_CharacterLeftInteractionOverlap.Comment", "// Character's Interaction sweep missed. (Can't reach it)\n" },
				{ "REASON_CharacterLeftInteractionOverlap.Name", "EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap" },
				{ "REASON_CharacterLeftInteractionOverlap.ToolTip", "Character's Interaction sweep missed. (Can't reach it)" },
				{ "REASON_InputRelease.Comment", "// Used when the interaction ends for any unknown reason\n" },
				{ "REASON_InputRelease.Name", "EDurationInteractEndReason::REASON_InputRelease" },
				{ "REASON_InputRelease.ToolTip", "Used when the interaction ends for any unknown reason" },
				{ "REASON_NewInteractionOverlapPriority.Name", "EDurationInteractEndReason::REASON_NewInteractionOverlapPriority" },
				{ "REASON_SuccessfulInteract.Comment", "// Used whenever the ability gets canceled (most likely due to one end not having valid variables on activation)\n" },
				{ "REASON_SuccessfulInteract.Name", "EDurationInteractEndReason::REASON_SuccessfulInteract" },
				{ "REASON_SuccessfulInteract.ToolTip", "Used whenever the ability gets canceled (most likely due to one end not having valid variables on activation)" },
				{ "REASON_SweepMiss.Comment", "// Player let go of interact input\n" },
				{ "REASON_SweepMiss.Name", "EDurationInteractEndReason::REASON_SweepMiss" },
				{ "REASON_SweepMiss.ToolTip", "Player let go of interact input" },
				{ "REASON_Unknown.Name", "EDurationInteractEndReason::REASON_Unknown" },
				{ "ToolTip", "Describes the reason the interact ended (Called from EndAbility())" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SonicSiege,
				nullptr,
				"EDurationInteractEndReason",
				"EDurationInteractEndReason",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* EDetectType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SonicSiege_EDetectType, Z_Construct_UPackage__Script_SonicSiege(), TEXT("EDetectType"));
		}
		return Singleton;
	}
	template<> SONICSIEGE_API UEnum* StaticEnum<EDetectType>()
	{
		return EDetectType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EDetectType(EDetectType_StaticEnum, TEXT("/Script/SonicSiege"), TEXT("EDetectType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SonicSiege_EDetectType_Hash() { return 2044928248U; }
	UEnum* Z_Construct_UEnum_SonicSiege_EDetectType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EDetectType"), 0, Get_Z_Construct_UEnum_SonicSiege_EDetectType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EDetectType::DETECTTYPE_NotDetected", (int64)EDetectType::DETECTTYPE_NotDetected },
				{ "EDetectType::DETECTTYPE_Sweeped", (int64)EDetectType::DETECTTYPE_Sweeped },
				{ "EDetectType::DETECTTYPE_Overlapped", (int64)EDetectType::DETECTTYPE_Overlapped },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/** Describes the detection state */" },
				{ "DETECTTYPE_NotDetected.Name", "EDetectType::DETECTTYPE_NotDetected" },
				{ "DETECTTYPE_Overlapped.Comment", "// Character did sweep for an Interactable to find this\n" },
				{ "DETECTTYPE_Overlapped.Name", "EDetectType::DETECTTYPE_Overlapped" },
				{ "DETECTTYPE_Overlapped.ToolTip", "Character did sweep for an Interactable to find this" },
				{ "DETECTTYPE_Sweeped.Name", "EDetectType::DETECTTYPE_Sweeped" },
				{ "ModuleRelativePath", "Public/Interfaces/Interactable.h" },
				{ "ToolTip", "Describes the detection state" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SonicSiege,
				nullptr,
				"EDetectType",
				"EDetectType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void UInteractable::StaticRegisterNativesUInteractable()
	{
	}
	UClass* Z_Construct_UClass_UInteractable_NoRegister()
	{
		return UInteractable::StaticClass();
	}
	struct Z_Construct_UClass_UInteractable_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UInteractable_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UInteractable_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Interfaces/Interactable.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UInteractable_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<IInteractable>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UInteractable_Statics::ClassParams = {
		&UInteractable::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000840A1u,
		METADATA_PARAMS(Z_Construct_UClass_UInteractable_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UInteractable_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UInteractable()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UInteractable_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UInteractable, 3302049584);
	template<> SONICSIEGE_API UClass* StaticClass<UInteractable>()
	{
		return UInteractable::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UInteractable(Z_Construct_UClass_UInteractable, &UInteractable::StaticClass, TEXT("/Script/SonicSiege"), TEXT("UInteractable"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UInteractable);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
