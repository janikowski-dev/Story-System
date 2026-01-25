#pragma once

#include "SGraphNode.h"

class SStoryGraphNode : public SGraphNode
{
public:
	virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true ) override;
};