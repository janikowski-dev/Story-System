#include "SStoryNode.h"

#include "Editors/FStoryNodeEditor.h"
#include "Nodes/Unreal/UStoryNode.h"
#include "Pins/SStoryGraphPin.h"

void SStoryNode::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

TSharedPtr<SGraphPin> SStoryNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SStoryGraphPin, Pin);
}

TSharedPtr<SGraphPin> SStoryNode::GetHoveredPin(
	const FGeometry& MyGeometry,
	const FPointerEvent& MouseEvent
) const
{
	return nullptr;
}

FReply SStoryNode::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
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
	
	return FReply::Handled();
}
