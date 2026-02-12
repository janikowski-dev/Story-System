#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UStoryGraph.generated.h"

struct FStoryLayoutNode;
class UStoryNode;

UCLASS()
class STORYSYSTEMEDITOR_API UStoryGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	UStoryNode* GetRootNode() const;
	void Refresh() const;
	
private:
	void ApplyLayout() const;
	void ApplyLineIndexes() const;
	
	FStoryLayoutNode* BuildLayoutTree(
		UStoryNode* Node,
		TMap<UStoryNode*, FStoryLayoutNode*>& LayoutMap
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

	void ApplyLineIndexes(
		UStoryNode* Node,
		int32& NodeIndex,
		TSet<UStoryNode*>& Visited
	) const;

	void ApplyResponseIndexes() const;

public:
	TSharedPtr<SGraphEditor> Editor;
};