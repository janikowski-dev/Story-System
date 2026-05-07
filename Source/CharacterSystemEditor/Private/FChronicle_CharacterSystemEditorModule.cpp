#include "FChronicle_CharacterSystemEditorModule.h"

#include "FChronicle_CharacterDirectory.h"
#include "FChronicle_EmotionIdCustomization.h"

#define LOCTEXT_NAMESPACE "ChronicleCharacterSystemEditorModule"

void FChronicle_CharacterSystemEditorModule::StartupModule()
{
	FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").RegisterCustomPropertyTypeLayout(
		"Chronicle_EmotionId",
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FChronicle_EmotionIdCustomization::MakeInstance)
	);
	FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").NotifyCustomizationModuleChanged();
	
	FChronicle_CharacterDirectory::Refresh();
}

void FChronicle_CharacterSystemEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		return;
	}

	FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").UnregisterCustomPropertyTypeLayout("Chronicle_EmotionId");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChronicle_CharacterSystemEditorModule, CharacterSystemEditor)