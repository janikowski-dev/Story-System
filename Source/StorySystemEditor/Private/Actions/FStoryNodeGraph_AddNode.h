#pragma once

struct FStoryNodeGraph_AddNode : FEdGraphSchemaAction
{
	TSubclassOf<UEdGraphNode> NodeClass;

	explicit FStoryNodeGraph_AddNode(const TSubclassOf<UEdGraphNode> InNodeClass) : NodeClass(InNodeClass)
	{
	}
	
	explicit FStoryNodeGraph_AddNode(
		const FText& InCategory,
		const FText& InMenuDesc,
		const FText& InTooltip,
		const TSubclassOf<UEdGraphNode> InNodeClass
	)
		: FEdGraphSchemaAction(InCategory, InMenuDesc, InTooltip, 0)
		, NodeClass(InNodeClass)
	{}

	virtual UEdGraphNode* PerformAction(
		UEdGraph* ParentGraph,
		UEdGraphPin* FromPin,
		const FVector2f& Location,
		bool bSelectNewNode = true
	) override;
	
	UEdGraphNode* CreateNewNode(UEdGraph* ParentGraph, const FVector2f& Location) const;
};