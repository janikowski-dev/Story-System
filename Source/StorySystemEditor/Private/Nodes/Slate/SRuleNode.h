#pragma once

#include "SGraphNode.h"
#include "Nodes/Unreal/URuleNode.h"

class SRuleNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, URuleNode* InNode);
	virtual void UpdateGraphNode() override;
};
