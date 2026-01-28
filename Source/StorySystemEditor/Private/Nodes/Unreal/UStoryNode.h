#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
	UEdGraph* GetInnerGraph();

private:
	void InitGraph();
};