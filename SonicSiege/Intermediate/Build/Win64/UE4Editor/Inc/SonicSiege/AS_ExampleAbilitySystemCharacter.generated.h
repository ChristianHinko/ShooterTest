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
#ifdef SONICSIEGE_AS_ExampleAbilitySystemCharacter_generated_h
#error "AS_ExampleAbilitySystemCharacter.generated.h already included, missing '#pragma once' in AS_ExampleAbilitySystemCharacter.h"
#endif
#define SONICSIEGE_AS_ExampleAbilitySystemCharacter_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnRep_ExampleAttribute);


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnRep_ExampleAttribute);


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAS_ExampleAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(UAS_ExampleAbilitySystemCharacter, USSAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAS_ExampleAbilitySystemCharacter) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ExampleAttribute=NETFIELD_REP_START, \
		NETFIELD_REP_END=ExampleAttribute	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(UAS_ExampleAbilitySystemCharacter) \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUAS_ExampleAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_UAS_ExampleAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(UAS_ExampleAbilitySystemCharacter, USSAttributeSet, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAS_ExampleAbilitySystemCharacter) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ExampleAttribute=NETFIELD_REP_START, \
		NETFIELD_REP_END=ExampleAttribute	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override; \
private: \
	REPLICATED_BASE_CLASS(UAS_ExampleAbilitySystemCharacter) \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAS_ExampleAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAS_ExampleAbilitySystemCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAS_ExampleAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAS_ExampleAbilitySystemCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAS_ExampleAbilitySystemCharacter(UAS_ExampleAbilitySystemCharacter&&); \
	NO_API UAS_ExampleAbilitySystemCharacter(const UAS_ExampleAbilitySystemCharacter&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAS_ExampleAbilitySystemCharacter(UAS_ExampleAbilitySystemCharacter&&); \
	NO_API UAS_ExampleAbilitySystemCharacter(const UAS_ExampleAbilitySystemCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAS_ExampleAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAS_ExampleAbilitySystemCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAS_ExampleAbilitySystemCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_PRIVATE_PROPERTY_OFFSET
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_13_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UAS_ExampleAbilitySystemCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_AS_ExampleAbilitySystemCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
