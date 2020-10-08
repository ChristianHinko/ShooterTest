// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/SSCharacterMovementComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSCharacterMovementComponent() {}
// Cross Module References
	SONICSIEGE_API UEnum* Z_Construct_UEnum_SonicSiege_ECustomMovementMode();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSCharacterMovementComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSCharacterMovementComponent();
	ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
// End Cross Module References
	static UEnum* ECustomMovementMode_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SonicSiege_ECustomMovementMode, Z_Construct_UPackage__Script_SonicSiege(), TEXT("ECustomMovementMode"));
		}
		return Singleton;
	}
	template<> SONICSIEGE_API UEnum* StaticEnum<ECustomMovementMode>()
	{
		return ECustomMovementMode_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ECustomMovementMode(ECustomMovementMode_StaticEnum, TEXT("/Script/SonicSiege"), TEXT("ECustomMovementMode"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SonicSiege_ECustomMovementMode_Hash() { return 1783398762U; }
	UEnum* Z_Construct_UEnum_SonicSiege_ECustomMovementMode()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ECustomMovementMode"), 0, Get_Z_Construct_UEnum_SonicSiege_ECustomMovementMode_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "CMOVE_None", (int64)CMOVE_None },
				{ "CMOVE_InfiniteAngleWalking", (int64)CMOVE_InfiniteAngleWalking },
				{ "CMOVE_MAX", (int64)CMOVE_MAX },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "CMOVE_InfiniteAngleWalking.Comment", "/** Walking on a surface with the ability to walk up any slope angle */" },
				{ "CMOVE_InfiniteAngleWalking.DisplayName", "InfiniteAngleWalking" },
				{ "CMOVE_InfiniteAngleWalking.Name", "CMOVE_InfiniteAngleWalking" },
				{ "CMOVE_InfiniteAngleWalking.ToolTip", "Walking on a surface with the ability to walk up any slope angle" },
				{ "CMOVE_MAX.Hidden", "" },
				{ "CMOVE_MAX.Name", "CMOVE_MAX" },
				{ "CMOVE_None.Comment", "/** None (custom movement is disabled). */" },
				{ "CMOVE_None.DisplayName", "None" },
				{ "CMOVE_None.Name", "CMOVE_None" },
				{ "CMOVE_None.ToolTip", "None (custom movement is disabled)." },
				{ "Comment", "/**\n * Custom movement modes. used when MovementMode == MOVE_Custom\n */// should we make this an enum class?\n" },
				{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
				{ "ToolTip", "Custom movement modes. used when MovementMode == MOVE_Custom\n // should we make this an enum class?" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SonicSiege,
				nullptr,
				"ECustomMovementMode",
				"ECustomMovementMode",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	DEFINE_FUNCTION(USSCharacterMovementComponent::execSSClientAdjustPosition)
	{
		P_GET_UBOOL(Z_Param_bAdjustedCanRun);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SSClientAdjustPosition_Implementation(Z_Param_bAdjustedCanRun);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USSCharacterMovementComponent::execOnOwningCharacterSetupWithAbilitySystemFinished)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOwningCharacterSetupWithAbilitySystemFinished();
		P_NATIVE_END;
	}
	static FName NAME_USSCharacterMovementComponent_SSClientAdjustPosition = FName(TEXT("SSClientAdjustPosition"));
	void USSCharacterMovementComponent::SSClientAdjustPosition(bool bAdjustedCanRun)
	{
		SSCharacterMovementComponent_eventSSClientAdjustPosition_Parms Parms;
		Parms.bAdjustedCanRun=bAdjustedCanRun ? true : false;
		ProcessEvent(FindFunctionChecked(NAME_USSCharacterMovementComponent_SSClientAdjustPosition),&Parms);
	}
	void USSCharacterMovementComponent::StaticRegisterNativesUSSCharacterMovementComponent()
	{
		UClass* Class = USSCharacterMovementComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnOwningCharacterSetupWithAbilitySystemFinished", &USSCharacterMovementComponent::execOnOwningCharacterSetupWithAbilitySystemFinished },
			{ "SSClientAdjustPosition", &USSCharacterMovementComponent::execSSClientAdjustPosition },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USSCharacterMovementComponent, nullptr, "OnOwningCharacterSetupWithAbilitySystemFinished", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics
	{
		static void NewProp_bAdjustedCanRun_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bAdjustedCanRun;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::NewProp_bAdjustedCanRun_SetBit(void* Obj)
	{
		((SSCharacterMovementComponent_eventSSClientAdjustPosition_Parms*)Obj)->bAdjustedCanRun = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::NewProp_bAdjustedCanRun = { "bAdjustedCanRun", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(SSCharacterMovementComponent_eventSSClientAdjustPosition_Parms), &Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::NewProp_bAdjustedCanRun_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::NewProp_bAdjustedCanRun,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USSCharacterMovementComponent, nullptr, "SSClientAdjustPosition", nullptr, nullptr, sizeof(SSCharacterMovementComponent_eventSSClientAdjustPosition_Parms), Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x01080C40, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USSCharacterMovementComponent_NoRegister()
	{
		return USSCharacterMovementComponent::StaticClass();
	}
	struct Z_Construct_UClass_USSCharacterMovementComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OwnerSSASC_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwnerSSASC;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OwnerAbilitySystemCharacter_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_OwnerAbilitySystemCharacter;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSCharacterMovementComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USSCharacterMovementComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USSCharacterMovementComponent_OnOwningCharacterSetupWithAbilitySystemFinished, "OnOwningCharacterSetupWithAbilitySystemFinished" }, // 628393321
		{ &Z_Construct_UFunction_USSCharacterMovementComponent_SSClientAdjustPosition, "SSClientAdjustPosition" }, // 1919830588
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Our custom base implementation of the CMC\n * \n *\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09""An overview:\n * \n * \n * \n * \n * \n * Movement restrictions:\n *\x09\x09- Movement restrictions is a way to expose the CMC for gameplay related code. This is mainly for integration with the Gameplay Ability System.\n *\x09\x09\x09- Ex: if a stun grenade hits a character, you would set bCanRun to false for the duration of the stun and\n *\x09\x09\x09this would work flawlessly over the network\n * \n *\x09\x09- All movement restrictions should be correctable by the server (SEE: Custom client adjustment section below).\n *\x09\x09\n * \n * \n * \n * \n * Custom client adjustment:\n *\x09\x09""1) To have custom CMC variables corrected by the server, make your own ClientAdjustPosition unreliable client RPC.\n *\x09\x09\x09- Add a parameter for each variable you want the server to correct (a good prefix is \"adjusted\" for example: bAdjustedCanRun).\n *\x09\x09\x09- In your _Implementation, set your correctable CMC variables to their corresponding \"adjusted\" variables.\n *\x09\x09\x09\x09---------------------------------------------------------------------------------------------------\n *\x09\x09\x09\x09| Example:\n *\x09\x09\x09\x09---------------------------------------------------------------------------------------------------\n *\x09\x09\x09\x09|\x09MyClientAdjustPosition_Implementation(bool bAdjustedCanRun, bool bAdjustedCanJump, float adjustedJumpHeight)\n *\x09\x09\x09\x09|\x09{\n *  \x09\x09\x09|\x09\x09""bCanRun = bAdjustedCanRun;\n *  \x09\x09\x09|\x09\x09""bCanJump = bAdjustedCanJump;\n *  \x09\x09\x09|\x09\x09jumpHeight = adjustedJumpHeight;\n *\x09\x09\x09\x09|\x09}\n *\x09\x09\x09\x09---------------------------------------------------------------------------------------------------\n * \n *\x09\x09""2) Override the ClientAdjustPosition() function\n *\x09\x09\x09- NOT THE _IMPLEMENTATION! We want the server to call our RPC not the client.\n *\x09\x09\x09- Call the Super, and make it call your client adjust RPC.\n *\x09\x09\x09- This is a perfect event to call you custom client adjust RPCs.\n * \n *\x09\x09- If you have children CMCs and they also want custom client adjustment, they can repeat this process.\n *\x09\x09\x09- You may say all of these RPCs are bad and you are correct but the CMC in general is bad, this is the best solution.\n *\x09\x09\x09\x09- Ex: if you are 3 levels deep of inheritance witht the CMC, thats 3 client RPCs at once when the client is corrected.\n * \n * \n * \n * \n * \n * Integration with GAS:\n *\x09\x09- Make heavy use of movement restrictions\n *\x09\x09\x09- You probably want a corresponding Gameplay Tag for each movement restriction\n *\x09\x09\x09- I would avoid setting the movement restrictions directly\n *\x09\x09\x09- Use RegisterGameplayTagEvent with EGameplayTagEventType::NewOrRemoved to have your movement restrictions synced with their gameplay tags\n * \n *\x09\x09- For movement abilities such as GA_CharacterRun\n *\x09\x09\x09- If something goes wrong set the abilities corresponding movement restriction to disable the movement (ex: set bCanRun to false)\n *\x09\x09\x09\x09- In CanActivateAbility() whenever you return false, disable the movement\n *\x09\x09\x09\x09- In ActivteAbility() anywhere you have CancelAbility(), disable the movement\n *\x09\x09\x09- This is an exception to not setting movement restrictions directly\x09\x09]\\]\\]][\x09\x09""actually its not maybe use a GE for this\n *\x09\x09\x09-\x09\x09\x09\x09talk about movement restrictions working as rollback\x09\x09\x09\\-\\-=\\-\\-\\]-\\]-\\]\\-\\-]-\\]-\\-]\\-=]\\-=\\]-]\\-=\\]\n * \n * \n * \n * \n *\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09I realized documenting this is probably a waste of time but its here if you want to finish it:\n * Steps to make a custom move:\n *\x09\x09""1) Make a function for activating it (ex: SetWantsToRun)\n *\x09\x09""2) Make a corresponding compressed movement flag for the move\n *\x09\x09\x09- Its good to define a macro representing that flag\n *\x09\x09""3) \n */" },
		{ "IncludePath", "Character/SSCharacterMovementComponent.h" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
		{ "ToolTip", "Our custom base implementation of the CMC\n\n                                                                                                                            An overview:\n\n\n\n\n\nMovement restrictions:\n            - Movement restrictions is a way to expose the CMC for gameplay related code. This is mainly for integration with the Gameplay Ability System.\n                    - Ex: if a stun grenade hits a character, you would set bCanRun to false for the duration of the stun and\n                    this would work flawlessly over the network\n\n            - All movement restrictions should be correctable by the server (SEE: Custom client adjustment section below).\n\n\n\n\n\nCustom client adjustment:\n            1) To have custom CMC variables corrected by the server, make your own ClientAdjustPosition unreliable client RPC.\n                    - Add a parameter for each variable you want the server to correct (a good prefix is \"adjusted\" for example: bAdjustedCanRun).\n                    - In your _Implementation, set your correctable CMC variables to their corresponding \"adjusted\" variables.\n                            ---------------------------------------------------------------------------------------------------\n                            | Example:\n                            ---------------------------------------------------------------------------------------------------\n                            |       MyClientAdjustPosition_Implementation(bool bAdjustedCanRun, bool bAdjustedCanJump, float adjustedJumpHeight)\n                            |       {\n                    |               bCanRun = bAdjustedCanRun;\n                    |               bCanJump = bAdjustedCanJump;\n                    |               jumpHeight = adjustedJumpHeight;\n                            |       }\n                            ---------------------------------------------------------------------------------------------------\n\n            2) Override the ClientAdjustPosition() function\n                    - NOT THE _IMPLEMENTATION! We want the server to call our RPC not the client.\n                    - Call the Super, and make it call your client adjust RPC.\n                    - This is a perfect event to call you custom client adjust RPCs.\n\n            - If you have children CMCs and they also want custom client adjustment, they can repeat this process.\n                    - You may say all of these RPCs are bad and you are correct but the CMC in general is bad, this is the best solution.\n                            - Ex: if you are 3 levels deep of inheritance witht the CMC, thats 3 client RPCs at once when the client is corrected.\n\n\n\n\n\nIntegration with GAS:\n            - Make heavy use of movement restrictions\n                    - You probably want a corresponding Gameplay Tag for each movement restriction\n                    - I would avoid setting the movement restrictions directly\n                    - Use RegisterGameplayTagEvent with EGameplayTagEventType::NewOrRemoved to have your movement restrictions synced with their gameplay tags\n\n            - For movement abilities such as GA_CharacterRun\n                    - If something goes wrong set the abilities corresponding movement restriction to disable the movement (ex: set bCanRun to false)\n                            - In CanActivateAbility() whenever you return false, disable the movement\n                            - In ActivteAbility() anywhere you have CancelAbility(), disable the movement\n                    - This is an exception to not setting movement restrictions directly            ]\\]\\]][         actually its not maybe use a GE for this\n                    -                               talk about movement restrictions working as rollback                    \\-\\-=\\-\\-\\]-\\]-\\]\\-\\-]-\\]-\\-]\\-=]\\-=\\]-]\\-=\\]\n\n\n\n\n                                                                            I realized documenting this is probably a waste of time but its here if you want to finish it:\nSteps to make a custom move:\n            1) Make a function for activating it (ex: SetWantsToRun)\n            2) Make a corresponding compressed movement flag for the move\n                    - Its good to define a macro representing that flag\n            3)" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet = { "CharacterAttributeSet", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, CharacterAttributeSet), Z_Construct_UClass_UAS_Character_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC = { "OwnerSSASC", nullptr, (EPropertyFlags)0x0020080000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, OwnerSSASC), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/SSCharacterMovementComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter = { "OwnerAbilitySystemCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USSCharacterMovementComponent, OwnerAbilitySystemCharacter), Z_Construct_UClass_AAbilitySystemCharacter_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_CharacterAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerSSASC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USSCharacterMovementComponent_Statics::NewProp_OwnerAbilitySystemCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSCharacterMovementComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSCharacterMovementComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSCharacterMovementComponent_Statics::ClassParams = {
		&USSCharacterMovementComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSCharacterMovementComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSCharacterMovementComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSCharacterMovementComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSCharacterMovementComponent, 697735341);
	template<> SONICSIEGE_API UClass* StaticClass<USSCharacterMovementComponent>()
	{
		return USSCharacterMovementComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSCharacterMovementComponent(Z_Construct_UClass_USSCharacterMovementComponent, &USSCharacterMovementComponent::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSCharacterMovementComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSCharacterMovementComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
