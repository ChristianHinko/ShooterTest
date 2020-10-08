// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SONICSIEGE_Interactable_generated_h
#error "Interactable.generated.h already included, missing '#pragma once' in Interactable.h"
#endif
#define SONICSIEGE_Interactable_generated_h

#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_SPARSE_DATA
#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_RPC_WRAPPERS
#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_RPC_WRAPPERS_NO_PURE_DECLS
#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	SONICSIEGE_API UInteractable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInteractable) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(SONICSIEGE_API, UInteractable); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractable); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	SONICSIEGE_API UInteractable(UInteractable&&); \
	SONICSIEGE_API UInteractable(const UInteractable&); \
public:


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	SONICSIEGE_API UInteractable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	SONICSIEGE_API UInteractable(UInteractable&&); \
	SONICSIEGE_API UInteractable(const UInteractable&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(SONICSIEGE_API, UInteractable); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInteractable); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInteractable)


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUInteractable(); \
	friend struct Z_Construct_UClass_UInteractable_Statics; \
public: \
	DECLARE_CLASS(UInteractable, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/SonicSiege"), SONICSIEGE_API) \
	DECLARE_SERIALIZER(UInteractable)


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_GENERATED_UINTERFACE_BODY() \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_GENERATED_UINTERFACE_BODY() \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IInteractable() {} \
public: \
	typedef UInteractable UClassType; \
	typedef IInteractable ThisClass; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_INCLASS_IINTERFACE \
protected: \
	virtual ~IInteractable() {} \
public: \
	typedef UInteractable UClassType; \
	typedef IInteractable ThisClass; \
	virtual UObject* _getUObject() const { check(0 && "Missing required implementation."); return nullptr; }


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_37_PROLOG
#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_54_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_RPC_WRAPPERS \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_54_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_SPARSE_DATA \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_RPC_WRAPPERS_NO_PURE_DECLS \
	SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h_40_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SONICSIEGE_API UClass* StaticClass<class UInteractable>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SonicSiege_Source_SonicSiege_Public_Interfaces_Interactable_h


#define FOREACH_ENUM_EDURATIONINTERACTENDREASON(op) \
	op(EDurationInteractEndReason::REASON_Unknown) \
	op(EDurationInteractEndReason::REASON_InputRelease) \
	op(EDurationInteractEndReason::REASON_SweepMiss) \
	op(EDurationInteractEndReason::REASON_CharacterLeftInteractionOverlap) \
	op(EDurationInteractEndReason::REASON_NewInteractionOverlapPriority) \
	op(EDurationInteractEndReason::REASON_AbilityCanceled) \
	op(EDurationInteractEndReason::REASON_SuccessfulInteract) 

enum class EDurationInteractEndReason;
template<> SONICSIEGE_API UEnum* StaticEnum<EDurationInteractEndReason>();

#define FOREACH_ENUM_EDETECTTYPE(op) \
	op(EDetectType::DETECTTYPE_NotDetected) \
	op(EDetectType::DETECTTYPE_Sweeped) \
	op(EDetectType::DETECTTYPE_Overlapped) 

enum class EDetectType;
template<> SONICSIEGE_API UEnum* StaticEnum<EDetectType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
