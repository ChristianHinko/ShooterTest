// Copyright 2017-2020 Puny Human, All Rights Reserved.

using UnrealBuildTool;

public class ArcTeams : ModuleRules
{
	public ArcTeams(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/ArcTeams.h";


        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				 "GameplayTags",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			});
		
	}
}
