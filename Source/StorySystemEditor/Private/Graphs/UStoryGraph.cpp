#include "UStoryGraph.h"

#include "Nodes/Unreal/UStoryLineNode.h"
#include "Nodes/Unreal/UStoryResponseNode.h"
#include "Nodes/Unreal/UStoryRootNode.h"

struct FStoryLayoutNode
{
	UStoryNode* Node = nullptr;
	TArray<FStoryLayoutNode*> Children;
	float Y = 0.0f;
};

void UStoryGraph::PostLoad()
{
	Super::PostLoad();
	Refresh();
}

void UStoryGraph::Refresh() const
{
	ApplyLayout();
	ApplyLineIndexes();
	ApplyResponseIndexes();
}

void UStoryGraph::ApplyLayout() const
{
	constexpr float CellWidth  = 350.0f;
	constexpr float CellHeight = 300.0f;
	float CursorY = 0.0f;

	TMap<UStoryNode*, FStoryLayoutNode*> LayoutMap;
	FStoryLayoutNode* Layout = BuildLayoutTree(GetRootNode(), LayoutMap);
	LayoutSubtree(Layout, CursorY, CellHeight);
	ApplyLayout(Layout, 0, CellWidth);
	
	for (const TPair<UStoryNode*, FStoryLayoutNode*>& Iterator : LayoutMap)
	{
		delete Iterator.Value;
	}
}

void UStoryGraph::ApplyLineIndexes() const
{
	int32 NodeIndex = 0;
	TSet<UStoryNode*> Visited;
	ApplyLineIndexes(GetRootNode(), NodeIndex, Visited);
}

UStoryNode* UStoryGraph::GetRootNode() const
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (UStoryRootNode* Root = Cast<UStoryRootNode>(Node))
		{
			return Root;
		}
	}
	
	return nullptr;
}

FStoryLayoutNode* UStoryGraph::BuildLayoutTree(
	UStoryNode* Node,
	TMap<UStoryNode*, FStoryLayoutNode*>& LayoutMap
) const
{
	FStoryLayoutNode*& Layout = LayoutMap.FindOrAdd(Node);
	
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
			UStoryNode* Child = Cast<UStoryNode>(Linked->GetOwningNode());
			
			if (!Child)
			{
				continue;
			}
			
			Layout->Children.Add(BuildLayoutTree(Child, LayoutMap));
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
	constexpr float InvisibleAndOutOfSightNodeX = -100000.0f;
	
	if (!LayoutNode || !LayoutNode->Node)
	{
		return;
	}

	if (LayoutNode->Node->bIsHidden)
	{
		LayoutNode->Node->NodePosX = InvisibleAndOutOfSightNodeX;
	}
	else
	{
		LayoutNode->Node->NodePosX = Depth * CellWidth;
	}
	
	LayoutNode->Node->NodePosY = LayoutNode->Y;

	for (FStoryLayoutNode* Child : LayoutNode->Children)
	{
		ApplyLayout(Child, Depth + 1, CellWidth);
	}
}

void UStoryGraph::ApplyLineIndexes(
	UStoryNode* Node,
	int32& NodeIndex,
	TSet<UStoryNode*>& Visited
) const
{
	if (!Node || Visited.Contains(Node))
	{
		return;
	}

	Visited.Add(Node);

	if (UStoryLineNode* Line = Cast<UStoryLineNode>(Node))
	{
		Line->LineIndex = ++NodeIndex;
	}

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (UStoryNode* Child = Cast<UStoryNode>(Linked->GetOwningNode()))
			{
				ApplyLineIndexes(Child, NodeIndex, Visited);
			}
		}
	}
}

void UStoryGraph::ApplyResponseIndexes() const
{
	for (UEdGraphNode* GraphNode : Nodes)
	{
		UStoryLineNode* Line = Cast<UStoryLineNode>(GraphNode);
		
		if (!Line)
		{
			continue;
		}

		int32 ChildIndex = 0;

		for (UEdGraphPin* Pin : Line->Pins)
		{
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}

			for (const UEdGraphPin* Linked : Pin->LinkedTo)
			{
				if (UStoryResponseNode* Response = Cast<UStoryResponseNode>(Linked->GetOwningNode()))
				{
					Response->ParentIndex = Line->LineIndex;
					Response->OrderIndex = ++ChildIndex;
				}
			}
		}
	}
}
