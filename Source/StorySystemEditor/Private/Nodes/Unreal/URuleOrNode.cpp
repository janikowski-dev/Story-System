#include "URuleOrNode.h"

void URuleOrNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition A"));
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition B"));
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("A or B"));
}

FText URuleOrNode::GetNodeTitle(ENodeTitleType::Type) const
{
	return FText::FromString("Or");
}

FLinearColor URuleOrNode::GetNodeTitleColor() const
{
	return FLinearColor::Blue;
}
