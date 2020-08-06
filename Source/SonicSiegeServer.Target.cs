// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SonicSiegeServerTarget : TargetRules
{
	//[SupportedPlatforms(UnrealPlatformClass.Server)]
	public SonicSiegeServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SonicSiege");
	}
}
