#include "UDialogueGraphNode.h"

void UDialogueGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input,  TEXT("StoryPin"), NAME_None, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, TEXT("StoryPin"), NAME_None, nullptr, TEXT("Out"));
}