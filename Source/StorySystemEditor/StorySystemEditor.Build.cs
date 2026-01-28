using UnrealBuildTool;

public class StorySystemEditor : ModuleRules
{
	public StorySystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine"
		]);
		
		PrivateDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"AssetTools",
			"EditorFramework",
			"Slate",
			"SlateCore",
			"GraphEditor",
			"ToolMenus",
			"InputCore",
			"WorkspaceMenuStructure"
		]);
	}
}
