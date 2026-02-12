#include "FStoryGraph_DeleteNodeWithChildren.h"
#include "EdGraph/EdGraph.h"

UEdGraphNode* FStoryGraph_DeleteNodeWithChildren::PerformAction(
	UEdGraph*,
	UEdGraphPin* FromPin,
	const FVector2f&,
	const bool
)
{
	if (UEdGraphNode* Node = Cast<UEdGraphNode>(FromPin->GetOwningNode()))
	{
		if (Node->CanUserDeleteNode())
		{
			Node->Modify();
			Node->DestroyNode();
		}
	}
	
	return nullptr;
}
