// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FinalProject : ModuleRules
{
	public FinalProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem", "AIModule", "MediaAssets", "Niagara", "Json", "LevelSequence" });

	}
}
