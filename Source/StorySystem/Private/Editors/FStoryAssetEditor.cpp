#include "FStoryAssetEditor.h"

#include "Assets/UStoryAsset.h"
#include "Graphs/UStoryGraph.h"

#include "GraphEditor.h"
#include "GraphEditorActions.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Nodes/URootGraphNode.h"

static const FName StoryGraphTabName(TEXT("StoryGraph"));

void FStoryAssetEditor::InitStoryAssetEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UStoryAsset* Asset
)
{
	EditedAsset = Asset;

	const TSharedRef<FTabManager::FLayout> Layout =
		FTabManager::NewLayout("StoryAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(StoryGraphTabName, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);

	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(Asset);

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

void FStoryAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(
		StoryGraphTabName,
		FOnSpawnTab::CreateRaw(this, &FStoryAssetEditor::SpawnGraphTab)
	)
	.SetDisplayName(FText::FromString("Story Graph"));
}

void FStoryAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(StoryGraphTabName);
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

TSharedRef<SDockTab> FStoryAssetEditor::SpawnGraphTab(const FSpawnTabArgs&)
{
	GraphCommands = MakeShared<FUICommandList>();

	GraphCommands->MapAction(
		FGraphEditorCommands::Get().DeleteAndReconnectNodes,
		FExecuteAction::CreateSP(this, &FStoryAssetEditor::DeleteSelectedNodes),
		FCanExecuteAction::CreateSP(this, &FStoryAssetEditor::CanDeleteNodes)
	);
	
	GraphEditor = SNew(SGraphEditor)
		.GraphToEdit(EditedAsset->Graph)
		.AdditionalCommands(GraphCommands)
		.IsEditable(true);

	return SNew(SDockTab)
		.Label(FText::FromString("Story Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}

bool FStoryAssetEditor::CanDeleteNodes() const
{
	if (!GraphEditor.IsValid())
	{
		return false;
	}
	
	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();

	if (SelectedNodes.Num() == 0)
	{
		return false;
	}
	
	for (UObject* Node : SelectedNodes)
	{
		if (Cast<URootGraphNode>(Node))
		{
			return false;
		}
	}

	return true;
}

void FStoryAssetEditor::DeleteSelectedNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = GraphEditor->GetSelectedNodes();

	GraphEditor->ClearSelectionSet();

	for (UObject* Obj : SelectedNodes)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(Obj))
		{
			Node->GetGraph()->RemoveNode(Node);
		}
	}

	GraphEditor->NotifyGraphChanged();
}

FName FStoryAssetEditor::GetToolkitFName() const
{
	return FName("StoryAssetEditor");
}

FText FStoryAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString("Story Asset Editor");
}

FString FStoryAssetEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("Story");
}

FLinearColor FStoryAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.1f, 0.6f, 1.0f);
}