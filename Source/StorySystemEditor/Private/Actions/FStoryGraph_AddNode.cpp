#include "FStoryGraph_AddNode.h"
#include "EdGraph/EdGraph.h"
#include "Graphs/UStoryGraph.h"

UEdGraphNode* FStoryGraph_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2f& Location,
	const bool bSelectNewNode
)
{
	const FScopedTransaction Transaction(NSLOCTEXT("StoryGraph", "AddNode", "Add Node"));
	UEdGraphNode* NewNode = CreateNewNode(ParentGraph);
	TryAttachingPin(ParentGraph, NewNode, FromPin);
	Cast<UStoryGraph>(ParentGraph)->AutoLayout();
	return NewNode;
}

UEdGraphNode* FStoryGraph_AddNode::CreateNewNode(UEdGraph* ParentGraph) const
{
	ParentGraph->Modify();

	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(
		ParentGraph,
		NodeClass,
		NAME_None,
		RF_Transactional
	);

	ParentGraph->AddNode(NewNode, true, true);

	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();
	
	return NewNode;
}

void FStoryGraph_AddNode::TryAttachingPin(
	const UEdGraph* ParentGraph,
	UEdGraphNode* NewNode,
	UEdGraphPin* FromPin
) const
{
	if (!FromPin)
	{
		return;
	}
	
	UEdGraphPin* TargetPin = nullptr;

	for (UEdGraphPin* Pin : NewNode->Pins)
	{
		if (Pin->Direction == FromPin->Direction || Pin->PinType.PinCategory != FromPin->PinType.PinCategory)
		{
			continue;
		}
		
		TargetPin = Pin;
		break;
	}

	if (!TargetPin)
	{
		return;
	}

	ParentGraph->GetSchema()->TryCreateConnection(
		FromPin,
		TargetPin
	);
}
