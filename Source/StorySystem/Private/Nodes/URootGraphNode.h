#pragma once

#include "CoreMinimal.h"
#include "UStoryGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "URootGraphNode.generated.h"

UCLASS()
class STORYSYSTEM_API URootGraphNode : public UStoryGraphNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};