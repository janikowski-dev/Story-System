#pragma once

#include "EdGraphUtilities.h"
#include "Nodes/SDialogueGraphNode.h"
#include "Nodes/SRootGraphNode.h"
#include "Nodes/UDialogueGraphNode.h"
#include "Nodes/URootGraphNode.h"

class FStorySystemNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UDialogueGraphNode* DialogueNode = Cast<UDialogueGraphNode>(Node))
		{
			return SNew(SDialogueGraphNode, DialogueNode);
		}
		
		if (URootGraphNode* RootNode = Cast<URootGraphNode>(Node))
		{
			return SNew(SRootGraphNode, RootNode);
		}
		
		return nullptr;
	}
};
