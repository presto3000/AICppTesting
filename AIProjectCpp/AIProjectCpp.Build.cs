// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
public class AIProjectCpp : ModuleRules
{
	public AIProjectCpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] 
			{ "Core", 
				"CoreUObject",
				"Engine",
				"InputCore",
				"HeadMountedDisplay",
				"AIModule",
				"GameplayTasks",
				"NavigationSystem",
				"UMG", // user interface
				"Slate",// user interface
				"SlateCore"// user interface
			});
	}
}
