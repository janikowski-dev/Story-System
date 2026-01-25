#include "UStoryGraphSchema.h"
#include "Actions/FGraphSchemaAction_AddNode.h"
#include "Nodes/UDialogueGraphNode.h"
#include "Nodes/URootGraphNode.h"
#include "Policies/StoryConnectionDrawingPolicy.h"
#include "Rendering/DrawElements.h"

void UStoryGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	URootGraphNode* EntryNode = NewObject<URootGraphNode>(
		&Graph,
		URootGraphNode::StaticClass(),
		NAME_None,
		RF_Transactional
	);

	Graph.AddNode(EntryNode, true, false);

	EntryNode->CreateNewGuid();
	EntryNode->PostPlacedNewNode();
	EntryNode->AllocateDefaultPins();

	EntryNode->NodePosX = 0;
	EntryNode->NodePosY = 0;
}

const FPinConnectionResponse UStoryGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(
			CONNECT_RESPONSE_DISALLOW,
			TEXT("Pins must be input/output")
		);
	}

	if (A->PinType.PinCategory != B->PinType.PinCategory)
	{
		return FPinConnectionResponse(
			CONNECT_RESPONSE_DISALLOW,
			TEXT("Pin types do not match")
		);
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UStoryGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	if (!A || !B)
	{
		return false;
	}
	
	if (const FPinConnectionResponse Response = CanCreateConnection(A, B); Response.Response == CONNECT_RESPONSE_DISALLOW)
	{
		return false;
	}

	UEdGraph* Graph = A->GetOwningNode()->GetGraph();
	check(Graph);

	Graph->Modify();

	A->Modify();
	B->Modify();

	A->MakeLinkTo(B);

	Graph->NotifyGraphChanged();
	return true;
}

FConnectionDrawingPolicy* UStoryGraphSchema::CreateConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj
) const
{
	return new FStoryConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	);
}

void UStoryGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	if (!ContextMenuBuilder.FromPin)
	{
		return;
	}

	Super::GetGraphContextActions(ContextMenuBuilder);
	
	ContextMenuBuilder.AddAction(MakeShared<FGraphSchemaAction_AddNode>(
		FText::FromString("Dialogue"),
		FText::FromString("Dialogue Node"),
		FText::FromString("Adds a dialogue node"),
		UDialogueGraphNode::StaticClass()
	));
}
