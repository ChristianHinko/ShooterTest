// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayTag;
struct FActiveGameplayEffectHandle;
class UAbilitySystemComponent;
class UBAA_EffectStackChanged;
#ifdef SONICSIEGE_BAA_EffectStackChanged_generated_h
#error "BAA_EffectStackChanged.generated.h already included, missing '#pragma once' in BAA_EffectStackChanged.h"
#endif
#define SONICSIEGE_BAA_EffectStackChanged_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_13_DELEGATE \
struct _Script_SonicSiege_eventOnGameplayEffectStackChanged_Parms \
{ \
	FGameplayTag EffectGameplayTag; \
	FActiveGameplayEffectHandle Handle; \
	int32 NewStackCount; \
	int32 OldStackCount; \
}; \
static inline void FOnGameplayEffectStackChanged_DelegateWrapper(const FMulticastScriptDelegate& OnGameplayEffectStackChanged, FGameplayTag EffectGameplayTag, FActiveGameplayEffectHandle Handle, int32 NewStackCount, int32 OldStackCount) \
{ \
	_Script_SonicSiege_eventOnGameplayEffectStackChanged_Parms Parms; \
	Parms.EffectGameplayTag=EffectGameplayTag; \
	Parms.Handle=Handle; \
	Parms.NewStackCount=NewStackCount; \
	Parms.OldStackCount=OldStackCount; \
	OnGameplayEffectStackChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForGameplayEffectStackChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForGameplayEffectStackChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBAA_EffectStackChanged(); \
	friend struct Z_Construct_UClass_UBAA_EffectStackChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_EffectStackChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_EffectStackChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_INCLASS \
private: \
	static void StaticRegisterNativesUBAA_EffectStackChanged(); \
	friend struct Z_Construct_UClass_UBAA_EffectStackChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_EffectStackChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_EffectStackChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_EffectStackChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_EffectStackChanged) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_EffectStackChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_EffectStackChanged); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_EffectStackChanged(UBAA_EffectStackChanged&&); \
	NO_API UBAA_EffectStackChanged(const UBAA_EffectStackChanged&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_EffectStackChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_EffectStackChanged(UBAA_EffectStackChanged&&); \
	NO_API UBAA_EffectStackChanged(const UBAA_EffectStackChanged&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_EffectStackChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_EffectStackChanged); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_EffectStackChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ASC() { return STRUCT_OFFSET(UBAA_EffectStackChanged, ASC); }


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_20_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UBAA_EffectStackChanged>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_EffectStackChanged_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
