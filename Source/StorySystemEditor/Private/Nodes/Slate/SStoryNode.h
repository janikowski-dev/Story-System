#pragma once

#include "SGraphNode.h"

enum ENodeViewType : int32
{
	Regular = 0,
	Collapsed = 1,
	Hidden = 2
};

class UStoryNode;

class SStoryNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual TSharedPtr<SGraphPin> GetHoveredPin(const FGeometry&, const FPointerEvent&) const override;
	virtual void UpdateGraphNode() override;

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) = 0;
	virtual FText GetTitle(UStoryNode* Node) = 0;
	virtual FSlateColor GetHeaderColor() const = 0;
	void Cache(UEdGraphNode* Node);

private:
	void AddHeader(const TSharedRef<SVerticalBox>& Box);
	void ApplyCollapse() const;
	void RefreshGraph() const;
	void ApplyCollapse(
		UStoryNode* CurrentNode,
		bool bParentHidden,
		TSet<UStoryNode*>& Visited
	) const;
	void ToggleCollapsedState() const;
	FReply ToggleCollapse() const;
	int GetBodyIndex() const;
	
public:
	TWeakObjectPtr<UStoryNode> TypedNode;

private:
	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
};
