#pragma once

#include "SStoryGraphNode.h"

class URootGraphNode;

class SRootGraphNode : public SStoryGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRootGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, URootGraphNode* InNode);
	virtual void UpdateGraphNode() override;
};
