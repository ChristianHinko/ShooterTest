// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayTag;
class UAbilitySystemComponent;
struct FGameplayTagContainer;
class UBAA_CooldownChanged;
#ifdef SONICSIEGE_BAA_CooldownChanged_generated_h
#error "BAA_CooldownChanged.generated.h already included, missing '#pragma once' in BAA_CooldownChanged.h"
#endif
#define SONICSIEGE_BAA_CooldownChanged_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_14_DELEGATE \
struct _Script_SonicSiege_eventOnCooldownChanged_Parms \
{ \
	FGameplayTag CooldownTag; \
	float TimeRemaining; \
	float Duration; \
}; \
static inline void FOnCooldownChanged_DelegateWrapper(const FMulticastScriptDelegate& OnCooldownChanged, FGameplayTag CooldownTag, float TimeRemaining, float Duration) \
{ \
	_Script_SonicSiege_eventOnCooldownChanged_Parms Parms; \
	Parms.CooldownTag=CooldownTag; \
	Parms.TimeRemaining=TimeRemaining; \
	Parms.Duration=Duration; \
	OnCooldownChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForCooldownChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForCooldownChange);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBAA_CooldownChanged(); \
	friend struct Z_Construct_UClass_UBAA_CooldownChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_CooldownChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_CooldownChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_INCLASS \
private: \
	static void StaticRegisterNativesUBAA_CooldownChanged(); \
	friend struct Z_Construct_UClass_UBAA_CooldownChanged_Statics; \
public: \
	DECLARE_CLASS(UBAA_CooldownChanged, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_CooldownChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_CooldownChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_CooldownChanged) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_CooldownChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_CooldownChanged); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_CooldownChanged(UBAA_CooldownChanged&&); \
	NO_API UBAA_CooldownChanged(const UBAA_CooldownChanged&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_CooldownChanged(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_CooldownChanged(UBAA_CooldownChanged&&); \
	NO_API UBAA_CooldownChanged(const UBAA_CooldownChanged&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_CooldownChanged); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_CooldownChanged); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_CooldownChanged)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ASC() { return STRUCT_OFFSET(UBAA_CooldownChanged, ASC); }


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_21_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UBAA_CooldownChanged>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_CooldownChanged_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
