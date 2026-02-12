#include "URuleOutputNode.h"

void URuleOutputNode::AllocateDefaultPins()
{
	if (Type == EOutputType::Requirements)
	{
		CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Result"));
	}
	else
	{
		CreatePin(EGPD_Input, TEXT("Callback"), NAME_None, nullptr, TEXT("Result"));
	}
}

FText URuleOutputNode::GetNodeTitle(ENodeTitleType::Type) const
{
	switch (Type)
	{
	case EOutputType::PreCallback: return FText::FromString("Pre Response Callback");
	case EOutputType::PostCallback: return FText::FromString("Post Response Callback");
	case EOutputType::Requirements: return FText::FromString("Requirements For Response");
	default: return FText::FromString("Invalid Node");
	}
}

bool URuleOutputNode::AllowMultipleInputs() const
{
	return Type != EOutputType::Requirements;
}

FLinearColor URuleOutputNode::GetNodeTitleColor() const
{
	switch (Type)
	{
	case EOutputType::PreCallback: return FLinearColor::Red;
	case EOutputType::PostCallback: return FLinearColor::Red;
	case EOutputType::Requirements: return FLinearColor::Blue;
	default: return FLinearColor::White;
	}
}
