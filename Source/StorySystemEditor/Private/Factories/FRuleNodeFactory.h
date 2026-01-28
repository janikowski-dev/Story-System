#pragma once

#include "EdGraphUtilities.h"

class STORYSYSTEMEDITOR_API FRuleNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};
