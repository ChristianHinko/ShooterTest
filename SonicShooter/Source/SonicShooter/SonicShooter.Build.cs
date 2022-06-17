// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SonicShooter : ModuleRules
{
	public SonicShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Private/SonicShooterPrivatePCH.h";

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
				"HelperLibraries",
				"PropertyWrapper",
				"AnimationSetup",
				"AutoSettings",
				"ArcInventory",
				"AnimGraphRuntime" // for KismetAnimationLibrary
			}
		);
	}
}
