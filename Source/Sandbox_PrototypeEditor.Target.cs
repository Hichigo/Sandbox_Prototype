// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Sandbox_PrototypeEditorTarget : TargetRules
{
    public Sandbox_PrototypeEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
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
