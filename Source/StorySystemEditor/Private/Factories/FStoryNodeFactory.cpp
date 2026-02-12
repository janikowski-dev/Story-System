#pragma once

#include "FStoryNodeFactory.h"
#include "Nodes/Slate/SStoryLineNode.h"
#include "Nodes/Slate/SStoryRootNode.h"
#include "Nodes/Slate/SStoryResponseNode.h"
#include "Nodes/Unreal/UStoryLineNode.h"
#include "Nodes/Unreal/UStoryResponseNode.h"
#include "Nodes/Unreal/UStoryRootNode.h"

TSharedPtr<SGraphNode> FStoryNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UStoryLineNode* TypedNode = Cast<UStoryLineNode>(Node))
	{
		return SNew(SStoryLineNode, TypedNode);
	}
		
	if (UStoryRootNode* TypedNode = Cast<UStoryRootNode>(Node))
	{
		return SNew(SStoryRootNode, TypedNode);
	}
		
	if (UStoryResponseNode* TypedNode = Cast<UStoryResponseNode>(Node))
	{
		return SNew(SStoryResponseNode, TypedNode);
	}
		
	return nullptr;
}
