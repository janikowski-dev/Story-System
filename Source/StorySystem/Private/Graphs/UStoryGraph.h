#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UStoryGraph.generated.h"

class UStoryGraphNode;

UCLASS()
class STORYSYSTEM_API UStoryGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	virtual void PostLoad() override;
	int32 GetNodeColumn(const UStoryGraphNode* Node) const;
	int32 GetNodeRow(const UStoryGraphNode* Node) const;
	UStoryGraphNode* GetRootNode() const;
};