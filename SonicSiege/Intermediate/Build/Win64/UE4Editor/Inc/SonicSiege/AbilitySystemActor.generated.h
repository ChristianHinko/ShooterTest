// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_AbilitySystemActor_generated_h
#error "AbilitySystemActor.generated.h already included, missing '#pragma once' in AbilitySystemActor.h"
#endif
#define SONICSIEGE_AbilitySystemActor_generated_h

#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAbilitySystemActor(); \
	friend struct Z_Construct_UClass_AAbilitySystemActor_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemActor, ASSActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemActor) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemActor*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ActorAbilitySpecHandle=NETFIELD_REP_START, \
		ActorAttributeSet, \
		NETFIELD_REP_END=ActorAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_INCLASS \
private: \
	static void StaticRegisterNativesAAbilitySystemActor(); \
	friend struct Z_Construct_UClass_AAbilitySystemActor_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemActor, ASSActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemActor) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemActor*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ActorAbilitySpecHandle=NETFIELD_REP_START, \
		ActorAttributeSet, \
		NETFIELD_REP_END=ActorAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAbilitySystemActor(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAbilitySystemActor) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemActor); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemActor(AAbilitySystemActor&&); \
	NO_API AAbilitySystemActor(const AAbilitySystemActor&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemActor(AAbilitySystemActor&&); \
	NO_API AAbilitySystemActor(const AAbilitySystemActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemActor); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAbilitySystemActor)


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ActorAbilityTSub() { return STRUCT_OFFSET(AAbilitySystemActor, ActorAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__ActorAbilitySpecHandle() { return STRUCT_OFFSET(AAbilitySystemActor, ActorAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__DefaultAttributeValuesEffect() { return STRUCT_OFFSET(AAbilitySystemActor, DefaultAttributeValuesEffect); } \
	FORCEINLINE static uint32 __PPO__EffectsToApplyOnStartup() { return STRUCT_OFFSET(AAbilitySystemActor, EffectsToApplyOnStartup); } \
	FORCEINLINE static uint32 __PPO__ActorAbilitySystemComponentReplicationMode() { return STRUCT_OFFSET(AAbilitySystemActor, ActorAbilitySystemComponentReplicationMode); } \
	FORCEINLINE static uint32 __PPO__ActorAbilitySystemComponent() { return STRUCT_OFFSET(AAbilitySystemActor, ActorAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__ActorAttributeSet() { return STRUCT_OFFSET(AAbilitySystemActor, ActorAttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_38_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h_41_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class AAbilitySystemActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Actor_AbilitySystemActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
