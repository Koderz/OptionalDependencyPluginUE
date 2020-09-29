// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PluginDependencyTest : ModuleRules
{
	public PluginDependencyTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
