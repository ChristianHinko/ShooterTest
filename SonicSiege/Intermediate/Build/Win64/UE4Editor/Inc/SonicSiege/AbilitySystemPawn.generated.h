// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_AbilitySystemPawn_generated_h
#error "AbilitySystemPawn.generated.h already included, missing '#pragma once' in AbilitySystemPawn.h"
#endif
#define SONICSIEGE_AbilitySystemPawn_generated_h

#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAbilitySystemPawn(); \
	friend struct Z_Construct_UClass_AAbilitySystemPawn_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemPawn, ASSPawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemPawn) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemPawn*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		PawnAttributeSet=NETFIELD_REP_START, \
		NETFIELD_REP_END=PawnAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_INCLASS \
private: \
	static void StaticRegisterNativesAAbilitySystemPawn(); \
	friend struct Z_Construct_UClass_AAbilitySystemPawn_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemPawn, ASSPawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemPawn) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemPawn*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		PawnAttributeSet=NETFIELD_REP_START, \
		NETFIELD_REP_END=PawnAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAbilitySystemPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAbilitySystemPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemPawn(AAbilitySystemPawn&&); \
	NO_API AAbilitySystemPawn(const AAbilitySystemPawn&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemPawn(AAbilitySystemPawn&&); \
	NO_API AAbilitySystemPawn(const AAbilitySystemPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAbilitySystemPawn)


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__DefaultAttributeValuesEffect() { return STRUCT_OFFSET(AAbilitySystemPawn, DefaultAttributeValuesEffect); } \
	FORCEINLINE static uint32 __PPO__EffectsToApplyOnStartup() { return STRUCT_OFFSET(AAbilitySystemPawn, EffectsToApplyOnStartup); } \
	FORCEINLINE static uint32 __PPO__AIAbilitySystemComponentReplicationMode() { return STRUCT_OFFSET(AAbilitySystemPawn, AIAbilitySystemComponentReplicationMode); } \
	FORCEINLINE static uint32 __PPO__SSPlayerState() { return STRUCT_OFFSET(AAbilitySystemPawn, SSPlayerState); } \
	FORCEINLINE static uint32 __PPO__PlayerAbilitySystemComponent() { return STRUCT_OFFSET(AAbilitySystemPawn, PlayerAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__AIAbilitySystemComponent() { return STRUCT_OFFSET(AAbilitySystemPawn, AIAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__PawnAttributeSet() { return STRUCT_OFFSET(AAbilitySystemPawn, PawnAttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_68_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h_71_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class AAbilitySystemPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Pawn_AbilitySystemPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
