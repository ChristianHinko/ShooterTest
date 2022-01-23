// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SonicShooter : ModuleRules
{
	public SonicShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Private/SonicShooterPCH.h";     // Only line needed for custom PCH if your using the default "UseExplicitOrSharedPCHs"

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
				"AutoSettings",
				"ArcInventory",
				"ArcTeams",
				"MoveIt",
				"UltimateFPSTemplate"
			}
		);
	}
}
