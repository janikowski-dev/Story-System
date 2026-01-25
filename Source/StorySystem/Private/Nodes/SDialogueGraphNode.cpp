#include "SDialogueGraphNode.h"
#include "UDialogueGraphNode.h"
#include "Layout/StoryGraphLayout.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

void SDialogueGraphNode::Construct(const FArguments&, UDialogueGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SDialogueGraphNode::UpdateGraphNode()
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
		.Text(FText::FromString(TEXT("Dialogue")))
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

		// Spacer (pushes right pins to the edge)
		+ SHorizontalBox::Slot()
		.FillWidth(1.f)
		[
			SNew(SSpacer)
		]

		// Out pins (right)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(RightNodeBox, SVerticalBox)
		]
	]

	// Dialogue editor
	+ SVerticalBox::Slot()
	.AutoHeight()
	.Padding(4)
	[
		SNew(SBox)
		.MinDesiredHeight(NodeHeight)
		.MinDesiredWidth(NodeWidth)
		[
			SNew(SMultiLineEditableTextBox)
			.Text(this, &SDialogueGraphNode::GetDialogueText)
			.OnTextCommitted(this, &SDialogueGraphNode::OnDialogueCommitted)
			.AutoWrapText(true)
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

FText SDialogueGraphNode::GetDialogueText() const
{
	return CastChecked<UDialogueGraphNode>(GraphNode)->DialogueText;
}

void SDialogueGraphNode::OnDialogueCommitted(const FText& NewText, ETextCommit::Type) const
{
	UDialogueGraphNode* Node = CastChecked<UDialogueGraphNode>(GraphNode);
	Node->Modify();
	Node->DialogueText = NewText;
}
