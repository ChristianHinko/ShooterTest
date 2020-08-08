// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "Net/Core/PushModel/PushModelMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayAttributeData;
#ifdef SONICSIEGE_AS_Character_generated_h
#error "AS_Character.generated.h already included, missing '#pragma once' in AS_Character.h"
#endif
#define SONICSIEGE_AS_Character_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRep_Stamina); \
	DECLARE_FUNCTION(execOnRep_MaxStamina); \
	DECLARE_FUNCTION(execOnRep_Health); \
	DECLARE_FUNCTION(execOnRep_MaxHealth); \
	DECLARE_FUNCTION(execOnRep_RunAccelaration); \
	DECLARE_FUNCTION(execOnRep_RunSpeed); \
	DECLARE_FUNCTION(execOnRep_WalkAcceleration); \
	DECLARE_FUNCTION(execOnRep_WalkSpeed);


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRep_Stamina); \
	DECLARE_FUNCTION(execOnRep_MaxStamina); \
	DECLARE_FUNCTION(execOnRep_Health); \
	DECLARE_FUNCTION(execOnRep_MaxHealth); \
	DECLARE_FUNCTION(execOnRep_RunAccelaration); \
	DECLARE_FUNCTION(execOnRep_RunSpeed); \
	DECLARE_FUNCTION(execOnRep_WalkAcceleration); \
	DECLARE_FUNCTION(execOnRep_WalkSpeed);


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAS_Character(); \
	friend struct Z_Construct_UClass_UAS_Character_Statics; \
public: \
	DECLARE_CLASS(UAS_Character, USSAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAS_Character) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		WalkSpeed=NETFIELD_REP_START, \
		WalkAcceleration, \
		RunSpeed, \
		RunAccelaration, \
		MaxHealth, \
		Health, \
		MaxStamina, \
		Stamina, \
		NETFIELD_REP_END=Stamina	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(UAS_Character) \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_INCLASS \
private: \
	static void StaticRegisterNativesUAS_Character(); \
	friend struct Z_Construct_UClass_UAS_Character_Statics; \
public: \
	DECLARE_CLASS(UAS_Character, USSAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAS_Character) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		WalkSpeed=NETFIELD_REP_START, \
		WalkAcceleration, \
		RunSpeed, \
		RunAccelaration, \
		MaxHealth, \
		Health, \
		MaxStamina, \
		Stamina, \
		NETFIELD_REP_END=Stamina	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(UAS_Character) \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAS_Character(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAS_Character) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAS_Character); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAS_Character); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAS_Character(UAS_Character&&); \
	NO_API UAS_Character(const UAS_Character&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAS_Character(UAS_Character&&); \
	NO_API UAS_Character(const UAS_Character&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAS_Character); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAS_Character); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAS_Character)


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_PRIVATE_PROPERTY_OFFSET
#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_17_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UAS_Character>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_AS_Character_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
