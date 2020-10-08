// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SonicSiege/Public/AbilitySystem/SSAbilitySystemComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSSAbilitySystemComponent() {}
// Cross Module References
	SONICSIEGE_API UEnum* Z_Construct_UEnum_SonicSiege_EAbilityInputID();
	UPackage* Z_Construct_UPackage__Script_SonicSiege();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister();
	SONICSIEGE_API UClass* Z_Construct_UClass_USSAbilitySystemComponent();
	GAMEPLAYABILITIES_API UClass* Z_Construct_UClass_UAbilitySystemComponent();
// End Cross Module References
	static UEnum* EAbilityInputID_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_SonicSiege_EAbilityInputID, Z_Construct_UPackage__Script_SonicSiege(), TEXT("EAbilityInputID"));
		}
		return Singleton;
	}
	template<> SONICSIEGE_API UEnum* StaticEnum<EAbilityInputID>()
	{
		return EAbilityInputID_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EAbilityInputID(EAbilityInputID_StaticEnum, TEXT("/Script/SonicSiege"), TEXT("EAbilityInputID"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_SonicSiege_EAbilityInputID_Hash() { return 2227178200U; }
	UEnum* Z_Construct_UEnum_SonicSiege_EAbilityInputID()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_SonicSiege();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EAbilityInputID"), 0, Get_Z_Construct_UEnum_SonicSiege_EAbilityInputID_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EAbilityInputID::None", (int64)EAbilityInputID::None },
				{ "EAbilityInputID::Jump", (int64)EAbilityInputID::Jump },
				{ "EAbilityInputID::Interact", (int64)EAbilityInputID::Interact },
				{ "EAbilityInputID::Run", (int64)EAbilityInputID::Run },
				{ "EAbilityInputID::PrimaryFire", (int64)EAbilityInputID::PrimaryFire },
				{ "EAbilityInputID::SecondaryFire", (int64)EAbilityInputID::SecondaryFire },
				{ "EAbilityInputID::Reload", (int64)EAbilityInputID::Reload },
				{ "EAbilityInputID::Crouch", (int64)EAbilityInputID::Crouch },
				{ "EAbilityInputID::SwitchWeapon", (int64)EAbilityInputID::SwitchWeapon },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Comment", "/**\n *\x09""Enum that makes GAS aware of which abilities are binded to which input in your project settings.\n *\x09""Each ability must be assigned one of these when granting an ability (unless you don't care about using some of UE4's wait for input AbilityTasks).\n *\n *\x09""Do not forget to update this enum whenever you modify the inputs in your project settings. They must match exactly. =@REVIEW MARKER@=\n *\x09""Also I do not know yet if you need to do a normal input bind in the SetupPlayerInputComponent() for ConfirmTarget and CancelTarget to\n *\x09manually call the confirm and cancel functions for target actors or if GAS internally listens for those inputs when a TargetActor is active without\n *\x09the need for you to call a function to activate a confirm or cancel. My guess though is that it does it internally for you when a target actor is active.\n *\x09""Confirm and cancel target was not looked into enough yet to know if it works fully or not yet.\n */" },
				{ "Crouch.Comment", "// 7 Crouch\n" },
				{ "Crouch.DisplayName", "Crouch" },
				{ "Crouch.Name", "EAbilityInputID::Crouch" },
				{ "Crouch.ToolTip", "7 Crouch" },
				{ "Interact.Comment", "// 2 Interact\n" },
				{ "Interact.DisplayName", "Interact" },
				{ "Interact.Name", "EAbilityInputID::Interact" },
				{ "Interact.ToolTip", "2 Interact" },
				{ "Jump.Comment", "// 1 Jump\n" },
				{ "Jump.DisplayName", "Jump" },
				{ "Jump.Name", "EAbilityInputID::Jump" },
				{ "Jump.ToolTip", "1 Jump" },
				{ "ModuleRelativePath", "Public/AbilitySystem/SSAbilitySystemComponent.h" },
				{ "None.Comment", "// 0 None\n" },
				{ "None.DisplayName", "None" },
				{ "None.Name", "EAbilityInputID::None" },
				{ "None.ToolTip", "0 None" },
				{ "PrimaryFire.Comment", "// 4 PrimaryFire\n" },
				{ "PrimaryFire.DisplayName", "Primary Fire" },
				{ "PrimaryFire.Name", "EAbilityInputID::PrimaryFire" },
				{ "PrimaryFire.ToolTip", "4 PrimaryFire" },
				{ "Reload.Comment", "// 6 Reload\n" },
				{ "Reload.DisplayName", "Reload" },
				{ "Reload.Name", "EAbilityInputID::Reload" },
				{ "Reload.ToolTip", "6 Reload" },
				{ "Run.Comment", "// 3 Run\n" },
				{ "Run.DisplayName", "Sprint" },
				{ "Run.Name", "EAbilityInputID::Run" },
				{ "Run.ToolTip", "3 Run" },
				{ "SecondaryFire.Comment", "// 5 SecondaryFire\n" },
				{ "SecondaryFire.DisplayName", "Secondary Fire" },
				{ "SecondaryFire.Name", "EAbilityInputID::SecondaryFire" },
				{ "SecondaryFire.ToolTip", "5 SecondaryFire" },
				{ "SwitchWeapon.Comment", "// 8 Switch Weapon\n" },
				{ "SwitchWeapon.DisplayName", "Switch Weapon" },
				{ "SwitchWeapon.Name", "EAbilityInputID::SwitchWeapon" },
				{ "SwitchWeapon.ToolTip", "8 Switch Weapon" },
				{ "ToolTip", "Enum that makes GAS aware of which abilities are binded to which input in your project settings.\nEach ability must be assigned one of these when granting an ability (unless you don't care about using some of UE4's wait for input AbilityTasks).\n\nDo not forget to update this enum whenever you modify the inputs in your project settings. They must match exactly. =@REVIEW MARKER@=\nAlso I do not know yet if you need to do a normal input bind in the SetupPlayerInputComponent() for ConfirmTarget and CancelTarget to\nmanually call the confirm and cancel functions for target actors or if GAS internally listens for those inputs when a TargetActor is active without\nthe need for you to call a function to activate a confirm or cancel. My guess though is that it does it internally for you when a target actor is active.\nConfirm and cancel target was not looked into enough yet to know if it works fully or not yet." },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_SonicSiege,
				nullptr,
				"EAbilityInputID",
				"EAbilityInputID",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	void USSAbilitySystemComponent::StaticRegisterNativesUSSAbilitySystemComponent()
	{
	}
	UClass* Z_Construct_UClass_USSAbilitySystemComponent_NoRegister()
	{
		return USSAbilitySystemComponent::StaticClass();
	}
	struct Z_Construct_UClass_USSAbilitySystemComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USSAbilitySystemComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAbilitySystemComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_SonicSiege,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USSAbilitySystemComponent_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Our custom base ability system component\n */" },
		{ "HideCategories", "Object LOD Lighting Transform Sockets TextureStreaming Object LOD Lighting Transform Sockets TextureStreaming" },
		{ "IncludePath", "AbilitySystem/SSAbilitySystemComponent.h" },
		{ "ModuleRelativePath", "Public/AbilitySystem/SSAbilitySystemComponent.h" },
		{ "ToolTip", "Our custom base ability system component" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USSAbilitySystemComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USSAbilitySystemComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USSAbilitySystemComponent_Statics::ClassParams = {
		&USSAbilitySystemComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_USSAbilitySystemComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USSAbilitySystemComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USSAbilitySystemComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USSAbilitySystemComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USSAbilitySystemComponent, 3197671151);
	template<> SONICSIEGE_API UClass* StaticClass<USSAbilitySystemComponent>()
	{
		return USSAbilitySystemComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USSAbilitySystemComponent(Z_Construct_UClass_USSAbilitySystemComponent, &USSAbilitySystemComponent::StaticClass, TEXT("/Script/SonicSiege"), TEXT("USSAbilitySystemComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USSAbilitySystemComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
