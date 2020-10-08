// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APawn;
struct FPawnInfo;
#ifdef SONICSIEGE_SSPlayerController_generated_h
#error "SSPlayerController.generated.h already included, missing '#pragma once' in SSPlayerController.h"
#endif
#define SONICSIEGE_SSPlayerController_generated_h

#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_30_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FPawnInfo_Statics; \
	SONICSIEGE_API static class UScriptStruct* StaticStruct();


template<> SONICSIEGE_API UScriptStruct* StaticStruct<struct FPawnInfo>();

#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSpawnPawnFromPendingInfo); \
	DECLARE_FUNCTION(execSetPendingPawnInfo);


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSpawnPawnFromPendingInfo); \
	DECLARE_FUNCTION(execSetPendingPawnInfo);


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASSPlayerController(); \
	friend struct Z_Construct_UClass_ASSPlayerController_Statics; \
public: \
	DECLARE_CLASS(ASSPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSPlayerController) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		SSPlayerState=NETFIELD_REP_START, \
		NETFIELD_REP_END=SSPlayerState	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_INCLASS \
private: \
	static void StaticRegisterNativesASSPlayerController(); \
	friend struct Z_Construct_UClass_ASSPlayerController_Statics; \
public: \
	DECLARE_CLASS(ASSPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SonicSiege"), NO_API) \
	DECLARE_SERIALIZER(ASSPlayerController) \
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; \
	enum class ENetFields_Private : uint16 \
	{ \
		NETFIELD_REP_START=(uint16)((int32)Super::ENetFields_Private::NETFIELD_REP_END + (int32)1), \
		SSPlayerState=NETFIELD_REP_START, \
		NETFIELD_REP_END=SSPlayerState	}; \
	NO_API virtual void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const override;


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASSPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASSPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSPlayerController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSPlayerController(ASSPlayerController&&); \
	NO_API ASSPlayerController(const ASSPlayerController&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASSPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASSPlayerController(ASSPlayerController&&); \
	NO_API ASSPlayerController(const ASSPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASSPlayerController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASSPlayerController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASSPlayerController)


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__PawnInfos() { return STRUCT_OFFSET(ASSPlayerController, PawnInfos); } \
	FORCEINLINE static uint32 __PPO__SSGamemode() { return STRUCT_OFFSET(ASSPlayerController, SSGamemode); } \
	FORCEINLINE static uint32 __PPO__SSPlayerState() { return STRUCT_OFFSET(ASSPlayerController, SSPlayerState); }


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_43_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_INCLASS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_PRIVATE_PROPERTY_OFFSET \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_INCLASS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h_46_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class ASSPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Player_SSPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
