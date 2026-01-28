#include "URootStoryNode.h"

void URootStoryNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("StoryPin"), NAME_None, nullptr, TEXT("Out"));
}
