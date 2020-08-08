// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSonicSiege_init() {}
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature();
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature();
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnGameplayEffectStackChanged__DelegateSignature();
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature();
	SONICSIEGE_API UFunction* Z_Construct_UDelegateFunction_SonicSiege_GDPlayMontageAndWaitForEventDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_SonicSiege()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_SonicSiege_OnAttributeChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SonicSiege_OnCooldownChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SonicSiege_OnGameplayEffectStackChanged__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SonicSiege_OnGameplayTagAddedRemoved__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_SonicSiege_GDPlayMontageAndWaitForEventDelegate__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/SonicSiege",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xB2703479,
				0x086F2352,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
