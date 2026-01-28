#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"

class UStoryNode;

class STORYSYSTEMEDITOR_API FStoryNodeEditor : public FAssetEditorToolkit
{
public:
	void InitNodeAssetEditor(
		const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		UStoryNode* Node
	);
	
	virtual void RegisterTabSpawners(
		const TSharedRef<FTabManager>& InTabManager
	) override;

	virtual void UnregisterTabSpawners(
		const TSharedRef<FTabManager>& InTabManager
	) override;

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& Args);

private:
	TSharedPtr<SGraphEditor> GraphEditor;
	UStoryNode* EditedNode = nullptr;
};
