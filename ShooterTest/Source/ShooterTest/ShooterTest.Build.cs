// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ShooterTest : ModuleRules
{
	public ShooterTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Private/ShooterTestPrivatePCH.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"InputCore",
				"PhysicsCore",
				"SlateCore",
				"GameplayTags",
				"GameplayAbilities",
				"GameplayTasks",
				"NetCore", // for push model
				"UMG",
				"AbilitySystemSetup",
				"AbilitySystemSetupExtras",
				"GameCore",
				"GameSetup",
				"AutoSettings",
				"ArcInventory",
				"ArcInventoryExtension",
				"AnimGraphRuntime" // for KismetAnimationLibrary
			}
		);
	}
}
