#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "UStoryResponseNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryResponseNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
};