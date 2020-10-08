// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UGameplayAbility;
class AAbilitySystemCharacter;
class UAT_Ticker;
#ifdef SONICSIEGE_AT_Ticker_generated_h
#error "AT_Ticker.generated.h already included, missing '#pragma once' in AT_Ticker.h"
#endif
#define SONICSIEGE_AT_Ticker_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_12_DELEGATE \
static inline void FDurationEnded_DelegateWrapper(const FMulticastScriptDelegate& DurationEnded) \
{ \
	DurationEnded.ProcessMulticastDelegate<UObject>(NULL); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_11_DELEGATE \
struct _Script_SonicSiege_eventTickDelegate_Parms \
{ \
	float DeltaTime; \
	float CurrentTime; \
	float TimeRemaining; \
}; \
static inline void FTickDelegate_DelegateWrapper(const FMulticastScriptDelegate& TickDelegate, float DeltaTime, float CurrentTime, float TimeRemaining) \
{ \
	_Script_SonicSiege_eventTickDelegate_Parms Parms; \
	Parms.DeltaTime=DeltaTime; \
	Parms.CurrentTime=CurrentTime; \
	Parms.TimeRemaining=TimeRemaining; \
	TickDelegate.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execTicker);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execTicker);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAT_Ticker(); \
	friend struct Z_Construct_UClass_UAT_Ticker_Statics; \
public: \
	DECLARE_CLASS(UAT_Ticker, USSAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_Ticker)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_INCLASS \
private: \
	static void StaticRegisterNativesUAT_Ticker(); \
	friend struct Z_Construct_UClass_UAT_Ticker_Statics; \
public: \
	DECLARE_CLASS(UAT_Ticker, USSAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_Ticker)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAT_Ticker(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_Ticker) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_Ticker); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_Ticker); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_Ticker(UAT_Ticker&&); \
	NO_API UAT_Ticker(const UAT_Ticker&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_Ticker(UAT_Ticker&&); \
	NO_API UAT_Ticker(const UAT_Ticker&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_Ticker); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_Ticker); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_Ticker)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_PRIVATE_PROPERTY_OFFSET
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_16_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UAT_Ticker>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_Ticker_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
