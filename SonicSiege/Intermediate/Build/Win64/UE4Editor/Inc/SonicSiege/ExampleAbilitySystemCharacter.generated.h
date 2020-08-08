// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_ExampleAbilitySystemCharacter_generated_h
#error "ExampleAbilitySystemCharacter.generated.h already included, missing '#pragma once' in ExampleAbilitySystemCharacter.h"
#endif
#define SONICSIEGE_ExampleAbilitySystemCharacter_generated_h

#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAExampleAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(AExampleAbilitySystemCharacter, AAbilitySystemCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AExampleAbilitySystemCharacter) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ExampleAbilitySpecHandle=NETFIELD_REP_START, \
		ExampleAbilitySystemCharacterAttributeSet, \
		NETFIELD_REP_END=ExampleAbilitySystemCharacterAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_INCLASS \
private: \
	static void StaticRegisterNativesAExampleAbilitySystemCharacter(); \
	friend struct Z_Construct_UClass_AExampleAbilitySystemCharacter_Statics; \
public: \
	DECLARE_CLASS(AExampleAbilitySystemCharacter, AAbilitySystemCharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(AExampleAbilitySystemCharacter) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		ExampleAbilitySpecHandle=NETFIELD_REP_START, \
		ExampleAbilitySystemCharacterAttributeSet, \
		NETFIELD_REP_END=ExampleAbilitySystemCharacterAttributeSet	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AExampleAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AExampleAbilitySystemCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AExampleAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AExampleAbilitySystemCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AExampleAbilitySystemCharacter(AExampleAbilitySystemCharacter&&); \
	NO_API AExampleAbilitySystemCharacter(const AExampleAbilitySystemCharacter&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AExampleAbilitySystemCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AExampleAbilitySystemCharacter(AExampleAbilitySystemCharacter&&); \
	NO_API AExampleAbilitySystemCharacter(const AExampleAbilitySystemCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AExampleAbilitySystemCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AExampleAbilitySystemCharacter); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AExampleAbilitySystemCharacter)


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__ExampleAbilityTSub() { return STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilityTSub); } \
	FORCEINLINE static uint32 __PPO__ExampleAbilitySpecHandle() { return STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilitySpecHandle); } \
	FORCEINLINE static uint32 __PPO__ExampleAbilitySystemCharacterAttributeSet() { return STRUCT_OFFSET(AExampleAbilitySystemCharacter, ExampleAbilitySystemCharacterAttributeSet); }


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_15_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class AExampleAbilitySystemCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Character_Characters_ExampleAbilitySystemCharacter_ExampleAbilitySystemCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
