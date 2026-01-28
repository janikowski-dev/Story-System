#include "FStoryGraph_FocusRoot.h"

#include "Graphs/UStoryGraph.h"

UEdGraphNode* FStoryGraph_FocusRoot::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f&,
	bool
)
{
	const UEdGraphNode* RootNode = Cast<UStoryGraph>(ParentGraph)->GetRootNode();

	if (!RootNode)
	{
		return nullptr;
	}

	Cast<UStoryGraph>(ParentGraph)->Editor->JumpToNode(RootNode);
	return nullptr;
}
