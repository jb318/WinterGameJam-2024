// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TimeWarpC : ModuleRules
{
	public TimeWarpC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem" });
	}
}
