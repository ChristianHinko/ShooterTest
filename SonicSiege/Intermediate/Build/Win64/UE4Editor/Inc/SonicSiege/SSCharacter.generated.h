// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_SSCharacter_generated_h
#error "SSCharacter.generated.h already included, missing '#pragma once' in SSCharacter.h"
#endif
#define SONICSIEGE_SSCharacter_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASSCharacter(); \
	friend struct Z_Construct_UClass_ASSCharacter_Statics; \
public: \
	DECLARE_CLASS(ASSCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_INCLASS \
private: \
	static void StaticRegisterNativesASSCharacter(); \
	friend struct Z_Construct_UClass_ASSCharacter_Statics; \
public: \
	DECLARE_CLASS(ASSCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASSCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASSCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSCharacter(ASSCharacter&&); \
	NO_API ASSCharacter(const ASSCharacter&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSCharacter(ASSCharacter&&); \
	NO_API ASSCharacter(const ASSCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSCharacter); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASSCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__POVMesh() { return STRUCT_OFFSET(ASSCharacter, POVMesh); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(ASSCharacter, FollowCamera); } \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(ASSCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__SSCharacterMovementComponent() { return STRUCT_OFFSET(ASSCharacter, SSCharacterMovementComponent); }


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_19_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class ASSCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_SSCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
