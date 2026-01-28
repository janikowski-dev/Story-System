#pragma once

#include "SGraphNode.h"

class SStoryNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true ) override;
	
	virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;
	
	virtual TSharedPtr<SGraphPin> GetHoveredPin(
		const FGeometry& MyGeometry,
		const FPointerEvent& MouseEvent
	) const override;
	
	virtual FReply OnMouseButtonDoubleClick(
		const FGeometry& InMyGeometry,
		const FPointerEvent& InMouseEvent
	) override;
};
