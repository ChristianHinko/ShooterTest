// Copyright 2017-2020 Puny Human, All Rights Reserved.

using UnrealBuildTool;

public class ArcInventory : ModuleRules
{
	public ArcInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "UMG",
                "DeveloperSettings",
            });
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});
	}
}
