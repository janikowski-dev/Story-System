#include "SStoryRootNode.h"

#include "Nodes/Unreal/UStoryRootNode.h"

void SStoryRootNode::Construct(const FArguments&, UStoryRootNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

void SStoryRootNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
}

FText SStoryRootNode::GetTitle(UStoryNode* Node)
{
	return FText::FromString("ROOT");
}

FSlateColor SStoryRootNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Black);
}
