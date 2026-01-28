#include "UStoryNodeGraphSchema.h"

#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Actions/FStoryNodeGraph_AddNode.h"
#include "Nodes/Unreal/URuleNode.h"

void UStoryNodeGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Rule"),
			FText::FromString("Rule Node"),
			FText::FromString("Adds a rule node"),
			URuleNode::StaticClass()
		)
	);
}

const FPinConnectionResponse UStoryNodeGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UStoryNodeGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	A->Modify();
	B->Modify();
	A->MakeLinkTo(B);
	return true;
}
