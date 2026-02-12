#include "UStoryNodeGraphSchema.h"

#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Actions/FStoryNodeGraph_AddNode.h"
#include "Actions/FStoryNodeGraph_AddOutputNode.h"
#include "Nodes/Unreal/URuleAndNode.h"
#include "Nodes/Unreal/URuleCallbackNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"
#include "Nodes/Unreal/URuleOrNode.h"
#include "Nodes/Unreal/URuleOutputNode.h"

void UStoryNodeGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	MakeShared<FStoryNodeGraph_AddOutputNode>(
		URuleOutputNode::StaticClass(),
		EOutputType::Requirements
	)->PerformAction(&Graph, nullptr, FVector2f(0.0f, -128.0f));
	
	MakeShared<FStoryNodeGraph_AddOutputNode>(
		URuleOutputNode::StaticClass(),
		EOutputType::PreCallback
	)->PerformAction(&Graph, nullptr, FVector2f::Zero());
	
	MakeShared<FStoryNodeGraph_AddOutputNode>(
		URuleOutputNode::StaticClass(),
		EOutputType::PostCallback
	)->PerformAction(&Graph, nullptr, FVector2f(0.0f, 128.0f));
}

void UStoryNodeGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("Condition Node"),
			FText::FromString("Adds a condition node"),
			URuleConditionNode::StaticClass()
		)
	);
	
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("And Node"),
			FText::FromString("Adds an and node"),
			URuleAndNode::StaticClass()
		)
	);
	
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("Or Node"),
			FText::FromString("Adds an or node"),
			URuleOrNode::StaticClass()
		)
	);
	
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("Callback Node"),
			FText::FromString("Adds a callback node"),
			URuleCallbackNode::StaticClass()
		)
	);
}

const FPinConnectionResponse UStoryNodeGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	if (A->PinType.PinCategory != B->PinType.PinCategory)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Nodes don't belong to the same category"));
	}
	
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't connect same direction pins"));
	}
	
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't connect pins from the same node"));
	}

	if (A->LinkedTo.Contains(B))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Pins are already connected"));
	}

	const UEdGraphPin* InputPin = nullptr;
	const URuleNode* InputNode = nullptr;

	if (A->Direction == EGPD_Input)
	{
		InputPin = A;
	}
	else if (B->Direction == EGPD_Input)
	{
		InputPin = B;
	}

	if (InputPin)
	{
		InputNode = Cast<URuleNode>(InputPin->GetOwningNode());
	}

	if (InputNode && !InputNode->AllowMultipleInputs() && InputPin->LinkedTo.Num() > 0)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,TEXT("This pin allows only one input"));
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, "");
}
