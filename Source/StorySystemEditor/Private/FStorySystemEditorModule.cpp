#include "FStorySystemEditorModule.h"

#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "Actions/FStoryAsset_OpenEditor.h"
#include "Factories/FRuleNodeFactory.h"
#include "Factories/FStoryNodeFactory.h"

#define LOCTEXT_NAMESPACE "FStorySystemModule"

void FStorySystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAssetTypeActions(MakeShared<FStoryAsset_OpenEditor>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FStoryNodeFactory>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FRuleNodeFactory>());
}

void FStorySystemEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStorySystemEditorModule, StorySystem)