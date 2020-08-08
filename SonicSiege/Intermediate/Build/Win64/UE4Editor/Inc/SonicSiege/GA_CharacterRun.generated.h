// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_GA_CharacterRun_generated_h
#error "GA_CharacterRun.generated.h already included, missing '#pragma once' in GA_CharacterRun.h"
#endif
#define SONICSIEGE_GA_CharacterRun_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRelease); \
	DECLARE_FUNCTION(execOnTimerTick);


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRelease); \
	DECLARE_FUNCTION(execOnTimerTick);


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGA_CharacterRun(); \
	friend struct Z_Construct_UClass_UGA_CharacterRun_Statics; \
public: \
	DECLARE_CLASS(UGA_CharacterRun, USSGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UGA_CharacterRun)


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_INCLASS \
private: \
	static void StaticRegisterNativesUGA_CharacterRun(); \
	friend struct Z_Construct_UClass_UGA_CharacterRun_Statics; \
public: \
	DECLARE_CLASS(UGA_CharacterRun, USSGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UGA_CharacterRun)


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGA_CharacterRun(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGA_CharacterRun) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGA_CharacterRun); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGA_CharacterRun); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGA_CharacterRun(UGA_CharacterRun&&); \
	NO_API UGA_CharacterRun(const UGA_CharacterRun&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGA_CharacterRun(UGA_CharacterRun&&); \
	NO_API UGA_CharacterRun(const UGA_CharacterRun&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGA_CharacterRun); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGA_CharacterRun); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGA_CharacterRun)


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__StaminaDrainEffectTSub() { return STRUCT_OFFSET(UGA_CharacterRun, StaminaDrainEffectTSub); } \
	FORCEINLINE static uint32 __PPO__GASCharacter() { return STRUCT_OFFSET(UGA_CharacterRun, GASCharacter); }


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_18_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UGA_CharacterRun>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_Abilities_GA_CharacterRun_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
