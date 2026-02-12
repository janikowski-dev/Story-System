#include "URuleCallbackNode.h"

void URuleCallbackNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("Callback"), NAME_None, nullptr, TEXT("Output"));
}

FText URuleCallbackNode::GetNodeTitle(ENodeTitleType::Type Param) const
{
	return FText::FromString("Callback");
}

FLinearColor URuleCallbackNode::GetNodeTitleColor() const
{
	return FLinearColor::Red;
}
