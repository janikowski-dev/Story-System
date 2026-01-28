#include "SStoryGraphPin.h"

#include "SGraphPin.h"

void SStoryGraphPin::Construct(const FArguments&, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);
	SetShowLabel(false);
	SetEnabled(false);
}

const FSlateBrush* SStoryGraphPin::GetPinIcon() const
{
	return nullptr;
}
