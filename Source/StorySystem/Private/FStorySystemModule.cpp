#include "FStorySystemModule.h"
#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "Actions/FAssetTypeActions_Story.h"
#include "Factories/FStorySystemNodeFactory.h"

#define LOCTEXT_NAMESPACE "FStorySystemModule"

void FStorySystemModule::StartupModule()
{
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FStorySystemNodeFactory>());
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get()
	.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_Story>());
}

void FStorySystemModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStorySystemModule, StorySystem)