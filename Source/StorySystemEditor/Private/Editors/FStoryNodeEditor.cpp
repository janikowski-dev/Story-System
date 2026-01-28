#include "FStoryNodeEditor.h"

#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Nodes/Unreal/UStoryNode.h"

static const FName NodeGraphTabName(TEXT("NodeGraph"));

void FStoryNodeEditor::InitNodeAssetEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UStoryNode* Node
)
{
	const TSharedRef<FTabManager::FLayout> Layout =
		FTabManager::NewLayout("NodeAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(NodeGraphTabName, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(Node);
	EditedNode = Node;

	InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		true,
		true,
		ObjectsToEdit
	);

	RegenerateMenusAndToolbars();
}

void FStoryNodeEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(
		NodeGraphTabName,
		FOnSpawnTab::CreateRaw(this, &FStoryNodeEditor::SpawnGraphTab)
	)
	.SetDisplayName(FText::FromString("Node Graph"));
}

void FStoryNodeEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(NodeGraphTabName);
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

TSharedRef<SDockTab> FStoryNodeEditor::SpawnGraphTab(const FSpawnTabArgs&)
{
	GraphEditor = SNew(SGraphEditor)
		.GraphToEdit(EditedNode->GetInnerGraph())
		.IsEditable(true);
	
	return SNew(SDockTab)
		.Label(FText::FromString("Node Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}

FName FStoryNodeEditor::GetToolkitFName() const
{
	return FName("NodeAssetEditor");
}

FText FStoryNodeEditor::GetBaseToolkitName() const
{
	return FText::FromString("Node Asset Editor");
}

FString FStoryNodeEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("Node");
}

FLinearColor FStoryNodeEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.1f, 0.6f, 1.0f);
}