#include "StoryGraphLayout.h"
#include "Graphs/UStoryGraph.h"
#include "Nodes/UStoryGraphNode.h"

void LayoutNode(UStoryGraphNode* Node)
{
	constexpr float CellWidth  = 350.0f;
	constexpr float CellHeight = 300.0f;

	const UStoryGraph* Graph = CastChecked<UStoryGraph>(Node->GetGraph());

	const int32 Column = Graph->GetNodeColumn(Node);
	const int32 Row = Graph->GetNodeRow(Node);
	
	Node->NodePosX = Column * CellWidth;
	Node->NodePosY = Row * CellHeight;
}

void Layout(TArray<TObjectPtr<UEdGraphNode>> Nodes)
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (auto* StoryNode = Cast<UStoryGraphNode>(Node))
		{
			LayoutNode(StoryNode);
		}
	}
}

void Layout(const UEdGraph* Graph)
{
	Layout(Graph->Nodes);
}