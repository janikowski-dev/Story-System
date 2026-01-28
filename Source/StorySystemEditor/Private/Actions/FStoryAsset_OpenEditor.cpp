#include "FStoryAsset_OpenEditor.h"
#include "Assets/UStoryAsset.h"
#include "Editors/FStoryAssetEditor.h"

void FStoryAsset_OpenEditor::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	for (UObject* Object : InObjects)
	{
		UStoryAsset* Asset = Cast<UStoryAsset>(Object);
		
		if (!Asset)
		{
			continue;
		}
		
		const TSharedRef<FStoryAssetEditor> Editor = MakeShared<FStoryAssetEditor>();

		Editor->InitStoryAssetEditor(
			EToolkitMode::Standalone,
			EditWithinLevelEditor,
			Asset
		);
	}
}
