// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BronzeSoul : ModuleRules
{
	public BronzeSoul(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "BronzeSoul" });
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "NavigationSystem", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
