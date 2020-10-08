// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UGameplayAbility;
class UAT_RepeatAction;
#ifdef SONICSIEGE_AT_RepeatAction_generated_h
#error "AT_RepeatAction.generated.h already included, missing '#pragma once' in AT_RepeatAction.h"
#endif
#define SONICSIEGE_AT_RepeatAction_generated_h

#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_12_DELEGATE \
static inline void FRepeatActionDelegate_DelegateWrapper(const FMulticastScriptDelegate& RepeatActionDelegate) \
{ \
	RepeatActionDelegate.ProcessMulticastDelegate<UObject>(NULL); \
}


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execRepeatAction);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execRepeatAction);


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAT_RepeatAction(); \
	friend struct Z_Construct_UClass_UAT_RepeatAction_Statics; \
public: \
	DECLARE_CLASS(UAT_RepeatAction, USSAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_RepeatAction)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_INCLASS \
private: \
	static void StaticRegisterNativesUAT_RepeatAction(); \
	friend struct Z_Construct_UClass_UAT_RepeatAction_Statics; \
public: \
	DECLARE_CLASS(UAT_RepeatAction, USSAbilityTask, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(UAT_RepeatAction)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAT_RepeatAction(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_RepeatAction) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_RepeatAction); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_RepeatAction); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_RepeatAction(UAT_RepeatAction&&); \
	NO_API UAT_RepeatAction(const UAT_RepeatAction&); \
public:


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAT_RepeatAction(UAT_RepeatAction&&); \
	NO_API UAT_RepeatAction(const UAT_RepeatAction&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAT_RepeatAction); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAT_RepeatAction); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAT_RepeatAction)


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_PRIVATE_PROPERTY_OFFSET
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_17_PROLOG
#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_INCLASS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UAT_RepeatAction>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_AbilitySystem_AbilityTasks_AT_RepeatAction_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
