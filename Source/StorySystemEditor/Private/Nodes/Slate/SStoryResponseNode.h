#pragma once

#include "SStoryNode.h"

class UStoryResponseNode;

class SStoryResponseNode : public SStoryNode
{
public:
	SLATE_BEGIN_ARGS(SStoryResponseNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStoryResponseNode* InNode);
	virtual void UpdateGraphNode() override;
};
