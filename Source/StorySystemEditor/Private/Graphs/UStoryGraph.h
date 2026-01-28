#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UStoryGraph.generated.h"

struct FStoryLayoutNode
{
	UEdGraphNode* Node = nullptr;
	TArray<FStoryLayoutNode*> Children;
	float Y = 0.f;
};

UCLASS()
class STORYSYSTEMEDITOR_API UStoryGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	
	UEdGraphNode* GetRootNode() const;
	
	void AutoLayout() const;
	
	FStoryLayoutNode* BuildLayoutTree(
		UEdGraphNode* Node,
		TMap<UEdGraphNode*, FStoryLayoutNode*>& OutMap
	) const;
	
	float LayoutSubtree(
		FStoryLayoutNode* Node,
		float& CursorY,
		float VerticalSpacing
	) const;
	
	void ApplyLayout(
		FStoryLayoutNode* LayoutNode,
		int32 Depth,
		float CellWidth
	) const;

public:
	TSharedPtr<SGraphEditor> Editor;
};