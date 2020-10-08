// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Character/AbilitySystemCharacter.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAbilitySystemCharacter() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemCharacter();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSCharacter();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Health_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Character_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPlayerState_NoRegister();
	GAMEPLAYABILITIES_API UEnum* Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
	GAMEPLAYABILITIES_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSGameplayAbility_NoRegister();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemInterface_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AAbilitySystemCharacter::execServerOnSetupWithAbilitySystemCompletedOnOwningClient)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		if (!P_THIS->ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Validate())
		{
			RPC_ValidateFailed(TEXT("ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Validate"));
			return;
		}
		P_THIS->ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Implementation();
		P_NATIVE_END;
	}
	static FName NAME_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient = FName(TEXT("ServerOnSetupWithAbilitySystemCompletedOnOwningClient"));
	void AAbilitySystemCharacter::ServerOnSetupWithAbilitySystemCompletedOnOwningClient()
	{
		ProcessEvent(FindFunctionChecked(NAME_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient),NULL);
	}
	void AAbilitySystemCharacter::StaticRegisterNativesAAbilitySystemCharacter()
	{
		UClass* Class = AAbilitySystemCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ServerOnSetupWithAbilitySystemCompletedOnOwningClient", &AAbilitySystemCharacter::execServerOnSetupWithAbilitySystemCompletedOnOwningClient },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/** Notifies server that the client has his ability system all setup. */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Notifies server that the client has his ability system all setup." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AAbilitySystemCharacter, nullptr, "ServerOnSetupWithAbilitySystemCompletedOnOwningClient", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x80240CC1, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AAbilitySystemCharacter_NoRegister()
	{
		return AAbilitySystemCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AAbilitySystemCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_HealthAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_HealthAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_CharacterAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AIAbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AIAbilitySystemComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerAbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PlayerAbilitySystemComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bRemoveCharacterTagsOnUnpossessed_MetaData[];
#endif
		static void NewProp_bRemoveCharacterTagsOnUnpossessed_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRemoveCharacterTagsOnUnpossessed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bRemoveAbilitiesOnUnpossessed_MetaData[];
#endif
		static void NewProp_bRemoveAbilitiesOnUnpossessed_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRemoveAbilitiesOnUnpossessed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData[];
#endif
		static void NewProp_bUnregisterAttributeSetsOnUnpossessed_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bUnregisterAttributeSetsOnUnpossessed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SSPlayerState_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_SSPlayerState;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AIAbilitySystemComponentReplicationMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_AIAbilitySystemComponentReplicationMode;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_AIAbilitySystemComponentReplicationMode_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EffectsToApplyOnStartup_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_EffectsToApplyOnStartup;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_EffectsToApplyOnStartup_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DefaultAttributeValuesEffect_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_DefaultAttributeValuesEffect;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractDurationAbilitySpecHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InteractDurationAbilitySpecHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractDurationAbilityTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_InteractDurationAbilityTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractInstantAbilitySpecHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_InteractInstantAbilitySpecHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InteractInstantAbilityTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_InteractInstantAbilityTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterRunAbilitySpecHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CharacterRunAbilitySpecHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterRunAbilityTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_CharacterRunAbilityTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterJumpAbilitySpecHandle_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CharacterJumpAbilitySpecHandle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterJumpAbilityTSub_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_CharacterJumpAbilityTSub;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NonHandleStartingAbilities_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_NonHandleStartingAbilities;
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_NonHandleStartingAbilities_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAbilitySystemCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ASSCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AAbilitySystemCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AAbilitySystemCharacter_ServerOnSetupWithAbilitySystemCompletedOnOwningClient, "ServerOnSetupWithAbilitySystemCompletedOnOwningClient" }, // 1667163146
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * A Base GAS class\n * Note: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this character. Having the ASC on the playerstate can make unpossesion and repossesion a pain\n * since granted abilities and attribute sets exist on the PlayerState's ASC (because the character doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:\n * bUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemoveCharacterTagsOnUnpossessed.\n\n Some tips:\n\x09""1) on EndPlay of this actor (so before it gets destroyed)\n\x09\x09- Removes Character owned Abilities and AttributeSets\n\x09""2) Levels\n\x09\x09- Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.\n\x09\x09\x09\x09You could even have multible GetLevel() functions, one for the character class and one that persists throughtout different characters in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your character or playerstate level, you will have to think of a way to keep track of each individual ability level.\n\x09""3) Abilities\n\x09\x09- Any Abilities added with its SourceObject being the character will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between characters make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)\n\x09\x09- We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle\n\x09\x09- If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n\x09""4) Attribute Sets\n\x09\x09- Any AttributeSets owned by this character will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between characters make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)\n\x09\x09- Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n\x09""4) Gameplay Effects\n\x09\x09- Every character should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n\x09\x09- Any gameplay effects that this character should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n\x09""5) Gmeplay Tags\x09\x09=@REVIEW MARKER@=\n\x09\x09- Right now I have a setup for it calling RemoveAllCharacterTags() to remove any character tags from the player's ASC on Unpossess if bRemoveCharacterTagsOnUnpossessed is set to true, but the function is NOT implemented.\n\x09\x09\x09\x09There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this character which is why it is not implemented. If we can figure out a way to give an owner to\n\x09\x09\x09\x09specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of \"Character\" so we know all\n\x09\x09\x09\x09the \"Character\" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature\n\x09\x09\x09\x09implemented somehow, it might be better to just make a new GAS setup with the ASC on the character class.\n\x09\x09- Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has \"Character\" as one of the parents in the tag, but then this limits us\n\x09\x09\x09\x09us into only using tags with the parent of \"Character\" for character related stuff (ie. we wouldn't be able to throw a generic \"Actor.IsOnFire\" tag onto the character because then on Unpossess it wouldn't get removed).\n\x09\x09\x09\x09""Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of\n\x09\x09\x09\x09replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an\n\x09\x09\x09\x09option but not prefered, (not very efficient).\n\x09\x09\x09\x09if that tag is on our ASC, it wouldn't be removed.\n\x09""6) AIAbilitySystemComponent\n\x09\x09- Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer\n Some problems to avoid:\n\x09""1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)\n\x09\x09- Have a different attribute set for every character and avoid inheriting attributes from a parent attribute set\n\x09""2) If you unpossess a character and unregister his attribute sets, his attributes are no longer associated with an ASC\n\x09\x09- Don't apply effects to characters that have unregistered attribute sets (it will crash)\n\x09\x09\x09-(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a character and unregisters its attributes and register those attribute sets with the AI ASC)\n\x09\x09\x09-(Possible work around: have an AI controller possess the unpossessed character which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)\n*/" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Character/AbilitySystemCharacter.h" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "A Base GAS class\nNote: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this character. Having the ASC on the playerstate can make unpossesion and repossesion a pain\nsince granted abilities and attribute sets exist on the PlayerState's ASC (because the character doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:\nbUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemoveCharacterTagsOnUnpossessed.\n\n Some tips:\n       1) on EndPlay of this actor (so before it gets destroyed)\n               - Removes Character owned Abilities and AttributeSets\n       2) Levels\n               - Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.\n                               You could even have multible GetLevel() functions, one for the character class and one that persists throughtout different characters in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your character or playerstate level, you will have to think of a way to keep track of each individual ability level.\n       3) Abilities\n               - Any Abilities added with its SourceObject being the character will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between characters make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)\n               - We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle\n               - If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n       4) Attribute Sets\n               - Any AttributeSets owned by this character will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between characters make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)\n               - Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n       4) Gameplay Effects\n               - Every character should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n               - Any gameplay effects that this character should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n       5) Gmeplay Tags         =@REVIEW MARKER@=\n               - Right now I have a setup for it calling RemoveAllCharacterTags() to remove any character tags from the player's ASC on Unpossess if bRemoveCharacterTagsOnUnpossessed is set to true, but the function is NOT implemented.\n                               There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this character which is why it is not implemented. If we can figure out a way to give an owner to\n                               specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of \"Character\" so we know all\n                               the \"Character\" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature\n                               implemented somehow, it might be better to just make a new GAS setup with the ASC on the character class.\n               - Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has \"Character\" as one of the parents in the tag, but then this limits us\n                               us into only using tags with the parent of \"Character\" for character related stuff (ie. we wouldn't be able to throw a generic \"Actor.IsOnFire\" tag onto the character because then on Unpossess it wouldn't get removed).\n                               Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of\n                               replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an\n                               option but not prefered, (not very efficient).\n                               if that tag is on our ASC, it wouldn't be removed.\n       6) AIAbilitySystemComponent\n               - Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer\n Some problems to avoid:\n       1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)\n               - Have a different attribute set for every character and avoid inheriting attributes from a parent attribute set\n       2) If you unpossess a character and unregister his attribute sets, his attributes are no longer associated with an ASC\n               - Don't apply effects to characters that have unregistered attribute sets (it will crash)\n                       -(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a character and unregisters its attributes and register those attribute sets with the AI ASC)\n                       -(Possible work around: have an AI controller possess the unpossessed character which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_HealthAttributeSet_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_HealthAttributeSet = { "HealthAttributeSet", nullptr, (EPropertyFlags)0x0040000000080028, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, HealthAttributeSet), Z_Construct_UClass_UAS_Health_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_HealthAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_HealthAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterAttributeSet_MetaData[] = {
		{ "Comment", "/** Every character will have this attribute set. This is useful because this gives you a place for common attributes that every character should have. Children can make another attribute set specific to their character (ie. UAS_Demoman, UAS_Ganondorf) */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Every character will have this attribute set. This is useful because this gives you a place for common attributes that every character should have. Children can make another attribute set specific to their character (ie. UAS_Demoman, UAS_Ganondorf)" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterAttributeSet = { "CharacterAttributeSet", nullptr, (EPropertyFlags)0x0040000000080028, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, CharacterAttributeSet), Z_Construct_UClass_UAS_Character_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponent = { "AIAbilitySystemComponent", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, AIAbilitySystemComponent), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_PlayerAbilitySystemComponent_MetaData[] = {
		{ "Comment", "/*Replicated*/// Replicated can be helpful for debugging issues\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Replicated// Replicated can be helpful for debugging issues" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_PlayerAbilitySystemComponent = { "PlayerAbilitySystemComponent", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, PlayerAbilitySystemComponent), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_PlayerAbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_PlayerAbilitySystemComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/**\n\x09   ---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllCharacterTags() FOR THIS TO DO SOMETHING--- \n\x09 * Removes all tags relating to this specific character from the PlayerState's ASC\n\x09 * Remove all tags related to the character, that way when we possess a new character,\n\x09 * the old tags don't interfere with the new character.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllCharacterTags() FOR THIS TO DO SOMETHING---\nRemoves all tags relating to this specific character from the PlayerState's ASC\nRemove all tags related to the character, that way when we possess a new character,\nthe old tags don't interfere with the new character." },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemCharacter*)Obj)->bRemoveCharacterTagsOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed = { "bRemoveCharacterTagsOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemCharacter), &Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/** Remove all abilities that this object owns on unpossess */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Remove all abilities that this object owns on unpossess" },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemCharacter*)Obj)->bRemoveAbilitiesOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed = { "bRemoveAbilitiesOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemCharacter), &Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/** \n\x09 * Takes this object's AttributeSet(s) away from the player's ASC. This is on by default to prevent the potential problem of the ASC having 2 attribute sets of the same class.\n\x09 * However if the ASC no longer has this object's AttributeSet, GameplayEffects can no longet modify their attributes.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Takes this object's AttributeSet(s) away from the player's ASC. This is on by default to prevent the potential problem of the ASC having 2 attribute sets of the same class.\nHowever if the ASC no longer has this object's AttributeSet, GameplayEffects can no longet modify their attributes." },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemCharacter*)Obj)->bUnregisterAttributeSetsOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed = { "bUnregisterAttributeSetsOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemCharacter), &Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_SSPlayerState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_SSPlayerState = { "SSPlayerState", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, SSPlayerState), Z_Construct_UClass_ASSPlayerState_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_SSPlayerState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_SSPlayerState_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData[] = {
		{ "Category", "AbilitySystemSetup|AI" },
		{ "Comment", "/** Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode = { "AIAbilitySystemComponentReplicationMode", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, AIAbilitySystemComponentReplicationMode), Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen) */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen)" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, EffectsToApplyOnStartup), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup_MetaData)) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup_Inner = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0004000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_DefaultAttributeValuesEffect_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** Default attributes values for a Character on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Character's starting attribute values will be on spawn */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Default attributes values for a Character on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Character's starting attribute values will be on spawn" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_DefaultAttributeValuesEffect = { "DefaultAttributeValuesEffect", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, DefaultAttributeValuesEffect), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_DefaultAttributeValuesEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_DefaultAttributeValuesEffect_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilitySpecHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilitySpecHandle = { "InteractDurationAbilitySpecHandle", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, InteractDurationAbilitySpecHandle), Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilitySpecHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilitySpecHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilityTSub_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Abilities" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilityTSub = { "InteractDurationAbilityTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, InteractDurationAbilityTSub), Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilityTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilityTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilitySpecHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilitySpecHandle = { "InteractInstantAbilitySpecHandle", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, InteractInstantAbilitySpecHandle), Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilitySpecHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilitySpecHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilityTSub_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Abilities" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilityTSub = { "InteractInstantAbilityTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, InteractInstantAbilityTSub), Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilityTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilityTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilitySpecHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilitySpecHandle = { "CharacterRunAbilitySpecHandle", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, CharacterRunAbilitySpecHandle), Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilitySpecHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilitySpecHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilityTSub_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Abilities" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilityTSub = { "CharacterRunAbilityTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, CharacterRunAbilityTSub), Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilityTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilityTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilitySpecHandle_MetaData[] = {
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilitySpecHandle = { "CharacterJumpAbilitySpecHandle", nullptr, (EPropertyFlags)0x0020080000000020, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, CharacterJumpAbilitySpecHandle), Z_Construct_UScriptStruct_FGameplayAbilitySpecHandle, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilitySpecHandle_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilitySpecHandle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilityTSub_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Abilities" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilityTSub = { "CharacterJumpAbilityTSub", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, CharacterJumpAbilityTSub), Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilityTSub_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilityTSub_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Abilities" },
		{ "Comment", "/** Note: No AbilitySpecHandles are tracked upon grant. These are good for passive abilities. These abilities are assigned EAbilityInputID::None */" },
		{ "ModuleRelativePath", "Public/Character/AbilitySystemCharacter.h" },
		{ "ToolTip", "Note: No AbilitySpecHandles are tracked upon grant. These are good for passive abilities. These abilities are assigned EAbilityInputID::None" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities = { "NonHandleStartingAbilities", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemCharacter, NonHandleStartingAbilities), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities_MetaData)) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities_Inner = { "NonHandleStartingAbilities", nullptr, (EPropertyFlags)0x0004000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_USSGameplayAbility_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAbilitySystemCharacter_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_HealthAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_PlayerAbilitySystemComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveCharacterTagsOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bRemoveAbilitiesOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_SSPlayerState,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_AIAbilitySystemComponentReplicationMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_EffectsToApplyOnStartup_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_DefaultAttributeValuesEffect,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilitySpecHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractDurationAbilityTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilitySpecHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_InteractInstantAbilityTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilitySpecHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterRunAbilityTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilitySpecHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_CharacterJumpAbilityTSub,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemCharacter_Statics::NewProp_NonHandleStartingAbilities_Inner,
	};
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UAbilitySystemInterface_NoRegister, (int32)VTABLE_OFFSET(AAbilitySystemCharacter, IAbilitySystemInterface), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAbilitySystemCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAbilitySystemCharacter>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAbilitySystemCharacter_Statics::ClassParams = {
		&AAbilitySystemCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AAbilitySystemCharacter_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemCharacter_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemCharacter_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAbilitySystemCharacter()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAbilitySystemCharacter_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAbilitySystemCharacter, 297641107);
	template<> SONICSIEGE_API UClass* StaticClass<AAbilitySystemCharacter>()
	{
		return AAbilitySystemCharacter::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAbilitySystemCharacter(Z_Construct_UClass_AAbilitySystemCharacter, &AAbilitySystemCharacter::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AAbilitySystemCharacter"), false, nullptr, nullptr, nullptr);

	void AAbilitySystemCharacter::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_CharacterJumpAbilitySpecHandle(TEXT("CharacterJumpAbilitySpecHandle"));
		static const FName Name_CharacterRunAbilitySpecHandle(TEXT("CharacterRunAbilitySpecHandle"));
		static const FName Name_InteractInstantAbilitySpecHandle(TEXT("InteractInstantAbilitySpecHandle"));
		static const FName Name_InteractDurationAbilitySpecHandle(TEXT("InteractDurationAbilitySpecHandle"));
		static const FName Name_CharacterAttributeSet(TEXT("CharacterAttributeSet"));
		static const FName Name_HealthAttributeSet(TEXT("HealthAttributeSet"));

		const bool bIsValid = true
			&& Name_CharacterJumpAbilitySpecHandle == ClassReps[(int32)ENetFields_Private::CharacterJumpAbilitySpecHandle].Property->GetFName()
			&& Name_CharacterRunAbilitySpecHandle == ClassReps[(int32)ENetFields_Private::CharacterRunAbilitySpecHandle].Property->GetFName()
			&& Name_InteractInstantAbilitySpecHandle == ClassReps[(int32)ENetFields_Private::InteractInstantAbilitySpecHandle].Property->GetFName()
			&& Name_InteractDurationAbilitySpecHandle == ClassReps[(int32)ENetFields_Private::InteractDurationAbilitySpecHandle].Property->GetFName()
			&& Name_CharacterAttributeSet == ClassReps[(int32)ENetFields_Private::CharacterAttributeSet].Property->GetFName()
			&& Name_HealthAttributeSet == ClassReps[(int32)ENetFields_Private::HealthAttributeSet].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AAbilitySystemCharacter"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAbilitySystemCharacter);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
