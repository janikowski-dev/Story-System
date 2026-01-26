#include "UStoryGraph.h"

#include "Nodes/URootGraphNode.h"
#include "Nodes/UStoryGraphNode.h"

void UStoryGraph::PostLoad()
{
	Super::PostLoad();
	AutoLayout();
}

void UStoryGraph::AutoLayout() const
{
	constexpr float CellWidth  = 350.0f;
	constexpr float CellHeight = 300.0f;
	float CursorY = 0.0f;

	TMap<UStoryGraphNode*, FStoryLayoutNode*> LayoutMap;
	FStoryLayoutNode* Layout = BuildLayoutTree(GetRootNode(), LayoutMap);
	LayoutSubtree(Layout, CursorY, CellHeight);
	ApplyLayout(Layout, 0, CellWidth);
}

UStoryGraphNode* UStoryGraph::GetRootNode() const
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (auto* Root = Cast<URootGraphNode>(Node))
		{
			return Root;
		}
	}
	
	return nullptr;
}

FStoryLayoutNode* UStoryGraph::BuildLayoutTree(
	UStoryGraphNode* Node,
	TMap<UStoryGraphNode*, FStoryLayoutNode*>& OutMap
) const
{
	FStoryLayoutNode*& Layout = OutMap.FindOrAdd(Node);
	
	if (Layout)
	{
		return Layout;
	}
	
	Layout = new FStoryLayoutNode{ Node };

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			UStoryGraphNode* Child = Cast<UStoryGraphNode>(Linked->GetOwningNode());
			
			if (!Child)
			{
				continue;
			}
			
			Layout->Children.Add(BuildLayoutTree(Child, OutMap));
		}
	}

	return Layout;
}

float UStoryGraph::LayoutSubtree(
	FStoryLayoutNode* Node,
	float& CursorY,
	const float VerticalSpacing
) const
{
	if (Node->Children.IsEmpty())
	{
		Node->Y = CursorY;
		CursorY += VerticalSpacing;
		return Node->Y;
	}

	float MinY = TNumericLimits<float>::Max();
	float MaxY = TNumericLimits<float>::Lowest();

	for (FStoryLayoutNode* Child : Node->Children)
	{
		const float ChildY = LayoutSubtree(Child, CursorY, VerticalSpacing);
		MinY = FMath::Min(MinY, ChildY);
		MaxY = FMath::Max(MaxY, ChildY);
	}

	Node->Y = (MinY + MaxY) * 0.5f;
	return Node->Y;
}

void UStoryGraph::ApplyLayout(
	FStoryLayoutNode* LayoutNode,
	const int32 Depth,
	const float CellWidth
) const
{
	if (!LayoutNode || !LayoutNode->Node)
	{
		return;
	}

	LayoutNode->Node->NodePosX = Depth * CellWidth;
	LayoutNode->Node->NodePosY = LayoutNode->Y;

	for (FStoryLayoutNode* Child : LayoutNode->Children)
	{
		ApplyLayout(Child, Depth + 1, CellWidth);
	}
}
