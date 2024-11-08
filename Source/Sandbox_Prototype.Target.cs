// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Sandbox_PrototypeTarget : TargetRules
{
    public Sandbox_PrototypeTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("Sandbox_Prototype");
        RegisterModulesCreatedByRider();
    }

    private void RegisterModulesCreatedByRider()
    {
        ExtraModuleNames.AddRange(new string[] { "SandboxEditor", "SandboxTests" });
    }
}
