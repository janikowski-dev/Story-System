#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"

class UStoryAsset;
class SGraphEditor;

class FStoryAssetEditor : public FAssetEditorToolkit
{
public:
	void InitStoryAssetEditor(
		const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		UStoryAsset* Asset
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
	
	bool CanDeleteNodes() const;
	void DeleteSelectedNodes() const;

private:
	TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& Args);

private:
	TSharedPtr<FUICommandList> GraphCommands;
	TSharedPtr<SGraphEditor> GraphEditor;
	UStoryAsset* EditedAsset = nullptr;
};