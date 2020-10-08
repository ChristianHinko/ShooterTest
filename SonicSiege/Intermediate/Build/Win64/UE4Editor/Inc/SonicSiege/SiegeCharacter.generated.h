// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef SONICSIEGE_SiegeCharacter_generated_h
#error "SiegeCharacter.generated.h already included, missing '#pragma once' in SiegeCharacter.h"
#endif
#define SONICSIEGE_SiegeCharacter_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnComponentEndOverlapCharacterCapsule); \
	DECLARE_FUNCTION(execOnComponentBeginOverlapCharacterCapsule);


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnComponentEndOverlapCharacterCapsule); \
	DECLARE_FUNCTION(execOnComponentBeginOverlapCharacterCapsule);


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASiegeCharacter(); \
	friend struct Z_Construct_UClass_ASiegeCharacter_Statics; \
public: \
	DECLARE_CLASS(ASiegeCharacter, AAbilitySystemCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASiegeCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_INCLASS \
private: \
	static void StaticRegisterNativesASiegeCharacter(); \
	friend struct Z_Construct_UClass_ASiegeCharacter_Statics; \
public: \
	DECLARE_CLASS(ASiegeCharacter, AAbilitySystemCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASiegeCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASiegeCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASiegeCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASiegeCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASiegeCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASiegeCharacter(ASiegeCharacter&&); \
	NO_API ASiegeCharacter(const ASiegeCharacter&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASiegeCharacter(ASiegeCharacter&&); \
	NO_API ASiegeCharacter(const ASiegeCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASiegeCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASiegeCharacter); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASiegeCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__InteractSweepDistance() { return STRUCT_OFFSET(ASiegeCharacter, InteractSweepDistance); } \
	FORCEINLINE static uint32 __PPO__InteractSweepRadius() { return STRUCT_OFFSET(ASiegeCharacter, InteractSweepRadius); }


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_16_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class ASiegeCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_SiegeCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
