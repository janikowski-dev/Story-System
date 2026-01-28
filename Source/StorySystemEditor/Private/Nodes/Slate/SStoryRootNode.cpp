#include "SStoryRootNode.h"

#include "Nodes/Unreal/URootStoryNode.h"

void SStoryRootNode::Construct(const FArguments&, URootStoryNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SStoryRootNode::UpdateGraphNode()
{
	SetupErrorReporting();

	const TSharedRef<SVerticalBox> NodeBody =
	SNew(SVerticalBox)

	// Title
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(4)
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("Root")))
	]

	// Pins row
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(2)
	[
		SNew(SHorizontalBox)

		// In pins (left)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(LeftNodeBox, SVerticalBox)
		]

		// Spacer
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			SNew(SSpacer)
		]

		// Out pins (right)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	];

	this->GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		[
			NodeBody
		]
	];

	CreatePinWidgets();
}
