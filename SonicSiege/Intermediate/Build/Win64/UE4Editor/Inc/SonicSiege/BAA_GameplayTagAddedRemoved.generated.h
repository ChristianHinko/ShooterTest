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
class UBAA_GameplayTagAddedRemoved;
#ifdef SONICSIEGE_BAA_GameplayTagAddedRemoved_generated_h
#error "BAA_GameplayTagAddedRemoved.generated.h already included, missing '#pragma once' in BAA_GameplayTagAddedRemoved.h"
#endif
#define SONICSIEGE_BAA_GameplayTagAddedRemoved_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_14_DELEGATE \
struct _Script_SonicSiege_eventOnGameplayTagAddedRemoved_Parms \
{ \
	FGameplayTag Tag; \
}; \
static inline void FOnGameplayTagAddedRemoved_DelegateWrapper(const FMulticastScriptDelegate& OnGameplayTagAddedRemoved, FGameplayTag Tag) \
{ \
	_Script_SonicSiege_eventOnGameplayTagAddedRemoved_Parms Parms; \
	Parms.Tag=Tag; \
	OnGameplayTagAddedRemoved.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForGameplayTagAddedOrRemoved);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execEndTask); \
	DECLARE_FUNCTION(execListenForGameplayTagAddedOrRemoved);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBAA_GameplayTagAddedRemoved(); \
	friend struct Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics; \
public: \
	DECLARE_CLASS(UBAA_GameplayTagAddedRemoved, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_GameplayTagAddedRemoved)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_INCLASS \
private: \
	static void StaticRegisterNativesUBAA_GameplayTagAddedRemoved(); \
	friend struct Z_Construct_UClass_UBAA_GameplayTagAddedRemoved_Statics; \
public: \
	DECLARE_CLASS(UBAA_GameplayTagAddedRemoved, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UBAA_GameplayTagAddedRemoved)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_GameplayTagAddedRemoved(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_GameplayTagAddedRemoved) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_GameplayTagAddedRemoved); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_GameplayTagAddedRemoved); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_GameplayTagAddedRemoved(UBAA_GameplayTagAddedRemoved&&); \
	NO_API UBAA_GameplayTagAddedRemoved(const UBAA_GameplayTagAddedRemoved&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBAA_GameplayTagAddedRemoved(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBAA_GameplayTagAddedRemoved(UBAA_GameplayTagAddedRemoved&&); \
	NO_API UBAA_GameplayTagAddedRemoved(const UBAA_GameplayTagAddedRemoved&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBAA_GameplayTagAddedRemoved); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBAA_GameplayTagAddedRemoved); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBAA_GameplayTagAddedRemoved)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ASC() { return STRUCT_OFFSET(UBAA_GameplayTagAddedRemoved, ASC); }


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_21_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UBAA_GameplayTagAddedRemoved>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AsyncListeners_BAA_GameplayTagAddedRemoved_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
