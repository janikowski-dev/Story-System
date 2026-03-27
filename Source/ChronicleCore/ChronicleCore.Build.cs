using UnrealBuildTool;

public class ChronicleCore : ModuleRules
{
	public ChronicleCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"LevelSequence",
			"MovieScene",
			"MovieSceneTracks",
			"CinematicCamera"
		]);
		
		PrivateDependencyModuleNames.AddRange([]);
	}
}