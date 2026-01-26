#include "FGraphSchemaAction_FocusRoot.h"

#include "Graphs/UStoryGraph.h"
#include "Nodes/URootGraphNode.h"

UEdGraphNode* FGraphSchemaAction_FocusRoot::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f&,
	bool
)
{
	const UStoryGraphNode* RootNode = Cast<UStoryGraph>(ParentGraph)->GetRootNode();

	if (!RootNode)
	{
		return nullptr;
	}

	Cast<UStoryGraph>(ParentGraph)->Editor->JumpToNode(RootNode);
	return nullptr;
}
