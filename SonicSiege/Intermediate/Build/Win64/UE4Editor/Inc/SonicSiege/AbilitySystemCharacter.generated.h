// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_AbilitySystemCharacter_generated_h
#error "AbilitySystemCharacter.generated.h already included, missing '#pragma once' in AbilitySystemCharacter.h"
#endif
#define SONICSIEGE_AbilitySystemCharacter_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_RPC_WRAPPERS \
	virtual bool ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Validate(); \
	virtual void ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Implementation(); \
 \
	DECLARE_FUNCTION(execServerOnSetupWithAbilitySystemCompletedOnOwningClient);


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_RPC_WRAPPERS_NO_PURE_DECLS \
	virtual bool ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Validate(); \
	virtual void ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Implementation(); \
 \
	DECLARE_FUNCTION(execServerOnSetupWithAbilitySystemCompletedOnOwningClient);


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_EVENT_PARMS
#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_CALLBACK_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_AAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemCharacter, ASSCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemCharacter) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemCharacter*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CharacterJumpAbilitySpecHandle=NETFIELD_REP_START, \
		CharacterRunAbilitySpecHandle, \
		InteractInstantAbilitySpecHandle, \
		InteractDurationAbilitySpecHandle, \
		CharacterAttributeSet, \
		HealthAttributeSet, \
		NETFIELD_REP_END=HealthAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_INCLASS \
private: \
	static void StaticRegisterNativesAAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_AAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(AAbilitySystemCharacter, ASSCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AAbilitySystemCharacter) \
	virtual UObject* _getUObject() const override { return const_cast<AAbilitySystemCharacter*>(this); } \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		CharacterJumpAbilitySpecHandle=NETFIELD_REP_START, \
		CharacterRunAbilitySpecHandle, \
		InteractInstantAbilitySpecHandle, \
		InteractDurationAbilitySpecHandle, \
		CharacterAttributeSet, \
		HealthAttributeSet, \
		NETFIELD_REP_END=HealthAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAbilitySystemCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemCharacter(AAbilitySystemCharacter&&); \
	NO_API AAbilitySystemCharacter(const AAbilitySystemCharacter&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AAbilitySystemCharacter(AAbilitySystemCharacter&&); \
	NO_API AAbilitySystemCharacter(const AAbilitySystemCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAbilitySystemCharacter); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AAbilitySystemCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__NonHandleStartingAbilities() { return STRUCT_OFFSET(AAbilitySystemCharacter, NonHandleStartingAbilities); } \
	FORCEINLINE static uint32 __PPO__CharacterJumpAbilityTSub() { return STRUCT_OFFSET(AAbilitySystemCharacter, CharacterJumpAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__CharacterJumpAbilitySpecHandle() { return STRUCT_OFFSET(AAbilitySystemCharacter, CharacterJumpAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__CharacterRunAbilityTSub() { return STRUCT_OFFSET(AAbilitySystemCharacter, CharacterRunAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__CharacterRunAbilitySpecHandle() { return STRUCT_OFFSET(AAbilitySystemCharacter, CharacterRunAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__InteractInstantAbilityTSub() { return STRUCT_OFFSET(AAbilitySystemCharacter, InteractInstantAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__InteractInstantAbilitySpecHandle() { return STRUCT_OFFSET(AAbilitySystemCharacter, InteractInstantAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__InteractDurationAbilityTSub() { return STRUCT_OFFSET(AAbilitySystemCharacter, InteractDurationAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__InteractDurationAbilitySpecHandle() { return STRUCT_OFFSET(AAbilitySystemCharacter, InteractDurationAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__DefaultAttributeValuesEffect() { return STRUCT_OFFSET(AAbilitySystemCharacter, DefaultAttributeValuesEffect); } \
	FORCEINLINE static uint32 __PPO__EffectsToApplyOnStartup() { return STRUCT_OFFSET(AAbilitySystemCharacter, EffectsToApplyOnStartup); } \
	FORCEINLINE static uint32 __PPO__AIAbilitySystemComponentReplicationMode() { return STRUCT_OFFSET(AAbilitySystemCharacter, AIAbilitySystemComponentReplicationMode); } \
	FORCEINLINE static uint32 __PPO__SSPlayerState() { return STRUCT_OFFSET(AAbilitySystemCharacter, SSPlayerState); } \
	FORCEINLINE static uint32 __PPO__PlayerAbilitySystemComponent() { return STRUCT_OFFSET(AAbilitySystemCharacter, PlayerAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__AIAbilitySystemComponent() { return STRUCT_OFFSET(AAbilitySystemCharacter, AIAbilitySystemComponent); } \
	FORCEINLINE static uint32 __PPO__CharacterAttributeSet() { return STRUCT_OFFSET(AAbilitySystemCharacter, CharacterAttributeSet); } \
	FORCEINLINE static uint32 __PPO__HealthAttributeSet() { return STRUCT_OFFSET(AAbilitySystemCharacter, HealthAttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_67_PROLOG \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_EVENT_PARMS


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_CALLBACK_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_CALLBACK_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h_70_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class AAbilitySystemCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_AbilitySystemCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
