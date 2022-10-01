// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ex_Cpp_Multiplayer : ModuleRules
{
	public Ex_Cpp_Multiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.AddRange(new string[] {"OnlineSubsystem", "OnlineSubsystemNull"});
	}
}