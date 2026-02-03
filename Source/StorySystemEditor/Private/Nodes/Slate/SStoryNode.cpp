#include "SStoryNode.h"

#include "Editors/FStoryNodeEditor.h"
#include "Nodes/Unreal/UStoryNode.h"
#include "Pins/SStoryGraphPin.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "SGraphPanel.h"
#include "Graphs/UStoryGraph.h"

void SStoryNode::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

TSharedPtr<SGraphPin> SStoryNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SStoryGraphPin, Pin);
}

TSharedPtr<SGraphPin> SStoryNode::GetHoveredPin(const FGeometry&, const FPointerEvent&) const
{
	return nullptr;
}

FReply SStoryNode::OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&)
{
	OpenNodeEditor();
	return FReply::Handled();
}

void SStoryNode::UpdateGraphNode()
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
	.WidgetIndex(this, &SStoryNode::GetBodyIndex)
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
		.BorderBackgroundColor(this, &SStoryNode::GetHeaderColor)
		[
			WidgetSwitcher.ToSharedRef()
		]
	];
	
	CreatePinWidgets();
}

void SStoryNode::AddHeader(const TSharedRef<SVerticalBox>& Box)
{
	const FText Title = GetTitle(Cast<UStoryNode>(GraphNode));
	
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
			.OnClicked(this, &SStoryNode::ToggleCollapse)
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

FReply SStoryNode::ToggleCollapse() const
{
	ToggleCollapsedState();
	ApplyCollapse();
	RefreshGraph();
	return FReply::Handled();
}

void SStoryNode::ApplyCollapse() const
{
	TSet<UStoryNode*> Visited;
	ApplyCollapse(TypedNode.Get(), false, Visited);
}

void SStoryNode::ApplyCollapse(
	UStoryNode* CurrentNode,
	const bool bParentHidden,
	TSet<UStoryNode*>& Visited
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
			if (UStoryNode* ChildNode = Cast<UStoryNode>(LinkedPin->GetOwningNode()))
			{
				ApplyCollapse(ChildNode, bHideChildren, Visited);
			}
		}
	}
}

void SStoryNode::ToggleCollapsedState() const
{
	TypedNode->bIsCollapsed = !TypedNode->bIsCollapsed;
}

void SStoryNode::RefreshGraph() const
{
	const UStoryGraph* TypedGraph = Cast<UStoryGraph>(GraphNode->GetGraph());
	TypedGraph->AutoLayout();
}

void SStoryNode::OpenNodeEditor() const
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

int SStoryNode::GetBodyIndex() const
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

void SStoryNode::Cache(UEdGraphNode* Node)
{
	TypedNode = Cast<UStoryNode>(Node);
	GraphNode = Node;
}
