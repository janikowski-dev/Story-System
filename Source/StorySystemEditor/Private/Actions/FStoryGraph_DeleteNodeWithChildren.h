#pragma once

struct FStoryGraph_DeleteNodeWithChildren : FEdGraphSchemaAction
{
	virtual UEdGraphNode* PerformAction(
		UEdGraph* ParentGraph,
		UEdGraphPin* FromPin,
		const FVector2f& Location,
		bool bSelectNewNode = true
	) override;
};