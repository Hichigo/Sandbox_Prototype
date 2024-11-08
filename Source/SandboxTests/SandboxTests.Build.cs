using UnrealBuildTool;

public class SandboxTests : ModuleRules
{
    public SandboxTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "Slate", "SlateCore" });

        PublicIncludePaths.AddRange(new string[] { "SandboxTests" });

        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PublicDependencyModuleNames.Add("FunctionalTesting");
        }
    }
}