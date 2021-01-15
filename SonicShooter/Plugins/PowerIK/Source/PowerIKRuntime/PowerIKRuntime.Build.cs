/* 
Copyright 2020 Power Animated, All Rights Reserved.
Unauthorized copying, selling or distribution of this software is strictly prohibited.
*/

using UnrealBuildTool;
using System.IO;

public class PowerIKRuntime : ModuleRules
{
	public PowerIKRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
				"Engine",
				"AnimationCore",
                "AnimGraphRuntime",

				"ControlRig",
				"RigVM",

				// ... add other public dependencies that you statically link with here ...
			}
			);

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...
			}
			);


        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        // get base folder
        string ModulePath = ModuleDirectory + '/';
        ModulePath = ModulePath.Replace('\\', '/');

        // add sdk include paths
        string IncludeDir = Path.Combine(ModulePath, "sdk", "include");
        PublicIncludePaths.Add(IncludeDir);

        // add sdk src paths (source code license only)
        //string SrcDir = Path.Combine(ModulePath, "sdk", "src");
        //PrivateIncludePaths.Add(SrcDir);

        // add binary libraries
        bool POWERIK_BINARY_MODE = true;
        if (POWERIK_BINARY_MODE)
        {
            // add per-platform paths to PowerIK library
            string LibPath = Path.Combine(ModulePath, "sdk", "lib");
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                string Win64Path = Path.Combine(LibPath, "Win64");
                PublicRuntimeLibraryPaths.Add(Win64Path);
                PublicAdditionalLibraries.Add(Path.Combine(Win64Path, "POWERIK.lib"));

                // copy .dll next to executable
                string DllPath = Path.Combine(LibPath, "Win64", "POWERIK.dll");
                RuntimeDependencies.Add("$(BinaryOutputDir)/POWERIK.dll", DllPath);
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                string StaticLibPath = Path.Combine(LibPath, "Linux", "libPOWERIK.a");
                PublicAdditionalLibraries.Add(StaticLibPath);
            }
            else
            {
                // add support for additional binary platforms here...
            }
        }
    }
}
