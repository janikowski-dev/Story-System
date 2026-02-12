#pragma once

enum class EOutputType : int8;

struct FStoryNodeGraph_AddOutputNode : FEdGraphSchemaAction
{
	TSubclassOf<UEdGraphNode> NodeClass;
	EOutputType OutputType;

	explicit FStoryNodeGraph_AddOutputNode(
		const TSubclassOf<UEdGraphNode> InNodeClass,
		const EOutputType OutputType)
	: NodeClass(InNodeClass), OutputType(OutputType)
	{
	}

	virtual UEdGraphNode* PerformAction(
		UEdGraph* ParentGraph,
		UEdGraphPin* FromPin,
		const FVector2f& Location,
		bool bSelectNewNode = true
	) override;
	
	UEdGraphNode* CreateNewNode(UEdGraph* ParentGraph, const FVector2f& Location) const;
};
