#pragma once

#include "FRuleNodeFactory.h"

#include "Nodes/Slate/SRuleNode.h"
#include "Nodes/Unreal/URuleNode.h"

TSharedPtr<SGraphNode> FRuleNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (URuleNode* TypedNode = Cast<URuleNode>(Node))
	{
		return SNew(SRuleNode, TypedNode);
	}
		
	return nullptr;
}
