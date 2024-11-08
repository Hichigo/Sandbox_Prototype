// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sandbox_Prototype : ModuleRules
{
    public Sandbox_Prototype(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayTags",
            "StateTreeModule",
            "GameplayStateTreeModule",
            "AIModule",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {});

        // TODO: DELETE FOR SHIPPING
        OptimizeCode = CodeOptimization.Never;

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled
        // attribute set to true
    }
}
