#include "SDialogueNode.h"

#include "Nodes/Unreal/UDialogueNode.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Nodes/Unreal/UDialogueLinkNode.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"
#include "Nodes/Unreal/UDialogueRootNode.h"

#include "Pins/SDialogueGraphPin.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "SGraphPanel.h"
#include "Graphs/UDialogueGraph.h"

template<typename TNodeType>
void SDialogueNode<TNodeType>::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

template<typename TNodeType>
TSharedPtr<SGraphPin> SDialogueNode<TNodeType>::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SDialogueGraphPin, Pin);
}

template<typename TNodeType>
TSharedPtr<SGraphPin> SDialogueNode<TNodeType>::GetHoveredPin(const FGeometry&, const FPointerEvent&) const
{
	return nullptr;
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
	SetupErrorReporting();

	const TSharedRef<SVerticalBox> RegularView = SNew(SVerticalBox);
	const TSharedRef<SVerticalBox> CollapsedView = SNew(SVerticalBox);
	const TSharedRef<SWidget> HiddenView = SNew(SSpacer);
	
	SAssignNew(LeftNodeBox, SVerticalBox);
	SAssignNew(RightNodeBox, SVerticalBox);

	AddHeader(CollapsedView);
	AddHeader(RegularView);
	AddBody(RegularView);
	
	SAssignNew(WidgetSwitcher, SWidgetSwitcher)
	.WidgetIndex(this, &SDialogueNode::GetBodyIndex)
	+ SWidgetSwitcher::Slot()
	[
		RegularView
	]

	+ SWidgetSwitcher::Slot()
	[
		CollapsedView
	]

	+ SWidgetSwitcher::Slot()
	[
		HiddenView
	];

	RemoveSlot(ENodeZone::Center);
	
	GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		.BorderBackgroundColor(this, &SDialogueNode::GetHeaderColor)
		[
			WidgetSwitcher.ToSharedRef()
		]
	];
	
	CreatePinWidgets();
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::AddHeader(const TSharedRef<SVerticalBox>& Box)
{
	const FText Title = TypedNode->GetTitle();
	
	Box->AddSlot()
	.AutoHeight()
	[
		SNew(SOverlay)
		
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.WidthOverride(275.0f)
			.Padding(4)
			[
				SNew(STextBlock)
				.Text(Title)
			]
		]

		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				LeftNodeBox.ToSharedRef()
			]
			
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SSpacer)
			]

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				RightNodeBox.ToSharedRef()
			]
		]

		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
			.ContentPadding(FMargin(4))
			.ClickMethod(EButtonClickMethod::MouseDown)
			.OnClicked(this, &SDialogueNode::ToggleCollapse)
			[
				SNew(SImage)
				.Image_Lambda([this]()
				{
					return TypedNode->bIsCollapsed
						? FAppStyle::Get().GetBrush("Icons.ChevronRight")
						: FAppStyle::Get().GetBrush("Icons.ChevronDown");
				})
			]
		]
	];
}

template<typename TNodeType>
FReply SDialogueNode<TNodeType>::ToggleCollapse() const
{
	ToggleCollapsedState();
	ApplyCollapse();
	RefreshGraph();
	return FReply::Handled();
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::ApplyCollapse() const
{
	TSet<UDialogueNode*> Visited;
	ApplyCollapse(TypedNode.Get(), false, Visited);
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::ApplyCollapse(
	UDialogueNode* CurrentNode,
	const bool bParentHidden,
	TSet<UDialogueNode*>& Visited
) const
{
	if (!CurrentNode || Visited.Contains(CurrentNode))
	{
		return;
	}

	Visited.Add(CurrentNode);
	CurrentNode->bIsHidden = bParentHidden;
	const bool bHideChildren = bParentHidden || CurrentNode->bIsCollapsed;

	for (UEdGraphPin* Pin : CurrentNode->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
		{
			if (UDialogueNode* ChildNode = Cast<UDialogueNode>(LinkedPin->GetOwningNode()))
			{
				ApplyCollapse(ChildNode, bHideChildren, Visited);
			}
		}
	}
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::ToggleCollapsedState() const
{
	TypedNode->bIsCollapsed = !TypedNode->bIsCollapsed;
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::RefreshGraph() const
{
	const UDialogueGraph* TypedGraph = Cast<UDialogueGraph>(GraphNode->GetGraph());
	TypedGraph->Refresh();
}

template<typename TNodeType>
int SDialogueNode<TNodeType>::GetBodyIndex() const
{
	if (TypedNode->bIsCollapsed)
	{
		return Collapsed;
	}

	if (TypedNode->bIsHidden)
	{
		return Hidden;
	}
	
	return Regular;
}

template<typename TNodeType>
void SDialogueNode<TNodeType>::Cache(UEdGraphNode* Node)
{
	TypedNode = Cast<TNodeType>(Node);
	GraphNode = Node;
}

template class SDialogueNode<UDialogueResponseNode>;
template class SDialogueNode<UDialogueLineNode>;
template class SDialogueNode<UDialogueLinkNode>;
template class SDialogueNode<UDialogueRootNode>;
