#pragma once

#include "SGraphNode.h"

class UDialogueNode;
class UDialogueResponseNode;
class UDialogueLineNode;
class UDialogueLinkNode;
class UDialogueRootNode;

enum ENodeViewType : int32
{
	Regular = 0,
	Collapsed = 1,
	Hidden = 2
};

template<typename TNodeType>
class SDialogueNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	virtual TSharedPtr<SGraphPin> GetHoveredPin(const FGeometry&, const FPointerEvent&) const override;
	virtual void UpdateGraphNode() override;

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) = 0;
	virtual FSlateColor GetHeaderColor() const = 0;
	
	void Cache(UEdGraphNode* Node);

private:
	void AddHeader(const TSharedRef<SVerticalBox>& Box);
	void ApplyCollapse() const;
	void RefreshGraph() const;
	void ApplyCollapse(
		UDialogueNode* CurrentNode,
		bool bParentHidden,
		TSet<UDialogueNode*>& Visited
	) const;
	void ToggleCollapsedState() const;
	FReply ToggleCollapse() const;
	int GetBodyIndex() const;
	
protected:
	TWeakObjectPtr<TNodeType> TypedNode;

private:
	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
};

extern template class SDialogueNode<UDialogueResponseNode>;
extern template class SDialogueNode<UDialogueLineNode>;
extern template class SDialogueNode<UDialogueLinkNode>;
extern template class SDialogueNode<UDialogueRootNode>;
