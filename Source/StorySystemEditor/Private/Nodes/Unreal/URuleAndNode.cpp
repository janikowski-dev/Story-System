#include "URuleAndNode.h"

void URuleAndNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition A"));
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition B"));
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("A and B"));
}

FText URuleAndNode::GetNodeTitle(ENodeTitleType::Type) const
{
	return FText::FromString("And");
}

FLinearColor URuleAndNode::GetNodeTitleColor() const
{
	return FLinearColor::Blue;
}
