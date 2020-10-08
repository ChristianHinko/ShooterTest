// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Actor/AbilitySystemActor.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAbilitySystemActor() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemActor_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemActor();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSActor();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Actor_NoRegister();
	GAMEPLAYABILITIES_API UEnum* Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemInterface_NoRegister();
// End Cross Module References
	void AAbilitySystemActor::StaticRegisterNativesAAbilitySystemActor()
	{
	}
	UClass* Z_Construct_UClass_AAbilitySystemActor_NoRegister()
	{
		return AAbilitySystemActor::StaticClass();
	}
	struct Z_Construct_UClass_AAbilitySystemActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ActorAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorAbilitySystemComponentReplicationMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_ActorAbilitySystemComponentReplicationMode;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ActorAbilitySystemComponentReplicationMode_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EffectsToApplyOnStartup_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_EffectsToApplyOnStartup;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_EffectsToApplyOnStartup_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultAttributeValuesEffect_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_DefaultAttributeValuesEffect;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActorAbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ActorAbilitySystemComponent;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAbilitySystemActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ASSActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * A Base GAS Actor class\n * \n * NOT TESTED YET!!!!!!!!!!!!!!!!!!\n * Code in this class is not just copied from the AbilitySystemCharacter class. The AbilitySystemActor class has a specific implementation that differs a little from the AbilitySystemCharacter class.\n *\n * Some tips:\n *\x09\x09""1) Levels\n *\x09\x09\x09- Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. since no player will ever possess this actor and the ASC always lives on here, you can put the GetLevel() function in this class.\n *\x09\x09""2) Abilities\n *\x09\x09\x09- If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n *\x09\x09""3) Attribute Sets\n *\x09\x09\x09- Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n *\x09\x09""4) Gameplay Effects\n *\x09\x09\x09- Every actor should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n *\x09\x09\x09- Any gameplay effects that this actor should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n *\x09\x09""5) Gmeplay Tags\n *\x09\x09\x09- Nothing special here\n *\x09\x09""6) Respawning\n *\x09\x09\x09- You can have a respawning system for this actor without destroying the actor or its ASC. Just reset its ASC using the custom function we wrote in the base ASC class FullReset() and also set bAttributesAndStartupEffectsInitialized to false so you can initialize again using SetupWithAbilitySystem(). This however assumes that all that needs to be reset for the actor is the stuff belonging to the ASC (ie. its AttributeSets). If more needs to be reset you can just add it\n */" },
		{ "IncludePath", "Actor/AbilitySystemActor.h" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "A Base GAS Actor class\n\nNOT TESTED YET!!!!!!!!!!!!!!!!!!\nCode in this class is not just copied from the AbilitySystemCharacter class. The AbilitySystemActor class has a specific implementation that differs a little from the AbilitySystemCharacter class.\n\nSome tips:\n            1) Levels\n                    - Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. since no player will ever possess this actor and the ASC always lives on here, you can put the GetLevel() function in this class.\n            2) Abilities\n                    - If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n            3) Attribute Sets\n                    - Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n            4) Gameplay Effects\n                    - Every actor should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n                    - Any gameplay effects that this actor should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n            5) Gmeplay Tags\n                    - Nothing special here\n            6) Respawning\n                    - You can have a respawning system for this actor without destroying the actor or its ASC. Just reset its ASC using the custom function we wrote in the base ASC class FullReset() and also set bAttributesAndStartupEffectsInitialized to false so you can initialize again using SetupWithAbilitySystem(). This however assumes that all that needs to be reset for the actor is the stuff belonging to the ASC (ie. its AttributeSets). If more needs to be reset you can just add it" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAttributeSet_MetaData[] = {
		{ "Comment", "/** Every actor will have this attribute set. This is useful because this gives you a place for common attributes that every actor should have. Children can make another attribute set specific to their actor (ie. UAS_MachineGun, UAS_PalmTree) */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "Every actor will have this attribute set. This is useful because this gives you a place for common attributes that every actor should have. Children can make another attribute set specific to their actor (ie. UAS_MachineGun, UAS_PalmTree)" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAttributeSet = { "ActorAttributeSet", nullptr, (EPropertyFlags)0x0040000000080028, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemActor, ActorAttributeSet), Z_Construct_UClass_UAS_Actor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/** Decide which replication mode you want for this Actor's AbilitySystemComponent. */" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "Decide which replication mode you want for this Actor's AbilitySystemComponent." },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode = { "ActorAbilitySystemComponentReplicationMode", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemActor, ActorAbilitySystemComponentReplicationMode), Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen) */" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen)" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemActor, EffectsToApplyOnStartup), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup_MetaData)) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup_Inner = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0004000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_DefaultAttributeValuesEffect_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** Default attributes values for a Actor on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Actor's starting attribute values will be on spawn */" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "Default attributes values for a Actor on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Actor's starting attribute values will be on spawn" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_DefaultAttributeValuesEffect = { "DefaultAttributeValuesEffect", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemActor, DefaultAttributeValuesEffect), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_DefaultAttributeValuesEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_DefaultAttributeValuesEffect_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponent_MetaData[] = {
		{ "Comment", "/*Replicated*/// Replicated can be helpful for debugging issues\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Actor/AbilitySystemActor.h" },
		{ "ToolTip", "Replicated// Replicated can be helpful for debugging issues" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponent = { "ActorAbilitySystemComponent", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemActor, ActorAbilitySystemComponent), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponent_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAbilitySystemActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponentReplicationMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_EffectsToApplyOnStartup_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_DefaultAttributeValuesEffect,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemActor_Statics::NewProp_ActorAbilitySystemComponent,
	};
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AAbilitySystemActor_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UAbilitySystemInterface_NoRegister, (int32)VTABLE_OFFSET(AAbilitySystemActor, IAbilitySystemInterface), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAbilitySystemActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAbilitySystemActor>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAbilitySystemActor_Statics::ClassParams = {
		&AAbilitySystemActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AAbilitySystemActor_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAbilitySystemActor()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAbilitySystemActor_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAbilitySystemActor, 876970729);
	template<> SONICSIEGE_API UClass* StaticClass<AAbilitySystemActor>()
	{
		return AAbilitySystemActor::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAbilitySystemActor(Z_Construct_UClass_AAbilitySystemActor, &AAbilitySystemActor::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AAbilitySystemActor"), false, nullptr, nullptr, nullptr);

	void AAbilitySystemActor::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_ActorAttributeSet(TEXT("ActorAttributeSet"));

		const bool bIsValid = true
			&& Name_ActorAttributeSet == ClassReps[(int32)ENetFields_Private::ActorAttributeSet].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AAbilitySystemActor"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAbilitySystemActor);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
