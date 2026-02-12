#include "SStoryResponseNode.h"

#include "Editors/FStoryNodeEditor.h"
#include "Nodes/Unreal/UStoryResponseNode.h"

void SStoryResponseNode::Construct(const FArguments&, UStoryResponseNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
	DocumentManager = MakeShared<FDocumentTracker>();
}

FText SStoryResponseNode::GetTitle(UStoryNode* Node)
{
	const UStoryResponseNode* Response = Cast<UStoryResponseNode>(Node);
	return FText::Format(FText::FromString("Response #{0}.{1}"), Response->ParentIndex, Response->OrderIndex);
}

FSlateColor SStoryResponseNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Blue);
}

FReply SStoryResponseNode::OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&)
{
	OpenNodeEditor();
	return FReply::Handled();
}

void SStoryResponseNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SStoryResponseNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SStoryResponseNode::SetText)
	);
}

FText SStoryResponseNode::GetText() const
{
	return CastChecked<UStoryResponseNode>(GraphNode)->Text;
}

void SStoryResponseNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UStoryResponseNode* Node = CastChecked<UStoryResponseNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}

void SStoryResponseNode::OpenNodeEditor() const
{
	if (UStoryNode* NodeAsset = Cast<UStoryNode>(GraphNode))
	{
		const TSharedRef<FStoryNodeEditor> Editor = MakeShared<FStoryNodeEditor>();

		Editor->InitNodeAssetEditor(
			EToolkitMode::Standalone,
			TSharedPtr<IToolkitHost>(),
			NodeAsset
		);
	}
}
