// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_SSPlayerState_generated_h
#error "SSPlayerState.generated.h already included, missing '#pragma once' in SSPlayerState.h"
#endif
#define SONICSIEGE_SSPlayerState_generated_h

#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASSPlayerState(); \
	friend struct Z_Construct_UClass_ASSPlayerState_Statics; \
public: \
	DECLARE_CLASS(ASSPlayerState, APlayerState, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSPlayerState) \
	virtual UObject* _getUObject() const override { return const_cast<ASSPlayerState*>(this); }


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_INCLASS \
private: \
	static void StaticRegisterNativesASSPlayerState(); \
	friend struct Z_Construct_UClass_ASSPlayerState_Statics; \
public: \
	DECLARE_CLASS(ASSPlayerState, APlayerState, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSPlayerState) \
	virtual UObject* _getUObject() const override { return const_cast<ASSPlayerState*>(this); }


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASSPlayerState(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASSPlayerState) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSPlayerState); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSPlayerState); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSPlayerState(ASSPlayerState&&); \
	NO_API ASSPlayerState(const ASSPlayerState&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSPlayerState(ASSPlayerState&&); \
	NO_API ASSPlayerState(const ASSPlayerState&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSPlayerState); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSPlayerState); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASSPlayerState)


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__SSAbilitySystemComponent() { return STRUCT_OFFSET(ASSPlayerState, SSAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__AttributeSet() { return STRUCT_OFFSET(ASSPlayerState, AttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_20_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class ASSPlayerState>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Player_SSPlayerState_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
