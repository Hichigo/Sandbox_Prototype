using UnrealBuildTool;

public class SandboxEditor : ModuleRules
{
    public SandboxEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "AssetTools",
            "Sandbox_Prototype",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "Slate",
            "SlateCore",
            "Sandbox_Prototype",
        });
    }
}