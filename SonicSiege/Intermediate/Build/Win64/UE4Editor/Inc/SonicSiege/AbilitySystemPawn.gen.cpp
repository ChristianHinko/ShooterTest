// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/Pawn/AbilitySystemPawn.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAbilitySystemPawn() {}
// Cross Module References
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemPawn_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_AAbilitySystemPawn();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPawn();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_UAS_Pawn_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_ASSPlayerState_NoRegister();
	GAMEPLAYABILITIES_API UEnum* Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UGameplayEffect_NoRegister();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemInterface_NoRegister();
// End Cross Module References
	void AAbilitySystemPawn::StaticRegisterNativesAAbilitySystemPawn()
	{
	}
	UClass* Z_Construct_UClass_AAbilitySystemPawn_NoRegister()
	{
		return AAbilitySystemPawn::StaticClass();
	}
	struct Z_Construct_UClass_AAbilitySystemPawn_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PawnAttributeSet_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PawnAttributeSet;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AIAbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AIAbilitySystemComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerAbilitySystemComponent_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_PlayerAbilitySystemComponent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bRemovePawnTagsOnUnpossessed_MetaData[];
#endif
		static void NewProp_bRemovePawnTagsOnUnpossessed_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRemovePawnTagsOnUnpossessed;
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
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAbilitySystemPawn_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ASSPawn,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * A Base GAS class\n   \n   Code in this class is just copied from the AbilitySystemPawn class. This is just the pawn version of that code. Only thing that really needs changing after copying the code is replace all instances of \"Pawn\" and \"pawn\" with \"Pawn\" and \"pawn\" respectively.\n\n   Note: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this pawn. Having the ASC on the playerstate can make unpossesion and repossesion a pain\n   since granted abilities and attribute sets exist on the PlayerState's ASC (because the pawn doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:\n   bUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemovePawnTagsOnUnpossessed.\n \n   \n Some tips:\n\x09""1) on EndPlay of this actor (so before it gets destroyed)\n\x09\x09- Removes Pawn owned Abilities and AttributeSets\n\x09""2) Levels\n\x09\x09- Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.\n\x09\x09\x09\x09You could even have multible GetLevel() functions, one for the pawn class and one that persists throughtout different pawns in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your pawn or playerstate level, you will have to think of a way to keep track of each individual ability level.\n\x09""3) Abilities\n\x09\x09- Any Abilities added with its SourceObject being the pawn will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between pawns make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)\n\x09\x09- We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle\n\x09\x09- If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n\x09""4) Attribute Sets\n\x09\x09- Any AttributeSets owned by this pawn will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between pawns make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)\n\x09\x09- Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n\x09""4) Gameplay Effects\n\x09\x09- Every pawn should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n\x09\x09- Any gameplay effects that this pawn should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n\x09""5) Gmeplay Tags\x09\x09=@REVIEW MARKER@=\n\x09\x09- Right now I have a setup for it calling RemoveAllPawnTags() to remove any pawn tags from the player's ASC on Unpossess if bRemovePawnTagsOnUnpossessed is set to true, but the function is NOT implemented.\n\x09\x09\x09\x09There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this pawn which is why it is not implemented. If we can figure out a way to give an owner to\n\x09\x09\x09\x09specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of \"Pawn\" so we know all\n\x09\x09\x09\x09the \"Pawn\" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature\n\x09\x09\x09\x09implemented somehow, it might be better to just make a new GAS setup with the ASC on the pawn class.\n\x09\x09- Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has \"Pawn\" as one of the parents in the tag, but then this limits us\n\x09\x09\x09\x09us into only using tags with the parent of \"Pawn\" for pawn related stuff (ie. we wouldn't be able to throw a generic \"Actor.IsOnFire\" tag onto the pawn because then on Unpossess it wouldn't get removed).\n\x09\x09\x09\x09""Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of\n\x09\x09\x09\x09replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an\n\x09\x09\x09\x09option but not prefered, (not very efficient).\n\x09\x09\x09\x09if that tag is on our ASC, it wouldn't be removed.\n\x09""6) AIAbilitySystemComponent\n\x09\x09- Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer\n Some problems to avoid:\n\x09""1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)\n\x09\x09- Have a different attribute set for every pawn and avoid inheriting attributes from a parent attribute set\n\x09""2) If you unpossess a pawn and unregister his attribute sets, his attributes are no longer associated with an ASC\n\x09\x09- Don't apply effects to pawns that have unregistered attribute sets (it will crash)\n\x09\x09\x09-(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a pawn and unregisters its attributes and register those attribute sets with the AI ASC)\n\x09\x09\x09-(Possible work around: have an AI controller possess the unpossessed pawn which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)\n*/" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Pawn/AbilitySystemPawn.h" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "A Base GAS class\n\n   Code in this class is just copied from the AbilitySystemPawn class. This is just the pawn version of that code. Only thing that really needs changing after copying the code is replace all instances of \"Pawn\" and \"pawn\" with \"Pawn\" and \"pawn\" respectively.\n\n   Note: This was designed to be as flexable as possible for things regarding unpossesion/reposession of this pawn. Having the ASC on the playerstate can make unpossesion and repossesion a pain\n   since granted abilities and attribute sets exist on the PlayerState's ASC (because the pawn doesn't have one unless it's an AI). To make this less painful, some useful bools were implemented:\n   bUnregisterAttributeSetsOnUnpossessed, bRemoveAbilitiesOnUnpossessed, and bRemovePawnTagsOnUnpossessed.\n\n\n Some tips:\n       1) on EndPlay of this actor (so before it gets destroyed)\n               - Removes Pawn owned Abilities and AttributeSets\n       2) Levels\n               - Always passed in as 1 because this template does not come with a level system. GetLevel() is what you should make if your wanting a level system. This is commented out at all places where the level is passed in. As to where you should make your GetLevel() function, idk.\n                               You could even have multible GetLevel() functions, one for the pawn class and one that persists throughtout different pawns in the PlayerState.However, if you want a system where you have to level up each ability individually and abilities don't reflect your pawn or playerstate level, you will have to think of a way to keep track of each individual ability level.\n       3) Abilities\n               - Any Abilities added with its SourceObject being the pawn will be automatically removed from the ASC (SourceObject is set in GrantAbility()). If you want an ability set to persist between pawns make sure you manually set its SourceObject to the PlayerState. (still havn't tested thoroughly but should work)\n               - We've decided on not having a StartingAbilities array, that way we can focus on having a reference to each ability's TSubClassOf and AbilitySpecHandle\n               - If you have a starting ability just override GrantStartingAbilities() and call Super in the beginning, then add your own logic\n       4) Attribute Sets\n               - Any AttributeSets owned by this pawn will be automatically removed from the ASC (owner actor is automatically set by the engine). If you want an attribute set to persist between pawns make sure you manually set its owner to the PlayerState. (still haven't tested with non subobject attribute sets)\n               - Subclasses should override RegisterAttributeSets() and call the Super at the beginning if they would like to add more attribute sets than the default pawn one\n       4) Gameplay Effects\n               - Every pawn should initialize their attributes through the DefaultAttributeValuesEffect GameplayEffectTSub in BP.\n               - Any gameplay effects that this pawn should have on spawn should be filled in in the EffectsToApplyOnStartup TArray in BP. (ie. GE_HealthRegen or GE_StaminaRegen)\n       5) Gmeplay Tags         =@REVIEW MARKER@=\n               - Right now I have a setup for it calling RemoveAllPawnTags() to remove any pawn tags from the player's ASC on Unpossess if bRemovePawnTagsOnUnpossessed is set to true, but the function is NOT implemented.\n                               There is no way of determining what tags to take off of the player's ASC when unpossessing/destroying this pawn which is why it is not implemented. If we can figure out a way to give an owner to\n                               specific tags without putting them on the actually actor, then this should be easily possible. You could implement it by removing all tags from the ASC that has a parent of \"Pawn\" so we know all\n                               the \"Pawn\" tags will get removed on unpossess, but that removes some flexability for organization with gameplay tags. Havn't thought of a better way though. If you really feel you need this feature\n                               implemented somehow, it might be better to just make a new GAS setup with the ASC on the pawn class.\n               - Was struggling on comming up with a good system to determine what tags to remove on Unpossess. We could try removing any tags that has \"Pawn\" as one of the parents in the tag, but then this limits us\n                               us into only using tags with the parent of \"Pawn\" for pawn related stuff (ie. we wouldn't be able to throw a generic \"Actor.IsOnFire\" tag onto the pawn because then on Unpossess it wouldn't get removed).\n                               Another thing to think about is how we will remove these tags. This leads us into having to make a simple and efficient way to add/remove tags through code for all machines. Will we use a GE? This will take care of\n                               replicating it to all machines, but then you have to have a predefined GE asset that does it. But we would like to have the game figure out at runtime what tags to remove. Reliable RPCs using LooseGameplayTags is an\n                               option but not prefered, (not very efficient).\n                               if that tag is on our ASC, it wouldn't be removed.\n       6) AIAbilitySystemComponent\n               - Subclasses can disable this feature by calling DoNotCreateDefaultSubobject through the constructor using the Super's ObjectInitializer\n Some problems to avoid:\n       1) Keeping your attribute set registered on UnPossessed will give you problems if your newly registered attribute set is the same as the old attribute set (or both old and new attribute sets have a same attribute from a shared parent)\n               - Have a different attribute set for every pawn and avoid inheriting attributes from a parent attribute set\n       2) If you unpossess a pawn and unregister his attribute sets, his attributes are no longer associated with an ASC\n               - Don't apply effects to pawns that have unregistered attribute sets (it will crash)\n                       -(Possible future solution: have the AIAbilitySystemComponent take over when a player unpossesses a pawn and unregisters its attributes and register those attribute sets with the AI ASC)\n                       -(Possible work around: have an AI controller possess the unpossessed pawn which will call SetUpWithAbilitySystem for the AIAbilitySystemComponent and register those attribute with the AI ASC)" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PawnAttributeSet_MetaData[] = {
		{ "Comment", "/** Every pawn will have this attribute set. This is useful because this gives you a place for common attributes that every pawn should have. Children can make another attribute set specific to their pawn (ie. UAS_Demoman, UAS_Ganondorf) */" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Every pawn will have this attribute set. This is useful because this gives you a place for common attributes that every pawn should have. Children can make another attribute set specific to their pawn (ie. UAS_Demoman, UAS_Ganondorf)" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PawnAttributeSet = { "PawnAttributeSet", nullptr, (EPropertyFlags)0x0040000000080028, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, PawnAttributeSet), Z_Construct_UClass_UAS_Pawn_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PawnAttributeSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PawnAttributeSet_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponent = { "AIAbilitySystemComponent", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, AIAbilitySystemComponent), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PlayerAbilitySystemComponent_MetaData[] = {
		{ "Comment", "/*Replicated*/// Replicated can be helpful for debugging issues\n" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Replicated// Replicated can be helpful for debugging issues" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PlayerAbilitySystemComponent = { "PlayerAbilitySystemComponent", nullptr, (EPropertyFlags)0x0040000000080008, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, PlayerAbilitySystemComponent), Z_Construct_UClass_USSAbilitySystemComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PlayerAbilitySystemComponent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PlayerAbilitySystemComponent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/**\n\x09   ---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllPawnTags() FOR THIS TO DO SOMETHING---\n\x09 * Removes all tags relating to this specific pawn from the PlayerState's ASC\n\x09 * Remove all tags related to the pawn, that way when we possess a new pawn,\n\x09 * the old tags don't interfere with the new pawn.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "---CURRENTLY DOES NOTHING. IMPLEMENT RemoveAllPawnTags() FOR THIS TO DO SOMETHING---\nRemoves all tags relating to this specific pawn from the PlayerState's ASC\nRemove all tags related to the pawn, that way when we possess a new pawn,\nthe old tags don't interfere with the new pawn." },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemPawn*)Obj)->bRemovePawnTagsOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed = { "bRemovePawnTagsOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemPawn), &Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/** Remove all abilities that this object owns on unpossess */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Remove all abilities that this object owns on unpossess" },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemPawn*)Obj)->bRemoveAbilitiesOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed = { "bRemoveAbilitiesOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemPawn), &Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Config" },
		{ "Comment", "/**\n\x09 * Takes this object's AttributeSet(s) away from the player's ASC. This is on by default to prevent the potential problem of the ASC having 2 attribute sets of the same class.\n\x09 * However if the ASC no longer has this object's AttributeSet, GameplayEffects can no longet modify their attributes.\n\x09 */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Takes this object's AttributeSet(s) away from the player's ASC. This is on by default to prevent the potential problem of the ASC having 2 attribute sets of the same class.\nHowever if the ASC no longer has this object's AttributeSet, GameplayEffects can no longet modify their attributes." },
	};
#endif
	void Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_SetBit(void* Obj)
	{
		((AAbilitySystemPawn*)Obj)->bUnregisterAttributeSetsOnUnpossessed = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed = { "bUnregisterAttributeSetsOnUnpossessed", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(AAbilitySystemPawn), &Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_SetBit, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_SSPlayerState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_SSPlayerState = { "SSPlayerState", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, SSPlayerState), Z_Construct_UClass_ASSPlayerState_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_SSPlayerState_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_SSPlayerState_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData[] = {
		{ "Category", "AbilitySystemSetup|AI" },
		{ "Comment", "/** Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Decide which replication mode you want for the AIAbilitySystemComponent. Should normally be set to Minimal. Only change if you know what your doing" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode = { "AIAbilitySystemComponentReplicationMode", nullptr, (EPropertyFlags)0x0020080000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, AIAbilitySystemComponentReplicationMode), Z_Construct_UEnum_GameplayAbilities_EGameplayEffectReplicationMode, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen) */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "These effects are only applied one time on startup (ie. GE_HealthRegen, GE_StaminaRegen)" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, EffectsToApplyOnStartup), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup_MetaData)) };
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup_Inner = { "EffectsToApplyOnStartup", nullptr, (EPropertyFlags)0x0004000000000000, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_DefaultAttributeValuesEffect_MetaData[] = {
		{ "Category", "AbilitySystemSetup|Effects" },
		{ "Comment", "/** Default attributes values for a Pawn on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Pawn's starting attribute values will be on spawn */" },
		{ "ModuleRelativePath", "Public/Pawn/AbilitySystemPawn.h" },
		{ "ToolTip", "Default attributes values for a Pawn on spawn. This should be an instant GE with the Modifier Op set to Override so you can choose what the Pawn's starting attribute values will be on spawn" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_DefaultAttributeValuesEffect = { "DefaultAttributeValuesEffect", nullptr, (EPropertyFlags)0x0024080000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AAbilitySystemPawn, DefaultAttributeValuesEffect), Z_Construct_UClass_UGameplayEffect_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_DefaultAttributeValuesEffect_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_DefaultAttributeValuesEffect_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAbilitySystemPawn_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PawnAttributeSet,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_PlayerAbilitySystemComponent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemovePawnTagsOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bRemoveAbilitiesOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_bUnregisterAttributeSetsOnUnpossessed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_SSPlayerState,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_AIAbilitySystemComponentReplicationMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_EffectsToApplyOnStartup_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAbilitySystemPawn_Statics::NewProp_DefaultAttributeValuesEffect,
	};
		const UE4CodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_AAbilitySystemPawn_Statics::InterfaceParams[] = {
			{ Z_Construct_UClass_UAbilitySystemInterface_NoRegister, (int32)VTABLE_OFFSET(AAbilitySystemPawn, IAbilitySystemInterface), false },
		};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAbilitySystemPawn_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAbilitySystemPawn>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AAbilitySystemPawn_Statics::ClassParams = {
		&AAbilitySystemPawn::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AAbilitySystemPawn_Statics::PropPointers,
		InterfaceParams,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::PropPointers),
		UE_ARRAY_COUNT(InterfaceParams),
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AAbilitySystemPawn_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AAbilitySystemPawn_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AAbilitySystemPawn()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AAbilitySystemPawn_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AAbilitySystemPawn, 2513820483);
	template<> SONICSIEGE_API UClass* StaticClass<AAbilitySystemPawn>()
	{
		return AAbilitySystemPawn::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AAbilitySystemPawn(Z_Construct_UClass_AAbilitySystemPawn, &AAbilitySystemPawn::StaticClass, TEXT("/Script/SonicSiege"), TEXT("AAbilitySystemPawn"), false, nullptr, nullptr, nullptr);

	void AAbilitySystemPawn::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
	{
		static const FName Name_PawnAttributeSet(TEXT("PawnAttributeSet"));

		const bool bIsValid = true
			&& Name_PawnAttributeSet == ClassReps[(int32)ENetFields_Private::PawnAttributeSet].Property->GetFName();

		checkf(bIsValid, TEXT("UHT Generated Rep Indices do not match runtime populated Rep Indices for properties in AAbilitySystemPawn"));
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAbilitySystemPawn);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
