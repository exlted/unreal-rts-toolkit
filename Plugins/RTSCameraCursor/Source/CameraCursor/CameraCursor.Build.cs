using UnrealBuildTool;

public class CameraCursor : ModuleRules
{
    public CameraCursor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "SupportFunctions", "RTSToolkitInterfaces", "SimpleAttachmentSystem"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG", "SimpleUIManager"
            }
        );
    }
}