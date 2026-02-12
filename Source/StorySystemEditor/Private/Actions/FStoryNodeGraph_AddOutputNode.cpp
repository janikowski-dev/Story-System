#include "FStoryNodeGraph_AddOutputNode.h"

#include "EdGraph/EdGraph.h"
#include "Nodes/Unreal/URuleOutputNode.h"

UEdGraphNode* FStoryNodeGraph_AddOutputNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f& Location,
	const bool
)
{
	const FScopedTransaction Transaction(NSLOCTEXT("NodeGraph", "AddNode", "Add Node"));
	return CreateNewNode(ParentGraph, Location);
}

UEdGraphNode* FStoryNodeGraph_AddOutputNode::CreateNewNode(UEdGraph* ParentGraph, const FVector2f& Location) const
{
	ParentGraph->Modify();

	URuleOutputNode* NewNode = NewObject<URuleOutputNode>(
		ParentGraph,
		NodeClass,
		NAME_None,
		RF_Transactional
	);

	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	NewNode->Type = OutputType;
	
	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();
	
	ParentGraph->AddNode(NewNode, true, true);
	
	return NewNode;
}
