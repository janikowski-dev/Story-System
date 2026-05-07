using UnrealBuildTool;

public class ChronicleCoreEditor : ModuleRules
{
	public ChronicleCoreEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine"
		]);
		
		PrivateDependencyModuleNames.AddRange([
			"ChronicleCore",
			"UnrealEd",
			"DeveloperSettings"
		]);
	}
}