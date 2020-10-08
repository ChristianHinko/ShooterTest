// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_SSCharacterMovementComponent_generated_h
#error "SSCharacterMovementComponent.generated.h already included, missing '#pragma once' in SSCharacterMovementComponent.h"
#endif
#define SONICSIEGE_SSCharacterMovementComponent_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_RPC_WRAPPERS \
	virtual void SSClientAdjustPosition_Implementation(bool bAdjustedCanRun); \
 \
	DECLARE_FUNCTION(execSSClientAdjustPosition); \
	DECLARE_FUNCTION(execOnOwningCharacterSetupWithAbilitySystemFinished);


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSSClientAdjustPosition); \
	DECLARE_FUNCTION(execOnOwningCharacterSetupWithAbilitySystemFinished);


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_EVENT_PARMS \
	struct SSCharacterMovementComponent_eventSSClientAdjustPosition_Parms \
	{ \
		bool bAdjustedCanRun; \
	};


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_CALLBACK_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSSCharacterMovementComponent(); \
	friend struct Z_Construct_UClass_USSCharacterMovementComponent_Statics; \
public: \
	DECLARE_CLASS(USSCharacterMovementComponent, UCharacterMovementComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(USSCharacterMovementComponent)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_INCLASS \
private: \
	static void StaticRegisterNativesUSSCharacterMovementComponent(); \
	friend struct Z_Construct_UClass_USSCharacterMovementComponent_Statics; \
public: \
	DECLARE_CLASS(USSCharacterMovementComponent, UCharacterMovementComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(USSCharacterMovementComponent)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USSCharacterMovementComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USSCharacterMovementComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USSCharacterMovementComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USSCharacterMovementComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USSCharacterMovementComponent(USSCharacterMovementComponent&&); \
	NO_API USSCharacterMovementComponent(const USSCharacterMovementComponent&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USSCharacterMovementComponent(USSCharacterMovementComponent&&); \
	NO_API USSCharacterMovementComponent(const USSCharacterMovementComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USSCharacterMovementComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USSCharacterMovementComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USSCharacterMovementComponent)


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__OwnerAbilitySystemCharacter() { return STRUCT_OFFSET(USSCharacterMovementComponent, OwnerAbilitySystemCharacter); } \
	FORCEINLINE static uint32 __PPO__OwnerSSASC() { return STRUCT_OFFSET(USSCharacterMovementComponent, OwnerSSASC); } \
	FORCEINLINE static uint32 __PPO__CharacterAttributeSet() { return STRUCT_OFFSET(USSCharacterMovementComponent, CharacterAttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_103_PROLOG \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_EVENT_PARMS


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_CALLBACK_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_CALLBACK_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h_106_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class USSCharacterMovementComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_SSCharacterMovementComponent_h


#define FOREACH_ENUM_ECUSTOMMOVEMENTMODE(op) \
	op(CMOVE_None) \
	op(CMOVE_InfiniteAngleWalking) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
