// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Return_To_The_Maul : ModuleRules
{
	public Return_To_The_Maul(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "SupportFunctions", "RTSPlayerController", "SimpleUIManager", "RTSToolkitInterfaces", "RTSEconomySystem", "RTSGamemode" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "SupportFunctions", "RTSUnitSystem" });
    }
}
