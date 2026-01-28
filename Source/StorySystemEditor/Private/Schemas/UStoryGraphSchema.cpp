#include "UStoryGraphSchema.h"

#include "Policies/FStoryGraphConnectionDrawingPolicy.h"
#include "Actions/FStoryGraph_AddNode.h"
#include "Nodes/Unreal/UStoryResponseNode.h"
#include "Nodes/Unreal/URootStoryNode.h"
#include "Nodes/Unreal/UStoryDialogueNode.h"
#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Actions/FStoryGraph_FocusRoot.h"

#pragma region Initialization

void UStoryGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	MakeShared<FStoryGraph_AddNode>(
		FText::FromString("Root"),
		FText::FromString("Root Node"),
		FText::FromString("Adds a root node"),
		URootStoryNode::StaticClass()
	)->PerformAction(&Graph,nullptr, FVector2f::Zero(), true);
}

#pragma endregion

#pragma region Connection

FConnectionDrawingPolicy* UStoryGraphSchema::CreateConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj
) const
{
	return new FStoryGraphConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	);
}

const FPinConnectionResponse UStoryGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UStoryGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	A->Modify();
	B->Modify();
	A->MakeLinkTo(B);
	return true;
}

#pragma endregion

#pragma region Additional Actions

void UStoryGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FStoryGraph_FocusRoot>());
}

#pragma endregion

#pragma region Node Creation

void UStoryGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection* Section = CreateSection(Menu, Context);

	if (!Section)
	{
		return;
	}

	AddDialogueContext(Context, Section);
	AddResponseContext(Context, Section);
	AddRootContext(Context, Section);
}

void UStoryGraphSchema::AddDialogueContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UStoryDialogueNode* Node = Cast<UStoryDialogueNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	if (HasChildOfType(Node, UStoryResponseNode::StaticClass()))
	{
		AddResponseAction(Context, Section);
	}
	else if (!HasAnyChild(Node))
	{
		AddDialogueAction(Context, Section);
		AddResponseAction(Context, Section);
	}
}

void UStoryGraphSchema::AddResponseContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UStoryResponseNode* Node = Cast<UStoryResponseNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	if (HasAnyChild(Node))
	{
		return;
	}
	
	AddDialogueAction(Context, Section);
}

void UStoryGraphSchema::AddRootContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const URootStoryNode* Node = Cast<URootStoryNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	if (HasAnyChild(Node))
	{
		return;
	}
	
	AddDialogueAction(Context, Section);
}

void UStoryGraphSchema::AddDialogueAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = GetOutputPin(Context->Node);
	
	Section->AddMenuEntry(
		"AddDialogueNode",
		FText::FromString("Dialogue Node"),
		FText::FromString("Adds a dialogue node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FStoryGraph_AddNode>(
					FText::FromString("Dialogue"),
					FText::FromString("Dialogue Node"),
					FText::FromString("Adds a dialogue node"),
					UStoryDialogueNode::StaticClass()
				)->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

void UStoryGraphSchema::AddResponseAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = GetOutputPin(Context->Node);
	
	Section->AddMenuEntry(
		"AddResponseNode",
		FText::FromString("Response Node"),
		FText::FromString("Adds a response node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FStoryGraph_AddNode>(
					FText::FromString("Response"),
					FText::FromString("Response Node"),
					FText::FromString("Adds a response node"),
					UStoryResponseNode::StaticClass()
				)->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

bool UStoryGraphSchema::HasChildOfType(const UEdGraphNode* Node, UClass* ChildClass) const
{
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (!Linked || !Linked->GetOwningNode()->IsA(ChildClass))
			{
				continue;
			}
			
			return true;
		}
	}

	return false;
}

bool UStoryGraphSchema::HasAnyChild(const UEdGraphNode* Node) const
{
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}
		
		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (Linked)
			{
				return true;
			}
		}
	}

	return false;
}

FToolMenuSection* UStoryGraphSchema::CreateSection(UToolMenu* Menu, const UGraphNodeContextMenuContext* Context) const
{
	if (!Context->Node)
	{
		return nullptr;
	}
	
	return &Menu->AddSection("SchemaNode", FText::FromString("Schema"));
}

UEdGraphPin* UStoryGraphSchema::GetOutputPin(const UEdGraphNode* Node) const
{
	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin && Pin->Direction == EGPD_Output)
		{
			return Pin;
		}
	}
	return nullptr;
}

#pragma endregion
