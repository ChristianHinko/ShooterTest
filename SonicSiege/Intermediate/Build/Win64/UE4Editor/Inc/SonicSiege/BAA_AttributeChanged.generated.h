// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayAttribute;
class UAbilitySystemComponent;
class UBAA_AttributeChanged;
#ifdef SONICSIEGE_BAA_AttributeChanged_generated_h
#error "BAA_AttributeChanged.generated.h already included, missing '#pragma once' in BAA_AttributeChanged.h"
#endif
#define SONICSIEGE_BAA_AttributeChanged_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_13_DELEGATE \
struct _Script_SonicSiege_eventOnAttributeChanged_Parms \
{ \
	FGameplayAttribute Attribute; \
	float NewValue; \
	float OldValue; \
}; \
static inline void FOnAttributeChanged_DelegateWrapper(const FMulticastScriptDelegate& OnAttributeChanged, FGameplayAttribute Attribute, float NewValue, float OldValue) \
{ \
	_Script_SonicSiege_eventOnAttributeChanged_Parms Parms; \
	Parms.Attribute=Attribute; \
	Parms.NewValue=NewValue; \
	Parms.OldValue=OldValue; \
	OnAttributeChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForAttributesChange); \
	DECLARE_FUNCTION(execListenForAttributeChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForAttributesChange); \
	DECLARE_FUNCTION(execListenForAttributeChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBAA_AttributeChanged(); \
	friend struct Z_Construct_UClass_UBAA_AttributeChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_AttributeChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_AttributeChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUBAA_AttributeChanged(); \
	friend struct Z_Construct_UClass_UBAA_AttributeChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_AttributeChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_AttributeChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_AttributeChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_AttributeChanged) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_AttributeChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_AttributeChanged); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_AttributeChanged(UBAA_AttributeChanged&&); \
	NO_API UBAA_AttributeChanged(const UBAA_AttributeChanged&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_AttributeChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_AttributeChanged(UBAA_AttributeChanged&&); \
	NO_API UBAA_AttributeChanged(const UBAA_AttributeChanged&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_AttributeChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_AttributeChanged); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_AttributeChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ASC() { return STRUCT_OFFSET(UBAA_AttributeChanged, ASC); }


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_20_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UBAA_AttributeChanged>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_AttributeChanged_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
