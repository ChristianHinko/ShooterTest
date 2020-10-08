// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayAbilityTargetDataHandle;
#ifdef SONICSIEGE_GA_Fire_generated_h
#error "GA_Fire.generated.h already included, missing '#pragma once' in GA_Fire.h"
#endif
#define SONICSIEGE_GA_Fire_generated_h

#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnCancelled); \
	DECLARE_FUNCTION(execOnValidData);


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnCancelled); \
	DECLARE_FUNCTION(execOnValidData);


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGA_Fire(); \
	friend struct Z_Construct_UClass_UGA_Fire_Statics; \
public: \
	DECLARE_CLASS(UGA_Fire, USSGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UGA_Fire)


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_INCLASS \
private: \
	static void StaticRegisterNativesUGA_Fire(); \
	friend struct Z_Construct_UClass_UGA_Fire_Statics; \
public: \
	DECLARE_CLASS(UGA_Fire, USSGameplayAbility, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UGA_Fire)


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGA_Fire(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGA_Fire) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGA_Fire); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGA_Fire); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGA_Fire(UGA_Fire&&); \
	NO_API UGA_Fire(const UGA_Fire&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGA_Fire(UGA_Fire&&); \
	NO_API UGA_Fire(const UGA_Fire&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGA_Fire); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGA_Fire); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGA_Fire)


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__FireEffectTSub() { return STRUCT_OFFSET(UGA_Fire, FireEffectTSub); } \
	FORCEINLINE static uint32 __PPO__BulletHitEffectTSub() { return STRUCT_OFFSET(UGA_Fire, BulletHitEffectTSub); } \
	FORCEINLINE static uint32 __PPO__SourceWeapon() { return STRUCT_OFFSET(UGA_Fire, SourceWeapon); } \
	FORCEINLINE static uint32 __PPO__BulletTraceTargetActor() { return STRUCT_OFFSET(UGA_Fire, BulletTraceTargetActor); }


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_15_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UGA_Fire>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Abilities_GA_Fire_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
