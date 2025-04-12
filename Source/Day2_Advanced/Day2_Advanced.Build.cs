// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Day2_Advanced : ModuleRules
{
	public Day2_Advanced(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
