#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "URootStoryNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API URootStoryNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
};