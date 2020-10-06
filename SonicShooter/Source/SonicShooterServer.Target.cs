// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SonicShooterServerTarget : TargetRules
{
	//[SupportedPlatforms(UnrealPlatformClass.Server)]
	public SonicShooterServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SonicShooter");
	}
}
