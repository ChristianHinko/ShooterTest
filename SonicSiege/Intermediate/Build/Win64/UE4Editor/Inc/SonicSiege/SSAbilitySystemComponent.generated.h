// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_SSAbilitySystemComponent_generated_h
#error "SSAbilitySystemComponent.generated.h already included, missing '#pragma once' in SSAbilitySystemComponent.h"
#endif
#define SONICSIEGE_SSAbilitySystemComponent_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSSAbilitySystemComponent(); \
	friend struct Z_Construct_UClass_USSAbilitySystemComponent_Statics; \
public: \
	DECLARE_CLASS(USSAbilitySystemComponent, UAbilitySystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(USSAbilitySystemComponent)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_INCLASS \
private: \
	static void StaticRegisterNativesUSSAbilitySystemComponent(); \
	friend struct Z_Construct_UClass_USSAbilitySystemComponent_Statics; \
public: \
	DECLARE_CLASS(USSAbilitySystemComponent, UAbilitySystemComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(USSAbilitySystemComponent)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USSAbilitySystemComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USSAbilitySystemComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USSAbilitySystemComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USSAbilitySystemComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USSAbilitySystemComponent(USSAbilitySystemComponent&&); \
	NO_API USSAbilitySystemComponent(const USSAbilitySystemComponent&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USSAbilitySystemComponent(USSAbilitySystemComponent&&); \
	NO_API USSAbilitySystemComponent(const USSAbilitySystemComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USSAbilitySystemComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USSAbilitySystemComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USSAbilitySystemComponent)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_PRIVATE_PROPERTY_OFFSET
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_51_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h_54_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class USSAbilitySystemComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_SSAbilitySystemComponent_h


#define FOREACH_ENUM_EABILITYINPUTID(op) \
	op(EAbilityInputID::None) \
	op(EAbilityInputID::Jump) \
	op(EAbilityInputID::Interact) \
	op(EAbilityInputID::Run) \
	op(EAbilityInputID::PrimaryFire) \
	op(EAbilityInputID::SecondaryFire) \
	op(EAbilityInputID::Reload) \
	op(EAbilityInputID::Crouch) \
	op(EAbilityInputID::SwitchWeapon) 

enum class EAbilityInputID : uint8;
template<> SONICSIEGE_API UEnum* StaticEnum<EAbilityInputID>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
