#include "SStoryDialogueNode.h"
#include "Nodes/Unreal/UStoryDialogueNode.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

void SStoryDialogueNode::Construct(const FArguments&, UStoryDialogueNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

void SStoryDialogueNode::UpdateGraphNode()
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
		.MinDesiredHeight(150.0f)
		.MinDesiredWidth(275.0f)
		[
			SNew(SMultiLineEditableTextBox)
			.Text(this, &SStoryDialogueNode::GetDialogueText)
			.OnTextCommitted(this, &SStoryDialogueNode::OnDialogueCommitted)
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

FText SStoryDialogueNode::GetDialogueText() const
{
	return CastChecked<UStoryDialogueNode>(GraphNode)->DialogueText;
}

void SStoryDialogueNode::OnDialogueCommitted(const FText& NewText, ETextCommit::Type) const
{
	UStoryDialogueNode* Node = CastChecked<UStoryDialogueNode>(GraphNode);
	Node->Modify();
	Node->DialogueText = NewText;
}
