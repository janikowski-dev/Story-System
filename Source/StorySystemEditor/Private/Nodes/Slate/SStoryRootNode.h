#pragma once

#include "SStoryNode.h"

class URootStoryNode;

class SStoryRootNode : public SStoryNode
{
public:
	SLATE_BEGIN_ARGS(SStoryRootNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, URootStoryNode* InNode);
	virtual void UpdateGraphNode() override;
};
