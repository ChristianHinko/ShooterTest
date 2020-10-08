// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGameplayTag;
struct FGameplayEventData;
class UGameplayAbility;
class UAnimMontage;
struct FGameplayTagContainer;
class UAT_PlayMontageAndWaitForEvent;
#ifdef SONICSIEGE_AT_PlayMontageAndWaitForEvent_generated_h
#error "AT_PlayMontageAndWaitForEvent.generated.h already included, missing '#pragma once' in AT_PlayMontageAndWaitForEvent.h"
#endif
#define SONICSIEGE_AT_PlayMontageAndWaitForEvent_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_16_DELEGATE \
struct _Script_SonicSiege_eventGDPlayMontageAndWaitForEventDelegate_Parms \
{ \
	FGameplayTag EventTag; \
	FGameplayEventData EventData; \
}; \
static inline void FGDPlayMontageAndWaitForEventDelegate_DelegateWrapper(const FMulticastScriptDelegate& GDPlayMontageAndWaitForEventDelegate, FGameplayTag EventTag, FGameplayEventData EventData) \
{ \
	_Script_SonicSiege_eventGDPlayMontageAndWaitForEventDelegate_Parms Parms; \
	Parms.EventTag=EventTag; \
	Parms.EventData=EventData; \
	GDPlayMontageAndWaitForEventDelegate.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPlayMontageAndWaitForEvent);


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPlayMontageAndWaitForEvent);


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAT_PlayMontageAndWaitForEvent(); \
	friend struct Z_Construct_UClass_UAT_PlayMontageAndWaitForEvent_Statics; \
public: \
	DECLARE_CLASS(UAT_PlayMontageAndWaitForEvent, UAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_PlayMontageAndWaitForEvent)


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUAT_PlayMontageAndWaitForEvent(); \
	friend struct Z_Construct_UClass_UAT_PlayMontageAndWaitForEvent_Statics; \
public: \
	DECLARE_CLASS(UAT_PlayMontageAndWaitForEvent, UAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_PlayMontageAndWaitForEvent)


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAT_PlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_PlayMontageAndWaitForEvent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_PlayMontageAndWaitForEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_PlayMontageAndWaitForEvent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_PlayMontageAndWaitForEvent(UAT_PlayMontageAndWaitForEvent&&); \
	NO_API UAT_PlayMontageAndWaitForEvent(const UAT_PlayMontageAndWaitForEvent&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_PlayMontageAndWaitForEvent(UAT_PlayMontageAndWaitForEvent&&); \
	NO_API UAT_PlayMontageAndWaitForEvent(const UAT_PlayMontageAndWaitForEvent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_PlayMontageAndWaitForEvent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_PlayMontageAndWaitForEvent); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_PlayMontageAndWaitForEvent)


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__MontageToPlay() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, MontageToPlay); } \
	FORCEINLINE static uint32 __PPO__EventTags() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, EventTags); } \
	FORCEINLINE static uint32 __PPO__Rate() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, Rate); } \
	FORCEINLINE static uint32 __PPO__StartSection() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, StartSection); } \
	FORCEINLINE static uint32 __PPO__AnimRootMotionTranslationScale() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, AnimRootMotionTranslationScale); } \
	FORCEINLINE static uint32 __PPO__bStopWhenAbilityEnds() { return STRUCT_OFFSET(UAT_PlayMontageAndWaitForEvent, bStopWhenAbilityEnds); }


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_25_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UAT_PlayMontageAndWaitForEvent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_AbilityTasks_AT_PlayMontageAndWaitForEvent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
