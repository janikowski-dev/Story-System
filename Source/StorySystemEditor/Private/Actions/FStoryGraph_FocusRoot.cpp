#include "FStoryGraph_FocusRoot.h"

#include "Nodes/Unreal/UStoryNode.h"
#include "Graphs/UStoryGraph.h"

UEdGraphNode* FStoryGraph_FocusRoot::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f&,
	bool
)
{
	const UStoryNode* RootNode = Cast<UStoryGraph>(ParentGraph)->GetRootNode();

	if (!RootNode)
	{
		return nullptr;
	}

	Cast<UStoryGraph>(ParentGraph)->Editor->JumpToNode(Cast<UEdGraphNode>(RootNode));
	return nullptr;
}
