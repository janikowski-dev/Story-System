#pragma once

#include "UStoryGraphNode.generated.h"

UCLASS()
class UStoryGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual bool CanUserDeleteNode() const override
	{
		return true;
	}
};