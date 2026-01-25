#include "SRootGraphNode.h"
#include "URootGraphNode.h"

void SRootGraphNode::Construct(const FArguments&, URootGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SRootGraphNode::UpdateGraphNode()
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
