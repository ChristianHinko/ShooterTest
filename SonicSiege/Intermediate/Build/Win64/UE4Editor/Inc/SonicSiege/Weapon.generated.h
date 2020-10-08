// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_Weapon_generated_h
#error "Weapon.generated.h already included, missing '#pragma once' in Weapon.h"
#endif
#define SONICSIEGE_Weapon_generated_h

#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAWeapon(); \
	friend struct Z_Construct_UClass_AWeapon_Statics; \
public: \
	DECLARE_CLASS(AWeapon, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AWeapon) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		FireAbilitySpecHandle=NETFIELD_REP_START, \
		NETFIELD_REP_END=FireAbilitySpecHandle	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_INCLASS \
private: \
	static void StaticRegisterNativesAWeapon(); \
	friend struct Z_Construct_UClass_AWeapon_Statics; \
public: \
	DECLARE_CLASS(AWeapon, AItem, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AWeapon) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		FireAbilitySpecHandle=NETFIELD_REP_START, \
		NETFIELD_REP_END=FireAbilitySpecHandle	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AWeapon(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AWeapon) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapon); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapon(AWeapon&&); \
	NO_API AWeapon(const AWeapon&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AWeapon(AWeapon&&); \
	NO_API AWeapon(const AWeapon&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AWeapon); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AWeapon); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AWeapon)


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__FireAbilityTSub() { return STRUCT_OFFSET(AWeapon, FireAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__FireAbilitySpecHandle() { return STRUCT_OFFSET(AWeapon, FireAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__WeaponAttributeSet() { return STRUCT_OFFSET(AWeapon, WeaponAttributeSet); } \
	FORCEINLINE static uint32 __PPO__BulletTraceTargetActorTSub() { return STRUCT_OFFSET(AWeapon, BulletTraceTargetActorTSub); } \
	FORCEINLINE static uint32 __PPO__BulletTraceTargetActor() { return STRUCT_OFFSET(AWeapon, BulletTraceTargetActor); }


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_15_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class AWeapon>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Actor_Item_Weapon_Weapon_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
