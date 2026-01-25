#include "FGraphSchemaAction_AddNode.h"
#include "EdGraph/EdGraph.h"
#include "Layout/StoryGraphLayout.h"

UEdGraphNode* FGraphSchemaAction_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2f& Location,
	const bool bSelectNewNode
)
{
	const FScopedTransaction Transaction(NSLOCTEXT("StoryGraph", "AddNode", "Add Node"));
	UEdGraphNode* NewNode = CreateNewNode(ParentGraph);
	TryAttachingPin(ParentGraph, NewNode, FromPin);
	Layout(ParentGraph);
	return NewNode;
}

UEdGraphNode* FGraphSchemaAction_AddNode::CreateNewNode(UEdGraph* ParentGraph) const
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

void FGraphSchemaAction_AddNode::TryAttachingPin(
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
